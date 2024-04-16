//TYCOD214

#include <bits/stdc++.h>

using namespace std;

void fifo(int dnum, int fnum, vector <int> &data)
{
	vector <int> fq;
	int counter=0, hit=0;
	for(int i:data)
	{
		if(find(fq.begin(), fq.end(), i)==fq.end())
		{
			if(fq.size()<fnum)
				fq.push_back(i);
			else
			{
				fq[counter]=i;
				if(counter==fnum-1)
					counter=0;
				else
					++counter;
			}
			cout<<endl<<i<<" FAULT     ";
		}
		else
		{
			cout<<endl<<i<<" HIT       ";
			++hit;
		}
		for(int j:fq)
			cout<<j<<" | ";
	}
	cout<<"\nHit ratio: "<<(float)hit/dnum;
	cout<<"\nFault ratio: "<<(float)(dnum-hit)/dnum;
}

void lru(int dnum, int fnum, vector <int> &data)
{
	deque <int> q(fnum);
	int hit=0;
	q.clear();
	for(int i:data) 
	{
		auto itr=find(q.begin(), q.end(), i);
		if(itr==q.end())
		{
			if(q.size()==fnum)
			{
				q.erase(q.begin());
				q.push_back(i);
			}
			else
				q.push_back(i);
			cout<<endl<<i<<" FAULT     ";
		}
		else
		{
			cout<<endl<<i<<" HIT       ";
			++hit;
			q.erase(itr);
			q.push_back(i);
		}
		for(int j:q)
			cout<<j<<" | ";
		cout<<endl;
	}
	cout<<"\nHit ratio: "<<(float)hit/dnum;
	cout<<"\nFault ratio: "<<(float)(dnum-hit)/dnum;
}

void opr(int dnum, int fnum, vector <int> &data)
{
	vector <int> oq;
	int hit=0;
	for(int i=0; i<dnum; ++i)
	{
		if(find(oq.begin(), oq.end(), data[i])==oq.end())
		{
			if(oq.size()<fnum)
				oq.push_back(data[i]);
			else
			{
				int far=i, ind=0;
				for(int j=0; j<fnum; ++j)
				{
					int k;
					for(k=i; k<dnum; ++k)
					{
						if(data[k]==oq[j])
						{
							if(k>far)
							{
								far=k;
								ind=j;
							}
							break;
						}
					}
					if(k==dnum)
					{
						ind=j;
						break;
					}
				}
				oq[ind]=data[i];
			}
			cout<<endl<<i<<" FAULT     ";
		}
		else
		{
			cout<<endl<<i<<" HIT       ";
			++hit;
		}
		for(int j:oq)
			cout<<j<<" | ";
	}
	cout<<"\nHit ratio: "<<(float)hit/dnum;
	cout<<"\nFault ratio: "<<(float)(dnum-hit)/dnum;
}

int main()
{
	while(true)
	{
		int dnum, fnum, choice;
		cout<<"\nMenu: ";
		cout<<"\n1. FIFO";
		cout<<"\n2. LRU";
		cout<<"\n3. Optimal";
		cout<<"\nEnter your choice (0 to exit): ";
		cin>>choice;
		if(choice==0)
			break;
		cout<<"\nEnter number of data: ";
		cin>>dnum;
		cout<<"\nEnter number of frames: ";
		cin>>fnum;
		vector <int> data(dnum);
		cout<<"\nEnter data: ";
		for(int i=0; i<dnum; ++i)
			cin>>data[i];
		if(choice==1)
			fifo(dnum, fnum, data);
		else if(choice==2)
			lru(dnum, fnum, data);
		else if(choice==3)
			opr(dnum, fnum, data);
		else
			cout<<"\nInvalid option.\n";
	}
	return 0;
}
