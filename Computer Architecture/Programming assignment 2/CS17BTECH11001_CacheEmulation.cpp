#include <bits/stdc++.h>
using namespace std;

int stringToInteger(string s)
{
	int ans=0,i;
	for(i=0;i<s.length();i++)
	{
		ans=ans*10+(s[i]-48);
	}
	return ans;
}

int main(int argc,char *argv[])
{
	int noOfEntries = stringToInteger(argv[3]);
	string replacement_type=argv[1];
	string file_to_open=argv[2];
	int l=file_to_open.length();
	file_to_open=file_to_open.erase(l-4,l);
	string s;
	vector<string>::iterator it;
	vector<string>::iterator it1;
	vector<string>::iterator it2;
	vector<string>::iterator it3;
	//declarations
	int lru_hits=0;
	int lru_misses=0;
	int lru_count=0;
	int lru_compulsory_misses=0;
	int lru_capacity_misses=0;
	int lru_accesses=0;
	vector<string>lru_unique_addresses;
	vector<string>lru_output;
	vector<string>lru_v;

	int fifo_hits=0;
	int fifo_misses=0;
	int fifo_count=0;
	int fifo_compulsory_misses=0;
	int fifo_capacity_misses=0;
	int fifo_accesses=0;
	vector<string>fifo_unique_addresses;
	vector<string>fifo_output;
	vector<string>fifo_v;

	int optimal_hits=0;
	int optimal_misses=0;
	int optimal_count=0;
	int optimal_compulsory_misses=0;
	int optimal_capacity_misses=0;
	int optimal_accesses=0;
	vector<string>optimal_unique_addresses;
	vector<string>optimal_output;
	vector<string>optimal_v;

	ofstream lru_outputfile;
	ofstream fifo_outputfile;
	ofstream optimal_outputfile;

	//FIFO
	if(replacement_type=="FIFO")
	{
		ifstream outfile(argv[2]);
		fifo_outputfile.open("CS17BTECH11001_"+replacement_type+"_"+file_to_open+"_"+argv[3]+".out");

		while(outfile>>s)
		{
			if(fifo_count<noOfEntries)
			{
				it=find(fifo_v.begin(),fifo_v.end(),s);
				//miss			
				if(it==fifo_v.end())
				{
					fifo_v.push_back(s);
					fifo_unique_addresses.push_back(s);
					fifo_compulsory_misses+=1;
					fifo_misses+=1;
					fifo_output.push_back("MISS");
					fifo_count++;
				}
				//hit
				else
				{
					fifo_hits+=1;
					fifo_output.push_back("HIT");
				}
			}
			else
			{
				it=find(fifo_v.begin(),fifo_v.end(),s);
				//miss
				if(it==fifo_v.end())
				{
					//find whether it is compulsory or not
					it=find(fifo_unique_addresses.begin(), fifo_unique_addresses.end(),s);
					if(it==fifo_unique_addresses.end()) //compulsory miss
					{
						fifo_compulsory_misses+=1;
						fifo_unique_addresses.push_back(s);
					}
					fifo_v.erase(fifo_v.begin());
					fifo_v.push_back(s);
					fifo_misses+=1;
					fifo_output.push_back("MISS");
					fifo_count++;
				}
				//hit
				else
				{
					fifo_hits+=1;
					fifo_output.push_back("HIT");
				}
			}
			fifo_accesses++;
		}
		fifo_capacity_misses=fifo_misses-fifo_compulsory_misses;

		fifo_outputfile<<"TOTAL_ACCESSES = "<<fifo_accesses<<endl;
		fifo_outputfile<<"TOTAL_MISSES = "<<fifo_misses<<endl;
		fifo_outputfile<<"COMPULSORY_MISSES = "<<fifo_compulsory_misses<<endl;
		fifo_outputfile<<"CAPACITY_MISSES = "<<fifo_capacity_misses<<endl;
		for(it=fifo_output.begin();it!=fifo_output.end();it++)
		{
			fifo_outputfile<<*it<<endl;
		}	
	}

	else if(replacement_type=="LRU")
	{
		ifstream outfile(argv[2]);
		lru_outputfile.open("CS17BTECH11001_"+replacement_type+"_"+file_to_open+"_"+argv[3]+".out");

		while(outfile>>s)
		{
			if(lru_count<noOfEntries)
			{
				it=find(lru_v.begin(),lru_v.end(),s);
				//miss			
				if(it==lru_v.end())
				{
					lru_compulsory_misses+=1;
					lru_unique_addresses.push_back(s);
					lru_v.push_back(s);
					lru_misses+=1;
					lru_output.push_back("MISS");
					lru_count++;
				}
				//hit
				else
				{
					lru_v.erase(it);
					lru_v.push_back(s);
					lru_hits+=1;
					lru_output.push_back("HIT");
				}
			}
			else
			{
				it=find(lru_v.begin(),lru_v.end(),s);
				//miss
				if(it==lru_v.end())
				{
					it=find(lru_unique_addresses.begin(), lru_unique_addresses.end(),s);
					if(it==lru_unique_addresses.end()) //compulsory miss
					{
						lru_compulsory_misses+=1;
						lru_unique_addresses.push_back(s);
					}
					lru_v.erase(lru_v.begin());
					lru_v.push_back(s);
					lru_misses+=1;
					lru_output.push_back("MISS");
					lru_count++;
				}
				//hit
				else
				{
					lru_v.erase(it);
					lru_v.push_back(s);
					lru_hits+=1;
					lru_output.push_back("HIT");
				}
			}
			lru_accesses++;
		}

		lru_capacity_misses=lru_misses-lru_compulsory_misses;
		lru_outputfile<<"TOTAL_ACCESSES = "<<lru_accesses<<endl;
		lru_outputfile<<"TOTAL_MISSES = "<<lru_misses<<endl;
		lru_outputfile<<"COMPULSORY_MISSES = "<<lru_compulsory_misses<<endl;
		lru_outputfile<<"CAPACITY_MISSES = "<<lru_capacity_misses<<endl;
		for(it=lru_output.begin();it!=lru_output.end();it++)
		{
				lru_outputfile<<*it<<endl;
		}	
	}

	else if(replacement_type=="OPTIMAL")
	{
		ifstream outfile(argv[2]);
		lru_outputfile.open("CS17BTECH11001_"+replacement_type+"_"+file_to_open+"_"+argv[3]+".out");
		vector<string>addresses;

		while(outfile>>s)
		{
			addresses.push_back(s);
		}

		for(it=addresses.begin();it!=addresses.end();it++) //optimal_accesses=addresses.size()
		{
			if(optimal_count<noOfEntries)
			{
				it1=find(optimal_v.begin(),optimal_v.end(),*it);
				//miss
				if(it1==optimal_v.end())
				{
					optimal_v.push_back(*it);
					optimal_compulsory_misses++;
					optimal_count++;
					optimal_output.push_back("MISS");
				}
				//hit
				else
				{
					optimal_hits++;
					optimal_output.push_back("HIT");
				}			
			}
			else
			{
				it1=find(optimal_v.begin(),optimal_v.end(),*it);
				//miss
				if(it1==optimal_v.end())
				{
					int farthest=INT_MIN;
					int index;
					for(it1=optimal_v.begin();it1!=optimal_v.end();it1++)
					{
						it2=find(it+1,addresses.end(),*it1);
						if(it2==addresses.end())
						{
							it3=it1;//address which is to be replaced
							break;
						}
						else
						{
							index=it2-addresses.begin()+1;
							if(index>farthest)
							{
								farthest=index;
								it3=it1;
							}
						}
					}
					optimal_v.erase(it3);
					optimal_v.push_back(*it1);
					optimal_misses++;
					optimal_output.push_back("MISS");
				}
				//hit
				else
				{
					optimal_hits++;
					optimal_output.push_back("hit");
				}
			}
		}

		optimal_capacity_misses=optimal_misses-optimal_compulsory_misses;
		optimal_outputfile<<"TOTAL_ACCESSES = "<<optimal_accesses<<endl;
		optimal_outputfile<<"TOTAL_MISSES = "<<optimal_misses<<endl;
		optimal_outputfile<<"COMPULSORY_MISSES = "<<optimal_compulsory_misses<<endl;
		optimal_outputfile<<"CAPACITY_MISSES = "<<optimal_capacity_misses<<endl;
		for(it=optimal_output.begin();it!=optimal_output.end();it++)
		{
				optimal_outputfile<<*it<<endl;
		}

	}

	return 0;
}