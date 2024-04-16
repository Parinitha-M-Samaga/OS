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

bool cond(Process pr1, Process pr2)
{
	return pr1.arrival<pr2.arrival;
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

void rr2(vector <Process> &process, int quant)
{
	int inctime=process[0].arrival, n=process.size(), i=1;
	vector <string> forgantt;
	forgantt.push_back(to_string(inctime));
	queue <string> ready;
	ready.push(process[0].name);
	int x=n;
	while(x)
	{
		int temp=inctime, j;
		for(j=0;j<n;++j)
			if(process[j].name==ready.front())
				break;
		if(process[j].rburst>0 and process[j].rburst<=quant)
		{
			inctime+=process[j].rburst;
			process[j].rburst=0;
			process[j].finish=inctime;
			process[j].turn_around=process[j].finish-process[j].arrival;
			process[j].waiting=process[j].turn_around-process[j].burst;
			--x;
			ready.pop();
			forgantt.push_back(process[j].name);
			forgantt.push_back(to_string(inctime));
		}
		else if(process[j].rburst>quant)
		{
			inctime+=quant;
			process[j].rburst-=quant;
			forgantt.push_back(process[j].name);
			forgantt.push_back(to_string(inctime));
			if(i<n and process[i].arrival<=inctime)
			{
				while(i<n and process[i].arrival<=inctime)
				{
					ready.push(process[i].name);
					++i;
				}
			}
			ready.push(process[j].name);
			ready.pop();
		}
		if(temp==inctime)
			++inctime;
	}
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
	int cont=1, quant;
	cout<<"Time quantum: ";
	cin>>quant;
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
	sort(process.begin(), process.end(), cond);
	rr2(process, quant);
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
