//TYCOD214

#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t common;
pthread_mutex_t writerlock;
int readcount=0;

using namespace std;

class Account
{
	public:
		float balance;
		string name;
};

void* getBalance(void* user)		//reader
{
	pthread_mutex_lock(&writerlock);
	++readcount;
	cout<<"\nA reader has entered.\n";
	if(readcount==1)
		sem_wait(&common);
	pthread_mutex_unlock(&writerlock);
	Account *usr=(Account *) user;		//reading
	usleep(10);
	pthread_mutex_lock(&writerlock);
	--readcount;
	cout<<"\nA reader has exited.\n";
	if(readcount==0)
		sem_post(&common);
	pthread_mutex_unlock(&writerlock);
	pthread_exit(&(usr->balance));
}

void* deposit(void* user)		//writer
{
	cout<<"\nA writer is trying to enter.\n";
	sem_wait(&common);
	cout<<"\nA writer has entered.\n";
	Account *usr=(Account *) user;		//writing
	usr->balance+=100;
	sem_post(&common);
	cout<<"\nA writer has exited.\n";
	return NULL;
}

void* withdraw(void* user)		//writer
{
	cout<<"\nA writer is trying to enter.\n";
	sem_wait(&common);
	cout<<"\nA writer has entered.\n";
	Account *usr=(Account *) user;		//writing
	usr->balance-=100;
	sem_post(&common);
	cout<<"\nA writer has exited.\n";
	return NULL;
}

int main()
{
	pthread_t t2, t3;
	cout<<"\nEnter number of users: ";
	int unum, autoid=1;
	cin>>unum;
	pthread_t t1[unum];
	vector <Account> users;
	sem_init(&common, 0, 1);
	pthread_mutex_init(&writerlock, NULL);
	for(int i=0;i<unum;++i)
	{
		Account temp;
		cout<<"\nYour ID: "<<autoid;
		cout<<"\nEnter name: ";
		cin>>temp.name;
		cout<<"\nEnter balance: ";
		cin>>temp.balance;
		users.push_back(temp);
		++autoid;
	}
	int opt;
	while(true)
	{
		cout<<"\nMenu:";
		cout<<"\n1. Get Balance.";
		cout<<"\n2. Deposit 100Rs.";
		cout<<"\n3. Withdraw 100Rs.";
		cout<<"\n4. Exit.";
		cout<<"\nEnter choice: ";
		cin>>opt;
		switch(opt)
		{
			case 1:
			{
				cout<<"\nEnter ID: ";
				int eid;
				cin>>eid;
				if(eid>unum)
					cout<<"\nInvalid ID!";
				else
				{
					pthread_create(&t1[eid-1], NULL, getBalance, (void *)&users[eid-1]);
					float *bal;
					pthread_join(t1[eid-1], (void **)&bal);
					cout<<"\nBalance: "<<*bal<<" Rs."<<endl;
				}
				break;
			}
			
			case 2:
			{
				for(int i=0;i<unum;++i)
				{
					pthread_create(&t1[i], NULL, getBalance, (void *)&users[i]);
					pthread_create(&t2, NULL, deposit, (void *)&users[i]);
				}
				for(int i=0;i<unum;++i)
				{
					float *bal;
					pthread_join(t1[i], (void **)&bal);
					cout<<"\nBalance: "<<*bal<<" Rs."<<endl;
					pthread_join(t2, NULL);
				}
				break;
			}
			
			case 3:
			{
				for(int i=0;i<unum;++i)
				{
					pthread_create(&t1[i], NULL, getBalance, (void *)&users[i]);
					pthread_create(&t3, NULL, withdraw, (void *)&users[i]);
				}
				for(int i=0;i<unum;++i)
				{
					float *bal;
					pthread_join(t1[i], (void **)&bal);
					cout<<"\nBalance: "<<*bal<<" Rs."<<endl;
					pthread_join(t3, NULL);
				}
				break;
			}
			
			case 4:
				exit(0);
			
			default:
				cout<<"\nPlease enter a valid option.\n";
		}
	}
	return 0;
}

/*#include <semaphore.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

sem_t x,y;
pthread_t tid;
pthread_t wt[100],rt[100];
int rc = 0;

void *reader(void* param)
{
	sem_wait(&x);
	++rc;
	if(rc==1)
		sem_wait(&y);
	sem_post(&x);
    printf("%d reader is inside\n",rc);
    usleep(3);
    sem_wait(&x);
    --rc;
    if(rc==0)
        sem_post(&y);
    sem_post(&x);
    printf("%d Reader is leaving\n",rc+1);
    return NULL;
}

void *writer(void* param)
{
    printf("Writer is trying to enter\n");
    sem_wait(&y);
    printf("Writer has entered\n");
    sem_post(&y);
    printf("Writer is leaving\n");
    return NULL;
}

int main()
{
    int n2,i;
    printf("Enter the number of readers:");
    scanf("%d",&n2);
    printf("\n");
    int n1[n2];
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    for(i=0;i<n2;i++)
    {
        pthread_create(&wt[i],NULL,reader,NULL);
        pthread_create(&rt[i],NULL,writer,NULL);
    }
    for(i=0;i<n2;i++)
    {
        pthread_join(wt[i],NULL);
        pthread_join(rt[i],NULL);
    }
    return 0;
}
*/
