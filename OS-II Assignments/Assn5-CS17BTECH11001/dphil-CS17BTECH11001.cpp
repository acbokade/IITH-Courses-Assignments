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
long long n, h, l1, l2; //input parameters
pthread_mutex_t lock; //mutex lock for ensuring mutual exclusion between philosopher threads
pthread_cond_t *self; //conditional variables
enum states {THINKING, HUNGRY, EATING}; //states that a philosopher can be in 
states *state; 
double waiting_time = 0; //total waiting time for philosphers threads
double avg_waiting_time; //average waiting time for philosopher threads
double max_waiting_time = -1; //worst case waiting time to enter cs by philosopher thread
default_random_engine generator1,generator2; //random number generator
exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
exponential_distribution<double> exponential2((double)1/(double)l2); //setting lambda values for exponential distribution

// test if a philospher thread can acquire both chopsticks
void test(int i)
{
	if((state[(i+n-1)%n]!=EATING)&&(state[i]==HUNGRY)&&(state[(i+1)%n]!=EATING))
	{
		state[i]=EATING; 
		pthread_cond_signal(&self[i]); // signals the thread waiting for eating
	}
}

// function for picking (acquiring) up both chopsticks
void pickUp(int i)
{
	pthread_mutex_lock(&lock);
	state[i]=HUNGRY;
	test(i);
	if(state[i]!=EATING)
	{
		pthread_cond_wait(&self[i], &lock); // thread waits for the condition until another signals it
	}
	pthread_mutex_unlock(&lock);
}

// function for releasing both chopsticks
void putDown(int i)
{
	pthread_mutex_lock(&lock);
	state[i]=THINKING;
	test((i+1)%n); // checks if its left neighbour can take both chopsticks or not
	test((i+n-1)%n); // checks if its right neighbour can take both chopsticks or not
	pthread_mutex_unlock(&lock);
}

//philosopher's code
void* philosopher(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	long long j;
	exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
	for(j=0;j<h;j++)
	{
		//entry section
		struct timeval requestTime, endTime;
		gettimeofday(&requestTime,NULL);
		time_t currentTime1 = time(0); //getting current time
		tm *entryTime = localtime(&currentTime1);
		fprintf(output1,"%lldth eat request by thread %lld at %.2d:%.2d:%.2d\n",j+1, id, entryTime->tm_hour, entryTime->tm_min, entryTime->tm_sec);

		//pickup both chopsticks
		pickUp(id-1);

		//entering CS and performing writing
		time_t currentTime2 = time(0); //getting current time
		tm *CSentryTime = localtime(&currentTime2);
		fprintf(output1,"%lldth CS Entry by Philosopher thread %lld at %.2d:%.2d:%.2d\n",j+1, id, CSentryTime->tm_hour, CSentryTime->tm_min, CSentryTime->tm_sec);
		gettimeofday(&endTime, NULL);
		if(max_waiting_time<(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec)))
		{
			max_waiting_time = (double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec));
		}
		waiting_time+=(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec));//calculating waiting time by taking difference between the time at which thread entered CS and it made request
		usleep(exponential1(generator1)*1000); //simulate a thread writing in CS
				
		//putdown both the chopsticks
		putDown(id-1);

		time_t currentTime3 = time(0); //getting current time
		tm *exitTime = localtime(&currentTime3);
		fprintf(output1,"%lldth Exit by Philosopher thread %lld at %.2d:%.2d:%.2d\n",j+1, id, exitTime->tm_hour, exitTime->tm_min, exitTime->tm_sec);
		//exit section
		usleep(exponential2(generator2)*1000); //simulate a thread exiting in exit section
	}
}

int main()
{
	input.open("inp-params.txt");
	output1 = fopen("dphil-log.txt", "w");
	output2 = fopen("Time.txt", "w");
	input>>n>>h>>l1>>l2;
	pthread_t philosophers[n]; //philosopher threads
	pthread_attr_t attr;
	pthread_attr_init(&attr); //setting attributes of philospher threads

	state = new states[n];
	self = new pthread_cond_t[n];

	for(long long i=0;i<n;i++)
	{
		pthread_cond_init(&self[i],NULL);
		state[i] = THINKING;
	}

	pthread_mutex_init(&lock, NULL);

	//creating philosopher threads
	for(long long i=0;i<n;i++)
	{
		pthread_create(philosophers+i, &attr, philosopher, (void*)i);
	}
	//joining philosopher threads
	for(long long i=0;i<n;i++)
	{
		pthread_join(philosophers[i], NULL);
	}

	//calculating average waiting time
	avg_waiting_time = waiting_time/n;
	fprintf(output2,"Average waiting time for philosopher threads is %lf milliseconds\n",avg_waiting_time*1000);
	fprintf(output2,"Worst-case time taken by the philosopher threads to enter the CS is %lf milliseconds\n",max_waiting_time*1000);
	input.close();
	fclose(output1);
	fclose(output2);
	pthread_mutex_destroy(&lock); // destroying lock
	for(long long i=0;i<n;i++) // destroying conditional variables
		pthread_cond_destroy(&self[i]);
	return 0;
}