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
FILE *output1,*output2;
long long capacity, np, nc, cntp, cntc, l1=1, l2=1, i; //input parameters
long long buffer[1000]; //shared buffer array
long long in = 0, out = 0, count = 0, pos;
double waiting_time_prod = 0,waiting_time_cons = 0;
double avg_waiting_time_prod, avg_waiting_time_cons; //average waiting time for producers and consumers
pthread_mutex_t m; //mutex lock
default_random_engine generator1,generator2; //random number generator

//producer code
void* producer(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	long long j;
	exponential_distribution<double> exponential1((double)1/(double)l1); //setting lambda values for exponential distribution
	for(j=0;j<cntp;j++)
	{
		//storing time at which thread made request to produce item
		struct timeval requestTime, endTime;
		gettimeofday(&requestTime,NULL);
		while(true)
		{
			//producing item
			long long produced_item = rand()%1000;

			pthread_mutex_lock(&m);
			//producer doesnt produce if buffer is full
			if(count==capacity)
			{
				pthread_mutex_unlock(&m);
			}
			else
			{
				buffer[in] = produced_item;
				if(in==capacity-1)
					pos=capacity;
				else
					pos=in+1;
				in = (in+1)%capacity;
				count++;
				time_t currentTime1 = time(0);
				tm *prodTime = localtime(&currentTime1);
				fprintf(output1,"%lldth item %lld produced by thread %lld at %.2d:%.2d:%.2d into buffer location %lld\n",j+1,produced_item,id,prodTime->tm_hour,prodTime->tm_min,prodTime->tm_sec,pos);
				gettimeofday(&endTime, NULL);
				waiting_time_prod+=(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec)); //adding the difference between time producer puts item in buffer and time when producer made request to put item
				pthread_mutex_unlock(&m);
				break;
			}
		}
		usleep(exponential1(generator1)*1000000); //sleeping for delay value t1
	}
}

//consumer code
void* consumer(void *threadId)
{
	long long id = (long long)threadId+1; //thread id
	long long j;
	exponential_distribution<double> exponential2((double)1/(double)l2); //setting lambda values for exponential distribution
	for(j=0;j<cntc;j++)
	{
		struct timeval requestTime, endTime;
		gettimeofday(&requestTime,NULL);
		while(true)
		{
			pthread_mutex_lock(&m);
			//consumer doesnt consume if buffer is empty
			if(count==0)
			{
				pthread_mutex_unlock(&m);
			}
			else
			{
				//cosnuming item
				long long consumed_item = buffer[out];
				if(out==capacity-1)
					pos=capacity;
				else
					pos=out+1;	
				out = (out+1)%capacity;
				count--;
				time_t currentTime2 = time(0);
				tm *consTime = localtime(&currentTime2);
				fprintf(output1,"%lldth item %lld consumed by thread %lld at %.2d:%.2d:%.2d into buffer location %lld\n",j+1,consumed_item,id,consTime->tm_hour,consTime->tm_min,consTime->tm_sec,pos);
				gettimeofday(&endTime, NULL);
				waiting_time_cons+=(double)((endTime.tv_usec-requestTime.tv_usec)*0.000001 + (endTime.tv_sec-requestTime.tv_sec)); //adding the difference between time consumer consumes item from buffer and time when consumer made request to consume item
				pthread_mutex_unlock(&m);
				break;
			}
		}
		usleep(exponential2(generator2)*1000000); //sleeping for delay value t2
	}
}

int main()
{
	input.open("inp-params.txt");
	output1 = fopen("locks.txt", "w");
	output2 = fopen("avgtimes-locks.txt", "w");
	input>>capacity>>np>>nc>>cntp>>cntc>>l1>>l2;
	pthread_mutex_init(&m,NULL); //initialzing mutex lock
	pthread_t producer_threads[np]; //producer threads 
	pthread_t consumer_threads[nc]; //consumer threads
	pthread_attr_t attr;
	pthread_attr_init(&attr); //setting attributes of threads
	srand(time(NULL)); //seeding for random number generator
	//creating consumer and producer threads
	for(long long i=0;i<max(np,nc);i++)
	{
		if(i<np)
			pthread_create(producer_threads+i, &attr, producer, (void*)i);
		if(i<nc)
			pthread_create(consumer_threads+i, &attr, consumer, (void*)i);
	}
	//joining threads
	for(int i=0;i<np;i++)
	{
		pthread_join(producer_threads[i], NULL);
	}
	for(int i=0;i<nc;i++)
	{
		pthread_join(consumer_threads[i], NULL);
	}
	//calculating average waiting time
	avg_waiting_time_cons = waiting_time_cons/cntc;
	avg_waiting_time_prod = waiting_time_prod/cntp;
	fprintf(output2,"Average waiting time for consumers is %lf seconds\n",avg_waiting_time_cons);
	fprintf(output2,"Average waiting time for producers is %lf seconds\n",avg_waiting_time_prod);
	input.close();
	fclose(output1);
	fclose(output2);
	return 0;
}