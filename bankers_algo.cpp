//TYCOD214

#include <bits/stdc++.h>

int pnum, rnum;

using namespace std;

bool safety(vector <int> work, vector <vector <int>> &allocation, vector <vector <int>> &need)
{
	vector <int> finish(pnum, 0), sseq;
	int i=0;
	while(i<pnum)
	{
		if(!finish[i])
		{
			int temp=0;
			for(int j=0; j<rnum; ++j)
				if(work[j]>=need[i][j])
					++temp;
				else
					break;
			if(temp==rnum)
			{
				sseq.push_back(i);
				for(int j=0; j<rnum; ++j)
					work[j]+=allocation[i][j];
				finish[i]=1;
				i=-1;
			}
		}
		++i;
	}
	int temp=1;
	for(int i:finish)
		temp&=i;
	if(temp)
	{
		cout<<"\nSafe Sequence: ";
		for(int i:sseq)
			cout<<"P"<<i<<"   ";
		cout<<endl;
		return true;
	}
	return false;
}

bool resourceRequest(int prc, vector <int> &request, vector <int> &available, vector <vector <int>> &allocation, vector <vector <int>> &need)
{
	for(int i=0; i<rnum; ++i)
		if(request[i]>need[prc][i] and request[i]>available[i])
			return false;
	for(int i=0; i<rnum; ++i)
	{
		available[i]-=request[i];
		allocation[prc][i]+=request[i];
		need[prc][i]-=request[i];
	}
	if(!safety(available, allocation, need))
	{
		for(int i=0; i<rnum; ++i)
		{
			available[i]+=request[i];
			allocation[prc][i]-=request[i];
			need[prc][i]+=request[i];
		}
		return false;
	}
	return true;
}

int main()
{
	cout<<"\nEnter number of resources: ";
	cin>>rnum;
	cout<<"\nEnter number of processes: ";
	cin>>pnum;
	vector <int> available(rnum);
	vector <vector <int>> maxall(pnum, (vector <int> (rnum))), allocation(pnum, (vector <int> (rnum))), need(pnum, (vector <int> (rnum)));
	for(int i=0; i<pnum; ++i)
	{
		cout<<"\nFor process "<<i<<":\n";
		for(int j=0; j<rnum; ++j)
		{
			cout<<"\nEnter allocation for resource "<<j<<": ";
			cin>>allocation[i][j];
			cout<<"\nEnter maximum allocation for resource "<<j<<": ";
			cin>>maxall[i][j];
			need[i][j]=maxall[i][j]-allocation[i][j];
		}
	}
	cout<<"\nEnter available resources: ";
	for(int i=0; i<rnum; ++i)
	{
		cout<<"\nFor resouce "<<i<<": ";
		cin>>available[i];
	}
	while(true)
	{
		int prc;
		vector <int> request(rnum);
		cout<<"\nEnter process number (-1 to exit): ";
		cin>>prc;
		if(prc==-1)
			break;
		for(int i=0; i<rnum; ++i)
		{
			cout<<"\nEnter requested instances of resource "<<i<<": ";
			cin>>request[i];
		}
		if(resourceRequest(prc, request, available, allocation, need))
			cout<<"Resource allocation is successful and leads to safe state.\n";
		else
			cout<<"Resource allocation is unsuccessful and leads to unsafe state.\n";
	}
	return 0;
}
