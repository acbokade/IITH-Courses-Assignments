//Ajinkya Bokade
#include <bits/stdc++.h>
using namespace std;

//class for process
class Process{
public:
	string pid;
	long cpu_burst;
	long period;
	long deadline;
	long frequency;
	long remaining_time;
	long arrival_time;
};

//for sorting ready queue
bool sortbyfirst(const pair<long,Process> &a, const pair<long,Process> &b) 
{ 
    return (a.first < b.first);
} 
//to get process object from its pid
unordered_map<string,Process>getProcess;

//for sorting event timestamp
bool sortbyPeriod(const pair<long,string> &a, const pair<long,string> &b)
{
	if (a.first==b.first)
		return getProcess[a.second].deadline<getProcess[b.second].deadline;
	return a.first<b.first;
}

int main()
{
	ifstream input;
	ofstream output1, output2;
	long processes,i,j,flag=0;
	long deadlines_missed=0;
	long total_processes=0;
	long successes=0;
	double avg_waiting_time=0;
	input.open("inp-params.txt");
	output1.open("EDF-Log.txt");
	output2.open("EDF-Stats.txt");
	input>>processes;
	vector< pair<long,Process> >ready_queue;
	vector< pair<long,Process> >::iterator iter;
	unordered_map<string,long>instances; //which instance of process is running, used for checking deadline
	unordered_map<string,double>waiting_time; //waiting time of each process
	//initializing processes
	for(i=0;i<processes;i++)
	{
		Process p;
		input>>p.pid;
		input>>p.cpu_burst;
		input>>p.period;
		input>>p.frequency;
		p.frequency-=1;
		p.remaining_time=p.cpu_burst;
		p.deadline=p.period;
		p.arrival_time=0;
		total_processes+=(p.frequency+1);
		ready_queue.push_back(make_pair(p.period,p));
		getProcess[p.pid]=p;
		instances[p.pid]=1;
		waiting_time[p.pid]=0;
		output1<<"Process "<<p.pid<<": processing time="<<p.cpu_burst<<"; deadline:"<<p.deadline<<"; period:"<<p.period<<" joined the system at time 0."<<endl;
	}
	long current_time=0;//current time
	vector<pair<long,string>>event_timestamp;//event queue
	//insertion of all events into event queue//sorting event queue
	for(auto it:ready_queue)
	{
		for(j=1;j<=it.second.frequency;j++)
		{
			event_timestamp.push_back(make_pair(j*it.first,it.second.pid));
		}
	}
	sort(event_timestamp.begin(),event_timestamp.end(),sortbyPeriod);//sorting event queue
	vector<pair<long,string>>::iterator it=event_timestamp.begin();
	//running loop until all events are finished and ready is empty
	while(it!=event_timestamp.end()||!(ready_queue.empty()))
	{
		//add next process to ready queue if it is empty
		if(ready_queue.empty())
		{
			if(it->first-current_time!=0)
				output1<<"CPU is idle till time "<<it->first<<endl;
			current_time=it->first;
			//adding process to ready queue
			Process new_process=getProcess[it->second];
			new_process.arrival_time=it->first;
			instances[new_process.pid]+=1;
			new_process.deadline=instances[new_process.pid]*new_process.period;
			ready_queue.push_back(make_pair(new_process.deadline,new_process));
			it++;
		}
		//sorting ready queue to get high priority process
		sort(ready_queue.begin(),ready_queue.end(),sortbyfirst);
		Process p=ready_queue.begin()->second;
		if(flag==0)
		{
			waiting_time[p.pid]+=current_time-ready_queue.begin()->second.arrival_time;
			if(p.remaining_time==p.cpu_burst)
				output1<<"Process "<<ready_queue.begin()->second.pid<<" starts execution at time "<<current_time<<"."<<" "<<endl; 
			else
				output1<<"Process "<<ready_queue.begin()->second.pid<<" resumes execution at time "<<current_time<<"."<<endl;
		} 
		//if events are still present
		if(it!=event_timestamp.end())
		{
			//if current process is missing deadline at that time 
			if(current_time==p.deadline)
			{
				deadlines_missed+=1;
				current_time=ready_queue.begin()->second.deadline;
				output1<<"Process "<<ready_queue.begin()->second.pid<<" misses its deadline at time "<<current_time<<"."<<endl;
				ready_queue.erase(ready_queue.begin());
				flag=0;
			}
			// no event is occuring in between
			else if(current_time+ready_queue.begin()->second.remaining_time<it->first)
			{
				if(current_time+ready_queue.begin()->second.remaining_time>ready_queue.begin()->second.deadline)
				{
					deadlines_missed+=1;
					current_time=ready_queue.begin()->second.deadline;
					output1<<"Process "<<ready_queue.begin()->second.pid<<" misses its deadline at time "<<current_time<<"."<<endl;
					ready_queue.erase(ready_queue.begin());
					flag=0;
				}
				else
				{
					flag=0;
					current_time+=ready_queue.begin()->second.remaining_time;
					successes+=1;
					output1<<"Process "<<ready_queue.begin()->second.pid<<" finishes execution at time "<<current_time<<"."<<endl;
					ready_queue.erase(ready_queue.begin());
				}
			}
			//event is occuring at the same as the process completion time
			else if(current_time+p.remaining_time==it->first)
			{
				flag=0;
				current_time+=ready_queue.begin()->second.remaining_time;
				successes+=1;
				output1<<"Process "<<ready_queue.begin()->second.pid<<" finishes execution at time "<<current_time<<"."<<endl;
				ready_queue.erase(ready_queue.begin());
				//adding the process in the queue
				Process new_process=getProcess[it->second];
				instances[new_process.pid]+=1;
				new_process.deadline=instances[new_process.pid]*new_process.period;
				new_process.arrival_time=it->first;
				for(iter=ready_queue.begin();iter!=ready_queue.end();iter++)
				{
					//instance of new process is already present in ready queue hence it missed deadline and thus removing it from queue
					if(iter->second.pid==new_process.pid)
					{
						deadlines_missed+=1;
						output1<<"Process "<<new_process.pid<<" misses its deadline at time "<<iter->second.deadline<<"."<<endl;
						waiting_time[new_process.pid]+=iter->second.deadline-iter->second.arrival_time;
						break;
					}
					if(p.pid==new_process.pid)
						flag=0;
				}
				//erasing that process from queue;
				if(iter!=ready_queue.end())
					ready_queue.erase(iter);
				ready_queue.push_back(make_pair(new_process.deadline,new_process));
				it++;
			}
			//event occurs in between 
			else
			{
				Process new_process=getProcess[it->second];
				instances[new_process.pid]+=1;
				new_process.deadline=instances[new_process.pid]*new_process.period;
				//new process has high priority
				if(new_process.deadline<p.deadline)
				{
					flag=0;
					//old process gets preempted
					long processingTime=it->first-current_time;
					current_time=it->first;
					(ready_queue.begin())->second.remaining_time-=processingTime;
					(ready_queue.begin())->second.arrival_time=current_time;
					new_process.arrival_time=current_time;
					output1<<"Process "<<ready_queue.begin()->second.pid<<" is preempted by Process "<<it->second<<" at time "<<current_time<<". Remaining processing time:"<<ready_queue.begin()->second.remaining_time<<"."<<endl;
					//add new process in ready queue
					new_process.arrival_time=it->first;
					for(iter=ready_queue.begin();iter!=ready_queue.end();iter++)
					{
						//new process is already present in ready queue hence it missed deadline and thus removing it from queue
						if(iter->second.pid==new_process.pid)
						{
							deadlines_missed+=1;
							output1<<"Process "<<new_process.pid<<" misses its deadline at time "<<iter->second.deadline<<"."<<endl;
							if(new_process.pid!=p.pid)
								waiting_time[new_process.pid]+=iter->second.deadline-iter->second.arrival_time;
							break;
						}
						if(p.pid==new_process.pid)
						{
							current_time=iter->second.deadline;
							flag=0;
						}
					}
					//erasing that process from queue;
					if(iter!=ready_queue.end())
						ready_queue.erase(iter);
					ready_queue.push_back(make_pair(new_process.deadline,new_process));
				}
				//new process has low priority
				else
				{
					flag=1;
					if(new_process.pid==p.pid)
						flag=0;
					new_process.arrival_time=it->first;
					for(iter=ready_queue.begin();iter!=ready_queue.end();iter++)
					{
						//instance of new process is already present in ready queue hence it missed deadline and thus removing it from queue
						if(iter->second.pid==new_process.pid)
						{
							deadlines_missed+=1;
							output1<<"Process "<<new_process.pid<<" misses its deadline at time "<<iter->second.deadline<<"."<<endl;
							if(p.pid!=new_process.pid)
								waiting_time[new_process.pid]+=iter->second.deadline-iter->second.arrival_time;
							break;
						}
						if(p.pid==new_process.pid)
						{
							current_time=iter->second.deadline;
							flag=0;
						}
					}
					//erasing that process from queue;
					if(iter!=ready_queue.end())
						ready_queue.erase(iter);
					ready_queue.push_back(make_pair(new_process.deadline,new_process));
					//running old process till event timestamp
					if(new_process.pid!=p.pid)
					{
						long processingTime=it->first-current_time;
						current_time=it->first;
						(ready_queue.begin())->second.remaining_time-=processingTime;
					}
					else if(new_process.pid==p.pid)
						current_time=it->first;
				}
				it++;
			}
		} 
		//processes are present only in ready queue and no event is left
		else
		{	
			//current process is missing its deadline
			if(current_time+p.remaining_time>p.deadline && current_time<=p.deadline)
			{
				current_time=p.deadline;
				deadlines_missed+=1;
				output1<<"Process "<<p.pid<<" misses its deadline at time "<<current_time<<"."<<endl;
				waiting_time[p.pid]+=current_time-p.arrival_time;
				ready_queue.erase(ready_queue.begin());
				flag=0;
			}
			//current process is missing its deadline
			else if(current_time > p.deadline)
			{
				deadlines_missed+=1;
				output1<<"Process "<<p.pid<<" misses its deadline at time "<<current_time<<"."<<endl;
				waiting_time[p.pid]+=current_time-p.arrival_time;
				ready_queue.erase(ready_queue.begin());
				flag=0;
			}
			//running current process upto its completion
			else
			{
				current_time+=p.remaining_time;
				ready_queue.erase(ready_queue.begin());
				successes+=1;
				output1<<"Process "<<p.pid<<" finishes execution at time "<<current_time<<"."<<endl;
				flag=0;
			}	
		}
	}
	//calculating average waiting time
	for(auto it:getProcess)
	{
		//cout<<"Average waiting time for Process P"<<it.first<<": "<<waiting_time[it.first]<<endl;
		avg_waiting_time+=waiting_time[it.first];
	}
	avg_waiting_time/=total_processes;
	output2<<"Number of processes that came into system: "<<total_processes<<endl;
	output2<<"Number of processes that successfully complete: "<<successes<<endl;
	output2<<"Number of processes that missed their deadlines: "<<deadlines_missed<<endl;
	output2<<"Average waiting time: "<<avg_waiting_time<<endl;
	input.close();
	output1.close();
	output2.close();
	return 0;
}