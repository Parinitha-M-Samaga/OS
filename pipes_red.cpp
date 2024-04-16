//TYCOD214

#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <fcntl.h>

using namespace std;

int main()
{
	int fd[2], filedes1=open("input_file.txt", O_RDONLY), filedes2=open("output_file.txt", O_RDWR);
	try
	{
		if(filedes1==-1)
			throw(1);
		else if(filedes2==-1)
			throw(2);
	}
	catch(int err)
	{
		if(err==1)
			cout<<"\nInput text file cannot be opened!\n";
		else if(err==2)
			cout<<"\nOutput text file cannot be opened!\n";
		exit(0);
	}
	dup2(filedes1, fileno(stdin));
	dup2(filedes2, fileno(stdout));
	close(filedes1);
	pipe(fd);
	pid_t pid=fork();
	try
	{
		if(pid<0)
			throw(pid);
	}
	catch(pid_t pid)
	{
		cout<<"\nError in creating child process!\n";
		exit(0);
	}
	if(pid>0)
	{
		dup2(fd[0], fileno(stdin));
		close(filedes2);
		close(fd[0]);
		close(fd[1]);
		execl("/usr/bin/uniq", "uniq", (char*)0);
	}
	else if(pid==0)
	{
		dup2(fd[1], fileno(stdout));
		close(fd[0]);
		close(fd[1]);
		execl("/usr/bin/sort", "sort", (char*)0);
	}
	return 0;
}
