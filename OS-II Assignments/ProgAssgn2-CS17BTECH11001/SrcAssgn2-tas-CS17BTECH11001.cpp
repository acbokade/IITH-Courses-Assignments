//Ajinkya Bokade
//CS17BTECH11001

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>
#include <atomic>
#include <string.h>
#include <unistd.h>
#include <random>
using namespace std;

long long n, k, l1=1, l2=1; //input parameters
double waitingTime = 0; //waiting time
double avgWaitingTime = 0; //average waiting time
double maxWaitingTime = -1.0; //worst case waiting time
ifstream input;
FILE *output1, *output2;

//intialize lock 
atomic_flag lock = ATOMIC_FLAG_INIT; 

//test function 
void* testCS(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	default_random_engine generator; //random number generator
	generator.seed(4); //seeding generator 
	exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
	exponential_distribution<double> exponential2((double)1/(double)l2);
	//running loop for k times
	for(long long i=0;i<k;i++)
	{
		//Entry 
		time_t currentTime1 = time(0);
		tm *EntryTime = localtime(&currentTime1);
		fprintf(output1,"%lldth CS Request at %.2d:%.2d:%.2d by thread %lld\n",i+1,EntryTime->tm_hour,EntryTime->tm_min,EntryTime->tm_sec,id);
		
		// spin until the lock is acquired
		while(std::atomic_flag_test_and_set_explicit(&lock, std::memory_order_acquire));

		//Critical Section
		time_t currentTime2 =  time(0);
		if(currentTime2 - currentTime1 > maxWaitingTime)
			maxWaitingTime = currentTime2 - currentTime1;
		waitingTime += currentTime2 - currentTime1;
		tm *acceptTime = localtime(&currentTime2);
		fprintf(output1,"%lldth CS Entry at %.2d:%.2d:%.2d by thread %lld\n",i+1,acceptTime->tm_hour,acceptTime->tm_min,acceptTime->tm_sec,id);
		sleep(exponential1(generator)); //sleeping thread

 		atomic_flag_clear_explicit(&lock, std::memory_order_release);

		//Remainder Section
		currentTime1 = time(0);
		tm *exitTime = localtime(&currentTime1);
		fprintf(output1,"%lldth CS Exit at %.2d %.2d:%.2d by thread %lld\n",i+1,exitTime->tm_hour,exitTime->tm_min,exitTime->tm_sec,id);
		sleep(exponential2(generator)); //sleeping thread
	}
	pthread_exit(0);
}

int main()
{
	input.open("inp-params.txt");
	output1 = fopen("TAS.txt", "w");
	output2 = fopen("performanceTAS.txt", "w");
	input>>n>>k>>l1>>l2;
	pthread_t threads[n];
	pthread_attr_t attr;
	pthread_attr_init(&attr);//setting attributes of threads
	fprintf(output1, "TAS ME Output:\n");
	//creating threads
	for(long long i=0;i<n;i++)
		pthread_create(threads+i, &attr, testCS, (void*)i);
	//joining threads
	for(int i=0;i<n;i++)
		pthread_join(threads[i], NULL);

	avgWaitingTime = (double)waitingTime/(double)(n*k); //calculating average waiting time
	fprintf(output2, "Average time taken to enter CS by each thread is %lf\n", avgWaitingTime);
	fprintf(output2, "Worst case time taken by a process to enter the CS is %lf\n", maxWaitingTime);
	input.close();
	fclose(output1);
	fclose(output2);
	return 0;
}