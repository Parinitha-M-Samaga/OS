//TYCOD214

#include <bits/stdc++.h>

using namespace std;

float avg_wait, avg_turnar;

class Process
{
	public:
		string name;
		int arrival, burst, finish, turn_around, waiting, exe, turn;
	Process()
	{
		turn_around=0;
		waiting=0;
		exe=0;
	}
};

void calculate(vector <Process> &process)
{
	float sumwt=0, sumta=0;
	for(auto pr: process)
	{
		sumwt+=pr.waiting;
		sumta+=pr.turn_around;
	}
	cout<<endl<<"Average Waiting time: "<<(float)(sumwt)/process.size()<<"s"<<endl;
	cout<<"Average Turn around time: "<<(float)(sumta)/process.size()<<"s"<<endl;
}

bool cond1(Process pr1, Process pr2)
{
	return pr1.burst<pr2.burst;
}

bool cond2(Process pr1, Process pr2)
{
	return pr1.turn<pr2.turn;
}

void sjf(vector <Process> &process)
{
	int min=9999, bt=9999, ind, ct=0;
	for(int i=0;i<process.size();++i)
		if(process[i].arrival<min and process[i].burst<bt)
		{
			min=process[i].arrival;
			bt=process[i].burst;
			ind=i;
		}
	ct+=process[ind].burst;
	process[ind].finish=ct;
	process[ind].turn_around=process[ind].finish-process[ind].arrival;
	process[ind].waiting=process[ind].turn_around-process[ind].burst;
	process[ind].exe=1;
	process[ind].turn=1;
	vector <Process> next;
	int nind=2;
	while(nind<=process.size())
	{
		for(int i=0;i<process.size();++i)
			if(process[i].arrival<=ct and process[i].exe==0)
				next.push_back(process[i]);
		if(next.size()==0)
		{
			min=9999; bt=9999;
			for(int i=0;i<process.size();++i)
				if(process[i].exe==0 and process[i].arrival<=min and process[i].burst<bt)
				{
					min=process[i].arrival;
					bt=process[i].burst;
					ind=i;
				}
			ct+=(process[ind].arrival-ct);
		}
		else
		{
			sort(next.begin(), next.end(), cond1);
			for(int i=0;i<process.size();++i)
				if(next[0].name==process[i].name)
				{
					ind=i;
					break;
				}
		}
		ct+=process[ind].burst;
		process[ind].finish=ct;
		process[ind].turn_around=process[ind].finish-process[ind].arrival;
		process[ind].waiting=process[ind].turn_around-process[ind].burst;
		process[ind].exe=1;
		process[ind].turn=nind;
		++nind;
		next.clear();
	}
	sort(process.begin(), process.end(), cond2);
}

void gantt(vector <Process> &process)
{
	cout<<endl<<endl;
	for(auto pr:process)
		cout<<"\t"<<pr.name<<"\t";
	cout<<endl<<process[0].arrival<<"s\t";
	for(auto pr:process)
		cout<<"\t"<<pr.finish<<"s\t";
	cout<<endl;
}

int main()
{
	vector <Process> process;
	int cont=1;
	while(cont)
	{
		Process inp;
		cout<<"\n\nEnter process name: ";
		cin>>inp.name;
		cout<<"\nEnter arrival time: ";
		cin>>inp.arrival;
		cout<<"\nEnter burst time: ";
		cin>>inp.burst;
		process.push_back(inp);
		cout<<"\nDo you want to continue? (0/1): ";
		cin>>cont;
	}
	sjf(process);
	cout<<endl;
	cout<<"Process name"<<"\t";
	cout<<"Arrival time"<<"\t";
	cout<<"Burst time"<<"\t";
	cout<<"Finish time"<<"\t";
	cout<<"Turn around time"<<"\t";
	cout<<"Waiting time"<<endl;
	for(auto pr: process)
	{
		cout<<pr.name<<"\t\t";
		cout<<pr.arrival<<"\t\t";
		cout<<pr.burst<<"\t\t";
		cout<<pr.finish<<"\t\t";
		cout<<pr.turn_around<<"\t\t\t";
		cout<<pr.waiting<<endl;
	}
	calculate(process);
	cout<<"Gantt chart:\n";
	gantt(process);
	return 0;
}
