//TYCOD214

#include <bits/stdc++.h>

using namespace std;

void FCFS(int reqn, int cur_pos, vector <int> &requests)
{
	int seek_time=0;
	cout<<"FCFS Seek sequence: "<<cur_pos<<" ";
	for(int i=0; i<reqn; ++i)
	{
		cout<<requests[i]<<" ";
		seek_time+=abs(cur_pos-requests[i]);
		cur_pos=requests[i];
	}
	cout<<"\nSeek time: "<<seek_time<<endl;
}

void SSTF(int reqn, int cur_pos, vector <int> &requests)
{
	int seek_time=0;
	cout<<"SSTF Seek sequence: "<<cur_pos<<" ";
	vector <int> visit(reqn, 1);
	for(int i=0; i<reqn; ++i)
	{
		int mind=INT_MAX, mini;
		for(int j=0; j<reqn; ++j)
		{
			if(visit[j] and mind>abs(cur_pos-requests[j]))
			{
				mini=j;
				mind=abs(cur_pos-requests[j]);
			}
		}
		visit[mini]=0;
		cout<<requests[mini]<<" ";
		seek_time+=abs(cur_pos-requests[mini]);
		cur_pos=requests[mini];
	}
	cout<<"\nSeek time: "<<seek_time<<endl;
}

void SCAN(int maxd, int reqn, int cur_pos, vector <int> &requests)
{
	int seek_time=0;
	vector <int> before, after;
	for(int i=0; i<reqn; ++i)
	{
		if(requests[i]<=cur_pos)
			before.push_back(requests[i]);
		else
			after.push_back(requests[i]);
	}
	sort(before.begin(), before.end());
	reverse(before.begin(), before.end());
	sort(after.begin(), after.end());
	cout<<"SCAN Seek sequence: "<<cur_pos<<" ";
	for(int i=0; i<before.size(); ++i)
		cout<<before[i]<<" ";
	cout<<"0 ";
	seek_time+=cur_pos;
	for(int i=0; i<after.size(); ++i)
		cout<<after[i]<<" ";
	seek_time+=after[after.size()-1];
	cout<<"\nSeek time: "<<seek_time<<endl;
}

void C_SCAN(int maxd, int reqn, int cur_pos, vector <int> &requests)
{
	int seek_time=0;
	vector <int> before, after;
	for(int i=0; i<reqn; ++i)
	{
		if(requests[i]<cur_pos)
			before.push_back(requests[i]);
		else
			after.push_back(requests[i]);
	}
	sort(before.begin(), before.end());
	sort(after.begin(), after.end());
	cout<<"C-SCAN Seek sequence: "<<cur_pos<<" ";
	for(int i=0; i<after.size(); ++i)
		cout<<after[i]<<" ";
	cout<<maxd<<" ";
	seek_time+=abs(cur_pos-maxd);
	cout<<"0 ";
	seek_time+=abs(maxd);
	for(int i=0; i<before.size(); ++i)
		cout<<before[i]<<" ";
	seek_time+=before[before.size()-1];
	cout<<"\nSeek time: "<<seek_time<<endl;
}

int main()
{
	int reqn, cur_pos, maxd;
	vector <int> requests;
	cout<<"\nEnter the maximum range of disk: ";
	cin>>maxd;
	cout<<"\nEnter the number of requests: ";
	cin>>reqn;
	cout<<"\nEnter the current position of the head: ";
	cin>>cur_pos;
	cout<<"\nEnter requests: ";
	for(int i=0; i<reqn; ++i)
	{
		int t;
		cin>>t;
		requests.push_back(t);
	}
	while(true)
	{
		cout<<"\nMenu: ";
		cout<<"\n1. FCFS.";
		cout<<"\n2. SSTF.";
		cout<<"\n3. SCAN.";
		cout<<"\n4. C-SCAN.";
		cout<<"\n5. Exit";
		cout<<"\nEnter your choice: ";
		int ch;
		cin>>ch;
		switch(ch)
		{
			case 1:
				FCFS(reqn, cur_pos, requests);
				break;
			
			case 2:
				SSTF(reqn, cur_pos, requests);
				break;
			
			case 3:
				SCAN(maxd, reqn, cur_pos, requests);
				break;
			
			case 4:
				C_SCAN(maxd, reqn, cur_pos, requests);
				break;
			
			case 5:
				return 0;
		}
	}
	return 0;
}
