/* 
Department maintains a student information. The file contains roll number, name, division and 
address. Write a program to create a sequential file to store and maintain student data. It 
should allow the user to add, delete information of student. Display information of particular 
employee. If record of student does not exist an appropriate message is displayed. If student 
record is found it should display the student details. 
*/ 
#include<iostream> 
#include<fstream> 
using namespace std; 
 
class student 
{     
 	int roll; 
 	char name[20]; 
 	char address[50]; 
 	char division; 
 	public: 
 	void getdata() 
 	{ 
 		cout<<"\n\tRoll No.>>"; 
 		cin>>roll; 
 		cout<<"\tEnter Name >>"; 
 		cin>>name; 
 		cout<<"\tEnter Address >>"; 
 		cin>>address; 
 		cout<<"\tEnter Division >>"; 
 		cin>>division; 
 	} 
 	void putdata() 
 	{ 
 		cout<<"\n\t"<<roll<<"\t\t"<<name<<"\t\t"<<address<<"\t\t"<<division; 
 	} 
 	int rollno() 
 	{ 
 	    return roll; 
 	} 
}; 
 
class ALGO 
{ 
	public: 
	void add(int i)  //add function 
	{ 
	    fstream fp("Student.txt",ios::out|ios::app); 
 
		student s; 
		s.getdata(); 
		fp.write((char *) &s,sizeof(s)); 
		fp.close(); 
	} 
	void display()      		  //display function 
	{ 
		fstream fp("Student.txt",ios::in); 
		student s; 
		fp.read((char *)&s,sizeof(s)); 
		while(!fp.eof()) 
		{ 
			s.putdata(); 
			fp.read((char *)&s,sizeof(s)); 
		} 
		fp.close(); 
	} 
	void delet(int rollno)    //delete function 
	{ 
		fstream fp1("Student.txt",ios::in); 
		fstream temp("Temp.txt",ios::out | ios::app); 
		student s; 
		int flag=0; 
		fp1.read((char *)&s,sizeof(s)); 
		while(!fp1.eof()) 
		{ 
			if(rollno==s.rollno()) 
			{ 
			    cout<<"\n\tRoll_No\t\tName\t\tAddress\t\tDivision"; 
			    s.putdata(); 
				cout<<"\n\tThe Record is Deleted!\n"; 
				flag=1; 
			} 
			else 
			{ 
				temp.write((char *)&s,sizeof(s)); 
			} 
			fp1.read((char *)&s,sizeof(s)); 
		} 
		if(flag==0) 
			cout<<"\n\tRecord Not Found!"; 
		fp1.close(); 
		temp.close(); 
		remove("Student.txt"); 
		rename("Temp.txt","Student.txt"); 
	} 
	void modify(int rollno)  //modify function 
	{ 
		fstream fp1("Student.txt",ios::in); 
		fstream temp("Temp.txt",ios::out | ios::app); 
		student s; 
		int flag=0; 
		fp1.read((char *)&s,sizeof(s)); 
		while(!fp1.eof()) 
		{ 
			if(rollno==s.rollno()) 
			{ 
			    cout<<"\n\tRoll_No\t\tName\t\tAddress\t\tDivision"; 
			    s.putdata(); 
				cout<<"\n\tEnter the New data:"; 
				s.getdata(); 
				flag=1; 
			} 
			temp.write((char *)&s,sizeof(s)); 
			fp1.read((char *)&s,sizeof(s)); 
		} 
		if(flag==0) 
			cout<<"\n\tRecord Not Found!"; 
		fp1.close(); 
		temp.close(); 
		remove("Student.txt"); 
		rename("Temp.txt","Student.txt"); 
	} 
}; 
 
int main() 
{ 
	ALGO a; 
	int i,n,rollno,choice; 
	 
	cout<<"\n\t\t\t**File Handling**\n"; 
	cout<<"\n\tEnter the number of records (n) >>"; 
	cin>>n; 
 
    for(i=0;i<n;i++) 
        a.add(i); 
 
	do 
	{ 
		cout<<"\n--------------------MENU--------------------"; 
		cout<<"\n\t1.Add\n\t2.Display\n\t3.Delete\n\t4.Modify\n\t0.Exit  >>"; 
		cin>>choice; 
		switch(choice) 
		{ 
		 
			case 1:	a.add(1); 
					break; 
			case 2:	cout<<"\n\tRoll_No\t\tName\t\tAddress\t\tDivision"; 
					a.display(); 
					break; 
			case 3:	cout<<"\n\tEnter the roll_no to delete >>"; 
					cin>>rollno; 
					a.delet(rollno); 
					break; 
			case 4:	cout<<"\n\tEnter the roll_no to modify >>"; 
					cin>>rollno; 
					a.modify(rollno); 
					break; 
 
		} 
	}while(choice!=0); 
	cout<<"\nTHANK YOU\n"; 
	return 0; 
} 
