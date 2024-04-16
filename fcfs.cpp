//TYCOD214

#include <bits/stdc++.h>

using namespace std;

float avg_wait, avg_turnar;

class Process
{
	public:
		string name;
		int arrival, burst, finish, turn_around, waiting;
	Process()
	{
		turn_around=0;
		waiting=0;
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

void proc_sort(vector <Process> &process)
{
	if(process.size()>1)
	{
		int mid=process.size()/2;
		vector <Process> left, right;
		for(int i=0;i<mid;++i)
			left.push_back(process[i]);
		for(int i=mid;i<process.size();++i)
			right.push_back(process[i]);
		proc_sort(left);
		proc_sort(right);
		int i=0, j=0, k=0;
		while(i<left.size() and j<right.size())
		{
			if(left[i].arrival<=right[j].arrival)
			{
				process[k]=left[i];
				++i;
			}
			else
			{
				process[k]=right[j];
				++j;
			}
			++k;
		}
		while(i<left.size())
		{
			process[k]=left[i];
			++i;
			++k;
		}
		while(j<right.size())
		{
			process[k]=right[j];
			++j;
			++k;
		}
	}
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
	proc_sort(process);
	process[0].finish=process[0].arrival+process[0].burst;
	process[0].turn_around=process[0].finish-process[0].arrival;
	process[0].waiting=process[0].turn_around-process[0].burst;
	for(int i=1;i<process.size();++i)
	{
		if(process[i-1].finish<process[i].arrival)
			process[i].finish=process[i].arrival+process[i].burst;
		else
			process[i].finish=process[i-1].finish+process[i].burst;
		process[i].turn_around=process[i].finish-process[i].arrival;
		process[i].waiting=process[i].turn_around-process[i].burst;
	}
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
