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
long long nw, nr, kw, kr, l1=1, l2=1, read_count=0; //input parameters
double waiting_time_writers = 0, waiting_time_readers = 0; 
double avg_waiting_time_writers, avg_waiting_time_readers; //average waiting time for readers and writers
double max_waiting_time_readers=-1,max_waiting_time_writers=-1; //worst case waiting time to enter cs by thread
sem_t rw_mutex,mutex; //semaphores for reader writer lock and reader lock
default_random_engine generator1,generator2; //random number generator
exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
exponential_distribution<double> exponential2((double)1/(double)l2); //setting lambda values for exponential distribution

//writer code
void* writer(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	long long j;
	exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
	for(j=0;j<kw;j++)
	{
		//entry section
		struct timeval requestTime, endTime;
		gettimeofday(&requestTime,NULL);
		time_t currentTime1 = time(0); //getting current time
		tm *entryTime = localtime(&currentTime1);
		fprintf(output1,"%lldth Request by writer thread %lld at %.2d:%.2d:%.2d\n",j+1, id, entryTime->tm_hour, entryTime->tm_min, entryTime->tm_sec);
		sem_wait(&rw_mutex);

		//entering CS and performing writing
		time_t currentTime2 = time(0); //getting current time
		tm *CSentryTime = localtime(&currentTime2);
		fprintf(output1,"%lldth Entry by writer thread %lld at %.2d:%.2d:%.2d\n",j+1, id, CSentryTime->tm_hour, CSentryTime->tm_min, CSentryTime->tm_sec);
		gettimeofday(&endTime, NULL);
		if(max_waiting_time_writers<(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec)))
		{
			max_waiting_time_writers = (double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec));
		}
		waiting_time_writers+=(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec));//calculating waiting time by taking difference between the time at which thread entered CS and it made request
		usleep(exponential1(generator1)*1000); //simulate a thread writing in CS
		time_t currentTime3 = time(0); //getting current time
		tm *exitTime = localtime(&currentTime3);
		fprintf(output1,"%lldth Exit by writer thread %lld at %.2d:%.2d:%.2d\n",j+1, id, exitTime->tm_hour, exitTime->tm_min, exitTime->tm_sec);
		sem_post(&rw_mutex);
		
		//exit section
		usleep(exponential2(generator2)*1000); //simulate a thread exiting in exit section
	}
}

//reader code
void* reader(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	long long j;
	for(j=0;j<kr;j++)
	{
		//entry section
		struct timeval requestTime, endTime;
		gettimeofday(&requestTime,NULL);
		time_t currentTime1 = time(0); //getting current time
		tm *entryTime = localtime(&currentTime1);
		fprintf(output1,"%lldth Request by reader thread %lld at %.2d:%.2d:%.2d\n",j+1, id, entryTime->tm_hour, entryTime->tm_min, entryTime->tm_sec);
		
		sem_wait(&mutex);
		read_count++;
		if(read_count == 1)
			sem_wait(&rw_mutex);
		sem_post(&mutex);
		//performing reading
		time_t currentTime2 = time(0); //getting current time
		tm *CSentryTime = localtime(&currentTime2);
		fprintf(output1,"%lldth Entry by reader thread %lld at %.2d:%.2d:%.2d\n",j+1, id, CSentryTime->tm_hour, CSentryTime->tm_min, CSentryTime->tm_sec);
		gettimeofday(&endTime, NULL);
		if(max_waiting_time_readers<(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec)))
		{
			max_waiting_time_readers = (double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec));
		}
		waiting_time_readers+=(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec)); //calculating waiting time by taking difference between the time at which thread entered CS and it made request
		usleep(exponential1(generator1)*1000); //simulate a thread writing in CS
		time_t currentTime3 = time(0); //getting current time
		tm *exitTime = localtime(&currentTime3);
		fprintf(output1,"%lldth Exit by reader thread %lld at %.2d:%.2d:%.2d\n",j+1, id, exitTime->tm_hour, exitTime->tm_min, exitTime->tm_sec);
		sem_wait(&mutex);
		read_count--;
		if(read_count == 0)
			sem_post(&rw_mutex);
		sem_post(&mutex);
		//exit section
		usleep(exponential2(generator2)*1000); //simulate a thread exiting in exit section
	}
}

int main()
{
	input.open("inp-params.txt");
	output1 = fopen("RW-log.txt", "w");
	output2 = fopen("RW.txt", "w");
	input>>nw>>nr>>kw>>kr>>l1>>l2;
	sem_init(&rw_mutex,0,1); //initializing rw_mutex to 1
	sem_init(&mutex,0,1); //initializing mutex lock to 1 to provide mutual exclusion
	pthread_t writers[nw]; //writer threads
	pthread_t readers[nr]; //reader threads
	pthread_attr_t attr;
	pthread_attr_init(&attr); //setting attributes of threads
	//creating readers and writers
	for(long long i=0;i<max(nw,nr);i++)
	{
		if(i<nw)
			pthread_create(writers+i, &attr, writer, (void*)i);
		if(i<nr)
			pthread_create(readers+i, &attr, reader, (void*)i);
	}
	//joining threads
	for(long long i=0;i<nw;i++)
	{
		pthread_join(writers[i], NULL);
	}
	for(long long i=0;i<nr;i++)
	{
		pthread_join(readers[i], NULL);
	}
	//calculating average waiting time
	avg_waiting_time_writers = waiting_time_writers/kw;
	avg_waiting_time_readers = waiting_time_readers/kr;
	fprintf(output2,"Average waiting time for writer threads is %lf milliseconds\n",avg_waiting_time_writers*1000);
	fprintf(output2,"Average waiting time for reader threads is %lf milliseconds\n",avg_waiting_time_readers*1000);
	fprintf(output2,"Worst-case time taken by the writer threads to enter the CS is %lf milliseconds\n",max_waiting_time_writers*1000);
	fprintf(output2,"Worst-case time taken by the reader threads to enter the CS is %lf milliseconds\n",max_waiting_time_readers*1000);
	sem_destroy(&rw_mutex);
	sem_destroy(&mutex);
	input.close();
	fclose(output1);
	fclose(output2);
	return 0;
}