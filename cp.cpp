#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		if(argc<3)
			throw(argc);
	}
	catch(int argc)
	{
		cout<<"Number of parameters should be at least 3.";
		exit(0);
	}
	/*FILE *filein, *fileout;
	filein=fopen(argv[1], "r");
	fileout=fopen(argv[2], "w");*/
	ifstream filein(argv[1]);
	ofstream fileout(argv[2]);
	string line;
	try
	{
		if((!filein.is_open()) or (!filein.good()))
			throw(1);
			
	}
	catch(int exc)
	{
		if(exc==1)
			cout<<"File to read from does not exist."<<endl;
		exit(0);
	}
	while(getline(filein, line))
	{
		fileout<<line<<endl;
	}
	filein.close();
	fileout.close();
	cout<<"Copying completed."<<endl;
	return 0;
}
