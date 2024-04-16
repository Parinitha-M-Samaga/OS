#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		cout<<"Enter at least 3 arguments.\n";
		exit(0);
	}
	ifstream filein(argv[1]);
	if(!filein.is_open() or !filein.good())
	{
		cout<<"File does not exist.\n";
		exit(0);
	}
	string line, pattern=argv[2];
	size_t pos;
	int no=0;
	while(getline(filein, line))
	{
		++no;
		pos=line.find(pattern);
		if(pos!=string::npos)
			cout<<no<<". "<<line<<endl;
	}
	filein.close();
	return 0;
}
