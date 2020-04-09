/* Yogita Misal
Roll no:27092
Implement priority queue using single linked list for servicing patients in an hospital with priorities as 
1)Serious (top priority)
2)medium illness (medium priority)
3)General (least priority)
*/

#include<iostream>
using namespace std;

class queue
{
	struct patient
	{
		char name[20];
		patient *next;
		patient()
		{
			name[0]='\0';
			next=NULL;
		}
		
		void acceptname()
		{
			cout<<"*************************\n";	
			cout<<"Enter name of patient:";
			cin>>name;
		}
	
		void displayname()
		{
			cout<<"*************************\n";	
			cout<<"Name of patient:"<<name;
		}
	};
	patient *front,*rear,*temp;
public:	
	queue()
	{
		front=rear=NULL;
	}

	int empty()
	{
		if(rear==NULL)
		return 1;
			
	return 0;
	}	
	
	void insert();
	void remove();
	void display();

};

void queue::insert()
{
	patient *newpatient=new patient;
	newpatient->acceptname();
	if(empty())
	{
		front=rear=newpatient;		
	}
	else
	{
		rear->next=newpatient;
		rear=newpatient;
	}
}

void queue::remove()
{
	patient *temp=front;
	if(empty())
	{
		cout<<"\nQueue is Empty.";
	}
	else if(front==rear)
	{
		front=rear=NULL;
	}
	else
	{
		front=front->next;
	}	
	cout<<"\t"<<temp->name;
	cout<<"\tGot the Treatment...!!";
}

void queue::display()
{
	patient *temp=front;
	while(temp!=NULL)
	{
		cout<<"\t"<<temp->name;
		temp=temp->next;
	}
}

void queuetype(int q)
{
	if(q==1)
		cout<<"\nSerious Patient Queue       -->";	
	else if(q==2)
		cout<<"\nMedium illness Patient Queue-->";	
	else if(q==3)
		cout<<"\nGeneral Patient Queue       -->";	
}

int main()
{
	queue q[3];
	int ch,priority,i;
	do
	{
		cout<<"\n**********Menu***********";
		cout<<"\n1.Accept\n2.Remove\n3.Display\n4.Exit\n";
		cout<<"*************************\n";
		cout<<"Enter your choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"*************************\n";
				cout<<"1.Serious Patient\n2.Medium illness Patient\n3.General Patient\n";
				cout<<"*************************\n";				
				cout<<"Enter your priority:";			
				cin>>priority;
				q[priority-1].insert();
				break;

			case 2:
				cout<<"\n*************************\n";
				cout<<"\tQueue"<<"\t\t\tName"<<"\tStatus";
				for(i=0;i<3;i++)
				{
					queuetype(i+1);
					if(!q[i].empty())
					{
						q[i].remove();
						break;
					}
					else
						cout<<"Queue is Empty..!!";
				}
				break;

			case 3:
				cout<<"\n*************************\n";
				cout<<"\tQueue"<<"\t\t\tName";
				for(i=0;i<3;i++)
				{
					queuetype(i+1);
					q[i].display();				
				}
				break;	

			case 4: return 0;				
		}
	}while(ch<=4);
return 0;
}

