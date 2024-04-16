#include <iostream>
#include <limits>
using namespace std;


struct MemoryBlock
{
	int size;
	bool allocated;
	MemoryBlock* next;
	string process;
	MemoryBlock(int s) : size(s), allocated(false), next(nullptr)
	{}
};

class MemoryManager
{
	private:
		MemoryBlock* head;
		MemoryBlock* current;

	public:
	MemoryManager()
	{
		head=nullptr;
		current=nullptr;
	}
   
   
	void addBlock(int size)
	{
		MemoryBlock* newBlock=new MemoryBlock(size);
		if (!head)
			head=newBlock;
		else
		{
			MemoryBlock* temp=head;
			while(temp->next)
				temp=temp->next;
			temp->next=newBlock;
		}
	}
	   

	void firstFit() 
	{
		cout<<"\nEnter number of processes: ";
		int pnum;
		cin>>pnum;
		for(int i=0; i<pnum; ++i)
		{
			cout<<"\nEnter process block: ";
			int t;
			cin>>t;
			MemoryBlock* temp=head;
			int flag=0;
			while(temp)
			{
				if(!temp->allocated and temp->size>=t) 
				{
					temp->allocated=true;
					int memsize=temp->size;
					temp->size=t;
					temp->process=("P_"+to_string(t));
					flag=1;
					cout<<"Memory allocated using First Fit\n";
					if(memsize-t)
					{
						MemoryBlock* newBlock=new MemoryBlock(memsize-t);
						newBlock->next=temp->next;
						temp->next=newBlock;
						current=newBlock;
					}
					else
					{
						if(temp->next)
							current=temp->next;
						else
							current=head;
					}
					break;
				}
				temp=temp->next;
			}
			if(!flag)
				cout<<"Memory allocation failed using First Fit\n";
		}
	}
	
	void bestFit()
	{
		cout<<"\nEnter number of processes: ";
		int pnum;
		cin>>pnum;
		for(int i=0; i<pnum; ++i)
		{
			cout<<"\nEnter process block: ";
			int t, flag=0;
			cin>>t;
			MemoryBlock* temp=head, *smallest=nullptr;
			while(temp)
			{
				if(!temp->allocated and temp->size>=t) 
				{
					if(!smallest)
						smallest=temp;
					else if((smallest->size)>(temp->size))
						smallest=temp;
				}
				temp=temp->next;
			}
			if(smallest)
			{
				smallest->allocated=true;
				int memsize=smallest->size;
				smallest->size=t;
				smallest->process=("P_"+to_string(t));
				flag=1;
				cout<<"Memory allocated using Best Fit\n";
				if(memsize-t)
				{
					MemoryBlock* newBlock=new MemoryBlock(memsize-t);
					newBlock->next=smallest->next;
					smallest->next=newBlock;
					current=newBlock;
				}
				else
				{
					if(temp->next)
						current=temp->next;
					else
						current=head;
				}
				break;
			}
			if(!flag)
				cout<<"Memory allocation failed using Best Fit\n";
		}
	}
	
	void nextFit()
	{
		cout<<"\nEnter number of processes: ";
		int pnum;
		cin>>pnum;
		for(int i=0; i<pnum; ++i)
		{
			cout<<"\nEnter process block: ";
			int t, flag=0;
			cin>>t;
			if(!current)
				current=head;
			MemoryBlock* temp=current;
			int f=1;
			while(temp!=current or f)
			{
				if(f)
					f=0;
				if(!temp->allocated and temp->size>=t) 
				{
					temp->allocated=true;
					int memsize=temp->size;
					temp->size=t;
					temp->process=("P_"+to_string(t));
					flag=1;
					cout<<"Memory allocated using Next Fit\n";
					if(memsize-t)
					{
						MemoryBlock* newBlock=new MemoryBlock(memsize-t);
						newBlock->next=temp->next;
						temp->next=newBlock;
						current=newBlock;
					}
					else
					{
						if(temp->next)
							current=temp->next;
						else
							current=head;
					}
					break;
				}
				if(temp->next)
					temp=temp->next;
				else
					temp=head;
			}
			if(!flag)
				cout<<"Memory allocation failed using Next Fit\n";
		}
	}
	
	void worstFit()
	{
		cout<<"\nEnter number of processes: ";
		int pnum;
		cin>>pnum;
		for(int i=0; i<pnum; ++i)
		{
			cout<<"\nEnter process block: ";
			int t, flag=0;
			cin>>t;
			MemoryBlock* temp=head, *largest=nullptr;
			while(temp)
			{
				if(!temp->allocated and temp->size>=t) 
				{
					if(!largest)
						largest=temp;
					if((largest->size)<(temp->size))
						largest=temp;
				}
				temp=temp->next;
			}
			if(largest)
			{
				largest->allocated=true;
				int memsize=largest->size;
				largest->size=t;
				largest->process=("P_"+to_string(t));
				flag=1;
				cout<<"Memory allocated using Worst Fit\n";
				if(memsize-t)
				{
					MemoryBlock* newBlock=new MemoryBlock(memsize-t);
					newBlock->next=largest->next;
					largest->next=newBlock;
					current=newBlock;
				}
				else
				{
					if(temp->next)
						current=temp->next;
					else
						current=head;
				}
				break;
			}
			if(!flag)
				cout<<"Memory allocation failed using Worst Fit\n";
		}
	}

	void display()
	{
		MemoryBlock* temp=head;
		while(temp)
		{
			cout<<"Memory Block: Size="<<temp->size<<", Allocated="<<(temp->allocated ? temp->process : "No")<<endl;
			temp=temp->next;
		}
	}
};


int main()
{
	while(true)
	{
		MemoryManager memory;
		int numBlocks;
		cout<<"Enter the number of memory blocks: ";
		cin>>numBlocks;
		int blockSize;
		for(int i=0; i<numBlocks; ++i)
		{
			cout<<"Enter size for block "<<i+1<<": ";
			cin>>blockSize;
			memory.addBlock(blockSize);
		}
		if(!blockSize)
			break;
		cout<<"\nSelect allocation method: ";
		cout<<"\n1. First Fit";
		cout<<"\n2. Best Fit";
		cout<<"\n3. Next Fit";
		cout<<"\n4. Worst Fit";
		cout<<"\nEnter choice: ";
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 1:
				memory.firstFit();
				break;
			
			case 2:
				memory.bestFit();
				break;
			
			case 3:
				memory.nextFit();
				break;
			
			case 4:
				memory.worstFit();
				break;
			
			default:
				cout<<"\nInvalid choice!\n";
		}
		cout<<"\nCurrent Memory Status:\n";
		memory.display();
	}
	return 0;
}
