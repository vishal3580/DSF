/* 
Store data of students with telephone no and name in the structure using hashing function for 
telephone number and implement chaining with and without replacement. 
*/ 
 
 
#include<iostream> 
using namespace std; 
#include<stdlib.h> 
#include<string.h> 
#define MAX 10 
 
struct STUDENT 
{ 
	long mob_no; 
	char name[20]; 
}; 
 
void accept(struct STUDENT *temp); 
void display(struct STUDENT *temp); 
 
int HASH(int mob); 
void table(struct STUDENT S[MAX],int chain[MAX]); 
 
void noreplace(); 
void replace(); 
 
//	//	//	//	//	//	//	//	//	// 
 
void accept(struct STUDENT *temp) 
{ 
	cout<<"\n\tEnter the NAME >>"; 
	cin>>temp->name; 
	cout<<"\tEnter the mob_no >>"; 
	cin>>temp->mob_no; 
} 
void display(struct STUDENT *temp) 
{ 
	cout<<"\n\tNAME \tmob_no"; 
	cout<<"\n\t"<<temp->name; 
	cout<<"\t"<<temp->mob_no; 
} 
 
int HASH(int mob) 
{ 
	int temp; 
	temp=mob%10; 
	return temp; 
} 
void table(struct STUDENT S[MAX],int chain[MAX]) 
{ 
	int i; 
	 
	cout<<"\n\tindex\tNAME\tMob_no\t\tchain"; 
	for(i=0;i<MAX;i++) 
		cout<<"\n\t"<<i<<"\t"<<S[i].name<<"\t"<<S[i].mob_no<<"\t\t"<<chain[i]; 
 
} 
 
void noreplace() 
{ 
	struct STUDENT S[MAX],temp; 
	int chain[MAX]; 
	 
	int choice,index,flag; 
	long key; 
 
	 
	for(flag=0 ; flag<MAX ; flag++) 
	{ 
		S[flag].mob_no=-1; 
		strcpy(S[flag].name,"-1"); 
		chain[flag]=-1; 
	} 
	 
	do 
	{ 
	cout<<"\n--------------------MENU--------------------\n"; 
	cout<<"\n\t1:Add\n\t2:Search\n\t3:#Table\n\t0:EXIT >>"; 
	cin>>choice; 
	switch(choice) 
	{ 
		case 1: 
			flag=0; 
			for(int i=0 ; i<MAX ; i++) 
				if(S[i].mob_no!=-1) 
					flag++; 
			 
			if(flag==MAX) 
				cout<<"\n\tNo more space to ADD New Entry"; 
			else 
			{ 
			accept(&temp); 
			index=HASH(temp.mob_no); 
				 
			flag=-1; 
			while(1) 
				if(S[index].mob_no==-1) 
				{ 
					if(flag!=-1) 
						chain[flag]=index; 
					S[index]=temp; 
					break; 
				} 
				else 
				{ 
					if(HASH(S[index].mob_no)!=HASH(temp.mob_no)) 
						index=(index+1)%MAX; 
					else if(chain[index]==-1) 
					{ 
						if(HASH(S[index].mob_no)==HASH(temp.mob_no)) 
							flag=index; 
						index=(index+1)%MAX; 
					} 
					else 
						index=chain[index]; 
				} 
			} 
			break; 
		case 2: 
			cout<<"\n\tEnter the mob_no to search >>"; 
			cin>>key; 
			index=HASH(key); 
			 
			flag=index; 
			while(1) 
			{ 
				if(S[index].mob_no==key) 
				{ 
					display(&S[index]); 
					break; 
				} 
				else 
				{ 
					if(HASH(S[index].mob_no)==HASH(key)) 
					{ 
						if(chain[index]==-1) 
						{ 
							cout<<"\n\tRecord Not Found"; 
							break; 
						} 
						else 
							index=chain[index]; 
					} 
					else 
						index=(index+1)%MAX; 
					 
					if(flag==index) 
					{ 
						cout<<"\n\tRecord Not Found"; 
						break; 
					} 
				} 
			} 
			break; 
		case 3: 
			table(S,chain); 
			break; 
	} 
	}while(choice!=0); 
 
} 
void replace() 
{ 
	struct STUDENT S[MAX],temp; 
	int chain[MAX]; 
	 
	int choice,index,flag,intermediate; 
	long key; 
 
	 
	for(flag=0 ; flag<MAX ; flag++) 
	{ 
		S[flag].mob_no=-1; 
		strcpy(S[flag].name,"-1"); 
		chain[flag]=-1; 
	} 
	 
	do 
	{ 
	cout<<"\n--------------------MENU--------------------\n"; 
	cout<<"\n\t1:Add\n\t2:Search\n\t3:#Table\n\t0:EXIT >>"; 
	cin>>choice; 
	switch(choice) 
	{ 
		case 1: 
			flag=0; 
			for(int i=0 ; i<MAX ; i++) 
				if(S[i].mob_no!=-1) 
					flag++; 
			 
			if(flag==MAX) 
				cout<<"\n\tNo more space to ADD New Entry"; 
			else 
			{ 
			accept(&temp); 
			index=HASH(temp.mob_no); 
				 
			flag=-1;	intermediate=-1; 
			while(1) 
				if(S[index].mob_no==-1) 
				{ 
					if(flag!=-1) 
						chain[flag]=index; 
					 
					if(intermediate!=-1) 
					{	 
						for(int i=0 ; i<MAX ; i++) 
						{ 
							if(chain[i]==intermediate) 
								chain[i]=index; 
						} 
						S[index]=S[intermediate]; 
						index=intermediate; 
					}	 
					S[index]=temp; 
					break; 
				} 
				else 
				{ 
					if(HASH(S[index].mob_no)!=HASH(temp.mob_no)) 
					{ 
						intermediate=index; 
						while(S[index].mob_no!=-1) 
							index=(index+1)%MAX; 
					} 
					else if(chain[index]==-1) 
					{ 
						if(HASH(S[index].mob_no)==HASH(temp.mob_no)) 
							flag=index; 
						while(S[index].mob_no!=-1) 
							index=(index+1)%MAX; 
					} 
					else 
						index=chain[index]; 
				} 
			} 
			break; 
		case 2: 
			cout<<"\n\tEnter the mob_no to search >>"; 
			cin>>key; 
			index=HASH(key); 
			 
			flag=index; 
			while(1) 
			{ 
				if(S[index].mob_no==key) 
				{ 
					display(&S[index]); 
					break; 
				} 
				else 
				{ 
					if(HASH(S[index].mob_no)!=HASH(key) || chain[index]==-1) 
					{ 
						cout<<"\n\tRecord Not Found"; 
						break; 
					} 
					else 
						index=chain[index]; 
					 
					if(flag==index) 
					{ 
						cout<<"\n\tRecord Not Found"; 
						break; 
					} 
				} 
			} 
			break; 
		case 3: 
			table(S,chain); 
			break; 
	} 
	}while(choice!=0); 
	 
} 
 
int main() 
{ 
	int choice; 
	 
	do 
	{ 
	cout<<"\n********************HASHING********************\n"; 
	cout<<"\n\t1:chaining without replacement\n\t2:chaining with replacement"; 
	cout<<"\n\t0:EXIT  >>"; 
	cin>>choice; 
	 
	switch(choice) 
	{ 
		case 1: 
			noreplace(); 
			break; 
		case 2: 
			replace(); 
			break; 
	} 
	}while(choice!=0); 
	 
	cout<<"\n"; 
	return 0; 
} 
