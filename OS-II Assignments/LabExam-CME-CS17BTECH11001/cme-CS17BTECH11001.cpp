//Ajinkya Bokade
//CS17BTECH11001

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <atomic>
#include <string.h>
#include <fcntl.h>
#include <random>
#include <sys/time.h>
#include <semaphore.h>
using namespace std;

ifstream input;
FILE *output1, *output2;
long long n,S,k,l1,l2; //input parameters
long long count = 0;
double waiting_time_request = 0;
double waiting_time_release = 0;
sem_t class_mutex, mutex;
bool *active_states;
double avg_waiting_time_request, avg_waiting_time_release; //average waiting time for readers and writers
default_random_engine generator1, generator2; //random number generator
exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
exponential_distribution<double> exponential2((double)1/(double)l2); //setting lambda values for exponential distribution

void* testCS(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	long long j;
	for(j=0;j<k;j++)
	{
		//random integer for session
		long long s = 1 + rand()%S;
		//entry section
		struct timeval requestTime, endTime, releaseTime;
		gettimeofday(&requestTime,NULL);
		time_t currentTime1 = time(0); //getting current time
		tm *entryTime = localtime(&currentTime1);
		fprintf(output1,"%lldth CS Request at %.2d:%.2d:%.2d by thread %lld for session %lld\n",j+1 ,entryTime->tm_hour, entryTime->tm_min, entryTime->tm_sec, id, s);

		//entrySec(s);
		if(!active_states[s])
		{
			sem_wait(&class_mutex);
			active_states[s] = true;
		}
		sem_wait(&mutex);
		count++;
		sem_post(&mutex);
		//entering CS 
		time_t currentTime2 = time(0); //getting current time
		tm *CSentryTime = localtime(&currentTime2);
		fprintf(output1,"%lldth CS Entry at %.2d:%.2d:%.2d by thread %lld for session %lld\n",j+1 ,CSentryTime->tm_hour, CSentryTime->tm_min, CSentryTime->tm_sec, id, s);
		gettimeofday(&endTime, NULL);
		waiting_time_request+=(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec));//calculating waiting time by taking difference between the time at which thread entered CS and it made request
		usleep(exponential1(generator1)*1000); //simulate a thread writing in CS
		
		//exitSec(s);
		sem_wait(&mutex);
		count--;
		if(count == 0)
		{
			sem_post(&class_mutex);
			active_states[s] = false;
		}
		time_t currentTime3 = time(0); //getting current time
		tm *exitTime = localtime(&currentTime3);
		fprintf(output1,"%lldth CS Exit at %.2d:%.2d:%.2d by thread %lld for session %lld\n",j+1 ,exitTime->tm_hour, exitTime->tm_min, exitTime->tm_sec, id, s);
		sem_post(&mutex);
		gettimeofday(&releaseTime, NULL);
		waiting_time_release+=(double)((releaseTime.tv_usec-endTime.tv_usec)*0.000001 + (releaseTime.tv_sec-endTime.tv_sec));
		usleep(exponential2(generator2)*1000); //simulate a thread exiting in exit section
	}
}

int main()
{
	srand(time(NULL));
	input.open("inp-params.txt");
	output1 = fopen("Log.txt", "w");
	output2 = fopen("times.txt", "w");
	input>>n>>k>>S>>l1>>l2;
	sem_init(&class_mutex,0,1); //initializing class_mutex to 1
	sem_init(&mutex,0,1); //initializing mutex lock to 1 to provide mutual exclusion
	active_states = new bool[S];
	pthread_t threads[n]; // threads
	pthread_attr_t attr;
	pthread_attr_init(&attr); //setting attributes of threads
	//creating readers and writers
	for(long long i=0;i<n;i++)
	{
		pthread_create(threads+i, &attr, testCS, (void*)i);
	}
	for(long long i=0;i<S;i++)
	{
		active_states[i] = false;
	}
	//joining threads
	for(long long i=0;i<n;i++)
	{
		pthread_join(threads[i], NULL);
	}
	avg_waiting_time_request = waiting_time_request/n;
	avg_waiting_time_release = waiting_time_release/n;
	fprintf(output2,"Average waiting time taken by scheduler to process request method for threads is %lf milliseconds\n",avg_waiting_time_request*1000);
	fprintf(output2,"Average waiting time taken by scheduler to process release method for threads is %lf milliseconds\n",avg_waiting_time_release*1000);
	sem_destroy(&class_mutex);
	sem_destroy(&mutex);
	input.close();
	fclose(output1);
	fclose(output2);

}