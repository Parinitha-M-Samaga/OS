//TYCOD214

#include <bits/stdc++.h>

using namespace std;

float avg_wait, avg_turnar;

class Process
{
	public:
		string name;
		int arrival, burst, finish, turn_around, waiting, rburst;
	Process()
	{
		turn_around=0;
		waiting=0;
	}
};

bool cond1(Process pr1, Process pr2)
{
	return pr1.arrival<pr2.arrival;
}

bool cond2(Process pr1, Process pr2)
{
	return pr1.rburst<pr2.rburst;
}

void gantt(vector <string> frgnt)
{
	cout<<endl<<endl;
	for(int i=1;i<frgnt.size();i+=2)
		cout<<"\t"<<frgnt[i]<<"\t";
	cout<<endl;
	for(int i=0;i<frgnt.size();i+=2)
		cout<<frgnt[i]<<"s\t\t";
	cout<<endl;
}

void pre_sjf(vector <Process> &process)
{
	int inctime=process[0].arrival, n=process.size(), ind=99999;
	vector <string> forgantt;
	vector <Process> temp;
	int x=n;
	while(x)
	{
		int ti=ind;
		for(int i=0;i<n;++i)
		{
			if(process[i].arrival<=inctime and process[i].rburst>0)
				temp.push_back(process[i]);
			else if(process[i].arrival>inctime)
				break;
		}
		if(temp.size())
		{
			sort(temp.begin(), temp.end(), cond2);
			for(int i=0;i<n;++i)
				if(temp[0].name==process[i].name)
					ind=i;
			--process[ind].rburst;
			if(process[ind].rburst==0)
			{
				--x;
				process[ind].finish=inctime+1;
				process[ind].turn_around=process[ind].finish-process[ind].arrival;
				process[ind].waiting=process[ind].turn_around-process[ind].burst;
			}
			if(ti!=ind)
			{
				forgantt.push_back(to_string(inctime));
				forgantt.push_back(process[ind].name);
			}
		}
		temp.clear();
		++inctime;
	}
	forgantt.push_back(to_string(inctime));
	cout<<"Gantt chart:\n";
	gantt(forgantt);
}

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
		inp.rburst=inp.burst;
		cout<<endl;
		process.push_back(inp);
		cout<<"Do you want to continue? (0/1): ";
		cin>>cont;
	}
	sort(process.begin(), process.end(), cond1);
	pre_sjf(process);
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
	return 0;
}
