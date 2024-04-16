//TYCOD214

#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		if(argc<4)
			throw(1);
	}
	catch(int exc)
	{
		cout<<"\nEnter at least 4 arguments.\n";
		exit(0);
	}
	cout<<"\nParent process ID: "<<getpid()<<endl;
	while(true)
	{
		cout<<"\nMenu:"<<endl;
		cout<<"1. Copy file contents."<<endl;
		cout<<"2. Find sentences having a pattern."<<endl;
		cout<<"3. Exit."<<endl;
		cout<<"Enter option: ";
		int opt;
		cin>>opt;
		switch(opt)
		{
			case 1:
			{
				pid_t pid=fork();
				if(pid<0)
				{
					cout<<"\nInvalid process ID."<<endl;
					exit(0);
				}
				else if(pid==0)
				{
					//vector <const char*> args(argv[1], argv[2], NULL);
					//execvp("./cp", const_cast <char* const*> (args.data()));
					cout<<"\nChild process ID: "<<getpid()<<endl;
					execl("./cp", "./cp", argv[1], argv[2], (char*)0);
				}
				else
				{
					wait(NULL);
				}
				continue;
			}
			
			case 2:
			{
				pid_t pid=fork();
				if(pid<0)
				{
					cout<<"\nInvalid process ID."<<endl;
					exit(0);
				}
				else if(pid==0)
				{
					cout<<"\nChild process ID: "<<getpid()<<endl;
					execl("./grep", "./grep", argv[1], argv[3], (char*)0);
				}
				else
				{
					wait(NULL);
				}
				continue;
			}
			
			case 3:
			{
				cout<<"\nExiting.\n";
				exit(0);
			}
			
			default:
				cout<<"\nPlease enter a valid option.\n";
		}
	}
	return 0;
}
