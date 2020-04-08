/* 
Yogita Misal
Roll No:27092
Implement stack as an abstract data type using linked list and use this ADT for conversion of 
infix expression to postfix, prefix and evaluation of postfix and prefix expression. 
*/ 
#include<iostream> 
using namespace std; 
#include<stdlib.h> 
#include<string.h> 
#include<math.h> 
 
 
class STACK 
{ 
	int *data; 
	STACK **next; 
	public: 
	STACK() 
	{ 
		data=new int; 
		next=new STACK*; 
	} 
	STACK * push(STACK * top,char key); 
	STACK * pop(char *postfix,int *j); 
	 
	int prio(char key,int flag); 
	 
	STACK * epush(STACK * top,int key); 
	STACK * epop(int *key); 
}; 
 
STACK * STACK::push(STACK * top,char key) 
{ 
	*data=key; 
	*next=top; 
	return this; 
} 
STACK * STACK::pop(char *postfix,int *index) 
{ 
	if(*data=='(' || *data==')') 
		(*index)--; 
	else 
		postfix[*index]=*data; 
	return *next; 
} 
int STACK::prio(char key,int flag) 
{ 
	if(flag==0)					//prefix 
	{ 
		if(*data=='(')			//returns 1:push 0:pop 
		{ 
			if(key==')') 
				return 2;		//returns 2:pop 
			return 1; 
		} 
		else if(*data=='+' || *data=='-') 
		{ 
			if(key=='+'||key=='-'||key==')') 
				return 0; 
			else 
				return 1; 
		} 
		else if(*data=='/' || *data=='*' || *data=='%') 
		{ 
			if(key=='+'||key=='-'||key=='*'||key=='/'||key=='%'||key==')') 
				return 0; 
			else 
				return 1; 
		} 
		else if(*data=='^') 
		{ 
			if(key=='(') 
				return 1; 
			return 0; 
		} 
	} 
	else if(flag==1)			//postfix 
	{ 
		if(*data==')')			//returns 1:push 0:pop 
		{ 
			if(key=='(') 
				return 2;		//returns 2:pop 
			else  
				return 1; 
		} 
		else if(*data=='+' || *data=='-') 
		{ 
			if(key=='(') 
				return 0; 
			return 1; 
		} 
		else if(*data=='/' || *data=='*' || *data=='%') 
		{ 
			if(key=='+'|| key=='-'|| key=='(') 
				return 0; 
			else 
				return 1; 
		} 
		else if(*data=='^') 
		{ 
			if(key==')') 
				return 1; 
			return 0; 
		} 
	} 
} 
STACK * STACK::epush(STACK * top,int key) 
{ 
	*data=key; 
	*next=top; 
	return this; 
} 
STACK * STACK::epop(int *key) 
{ 
	*key=*data; 
	return *next; 
} 
 
//	//	//	//	//	//	//	//	//	//	Functions: 
 
int check(char str[50])		//Checks Validity of Expression 
{ 
	int i=0,count=0; 
	 
	for(i=0 ; str[i]!='\0' ; i++) 
	{ 
		if(str[i]>=48&&str[i]<=57 || str[i]>=65&&str[i]<=90 || str[i]>=97&&str[i]<=122 || str[i]=='(') 
			count++; 
	} 
	if((2*count-strlen(str))==1) 
		return 1; 
	return 0; 
} 
 
void reverse(char *temp)	//Reverses the string 
{ 
	char newstr[50]; 
	int i,k; 
	 
	i=strlen(temp)-1;	k=0; 
	 
	for( ; i>=0 ; i--,k++) 
		newstr[k]=*(temp+i); 
	   
	newstr[k]='\0'; 
	strcpy(temp,newstr); 
 
} 
 
void in_post()				//converts expression InFix->PostFix 
{ 
	STACK *top=NULL,*ptr; 
	int i,j; 
	char infix[50],postfix[50]; 
	 
	while(1) 
	{ 
	cout<<"\n\tEnter the Infix-Expression : "; 
	cin>>infix; 
	if(check(infix)==1) 
		break; 
	cout<<"\n\tIncorrect Expression. Try Again :(\n"; 
	} 
	 
	for(i=0,j=0 ; infix[i]!='\0' ; i++) 
	{ 
		if(infix[i]>=48&&infix[i]<=57 || infix[i]>=65&&infix[i]<=90 || infix[i]>=97&&infix[i]<=122) 
		{ 
			postfix[j]=infix[i]; 
			j++;	 
		} 
		else if(top==NULL || top->prio(infix[i],0)==1 ) 
		{ 
			ptr=new STACK; 
			top=ptr->push(top,infix[i]); 
		} 
		else if(top->prio(infix[i],0)!=1) 
		{ 
			if(top->prio(infix[i],0)!=2) 
				i--; 
			top=top->pop(postfix,&j); 
			j++; 
		} 
	} 
	while(top!=NULL) 
	{ 
		top=top->pop(postfix,&j); 
		j++; 
	} 
	postfix[j]='\0'; 
	 
	cout<<"\n\tPostfix-Expression : "<<postfix; 
	 
} 
 
void in_pre()				//converts expression InFix->PostFix 
{ 
	STACK *top=NULL,*ptr; 
	char infix[50],prefix[50]; 
	int i,j; 
 
	while(1) 
	{ 
	cout<<"\n\tEnter the Infix-Expression : "; 
	cin>>infix; 
	if(check(infix)==1) 
		break; 
	cout<<"\n\tIncorrect Expression. Try Again :(\n"; 
	} 
	 
	reverse(infix); 
	 
	for(i=0,j=0;infix[i]!='\0';i++) 
	{ 
		if(infix[i]>=48&&infix[i]<=57 || infix[i]>=65&&infix[i]<=90 || infix[i]>=97&&infix[i]<=122) 
		{ 
			prefix[j]=infix[i]; 
			j++;	 
		} 
		else if(top==NULL || top->prio(infix[i],1)==1 ) 
		{ 
			ptr=new STACK; 
			top=ptr->push(top,infix[i]); 
		} 
		else if(top->prio(infix[i],1)!=1) 
		{ 
			if(top->prio(infix[i],1)!=2) 
				i--; 
			top=top->pop(prefix,&j); 
			j++; 
		} 
	} 
	while(top!=NULL) 
	{ 
		top=top->pop(prefix,&j); 
		j++; 
	} 
	prefix[j]='\0'; 
	 
	reverse(prefix); 
	 
	cout<<"\n\tprefix-Expression : "<<prefix; 
	 
} 
 
void epost()				//Evaluates PostFix Expression 
{ 
	STACK *top=NULL,*ptr; 
	char postfix[50]; 
	int i,j,first,second,result; 
	 
	while(1) 
	{ 
	cout<<"\n\tEnter the PostFix-Expression : "; 
	cin>>postfix; 
	if(check(postfix)==1) 
		break; 
	cout<<"\n\tIncorrect Expression. Try Again :(\n"; 
	} 
	 
	for(i=0 ; postfix[i]!='\0' ; i++) 
	{ 
		if(postfix[i]>=48&&postfix[i]<=57) 
		{ 
			ptr=new STACK; 
			top=ptr->epush(top,postfix[i]-48); 
		} 
		else if(postfix[i]>=65&&postfix[i]<=90 || postfix[i]>=97&&postfix[i]<=122) 
		{ 
			ptr=new STACK; 
			cout<<"\n\tEnter the value of '"<<postfix[i]<<"' = "; 
			cin>>result; 
			top=ptr->epush(top,result); 
		} 
		else  
		{ 
			if(top==NULL) 
			{ 
				cout<<"\n\tIncorrect Expression"; 
				return; 
			} 
			top=top->epop(&second); 
			if(top==NULL) 
			{ 
				cout<<"\n\tIncorrect Expression"; 
				return; 
			} 
			top=top->epop(&first); 
			if(postfix[i]=='+') 
				result=first+second; 
			else if(postfix[i]=='-') 
				result=first-second; 
			else if(postfix[i]=='/') 
				result=first/second; 
			else if(postfix[i]=='*') 
				result=first*second; 
			else if(postfix[i]=='%') 
				result=first%second; 
			else if(postfix[i]=='^') 
				result=pow(first,second); 
				 
			top=ptr->epush(top,result); 
		} 
	} 
	 
	top=top->epop(&result); 
	cout<<"\n\tResult = "<<result; 
} 
 
void epre()					//Evaluates PreFix Expression 
{	 
	STACK *top=NULL,*ptr; 
	char prefix[50]; 
	int i,j,first,second,result; 
	 
	while(1) 
	{ 
	cout<<"\n\tEnter the preFix-Expression : "; 
	cin>>prefix; 
	if(check(prefix)==1) 
		break; 
	cout<<"\n\tIncorrect Expression. Try Again :(\n"; 
	} 
	 
	reverse(prefix); 
	 
	for(i=0 ; prefix[i]!='\0' ; i++) 
	{ 
		if(prefix[i]>=48&&prefix[i]<=57) 
		{ 
			ptr=new STACK; 
			top=ptr->epush(top,prefix[i]-48); 
		} 
		else if(prefix[i]>=65&&prefix[i]<=90 || prefix[i]>=97&&prefix[i]<=122) 
		{ 
			ptr=new STACK; 
			cout<<"\n\tEnter the value of '"<<prefix[i]<<"' = "; 
			cin>>result; 
			top=ptr->epush(top,result); 
		} 
		else  
		{ 
			if(top==NULL) 
			{ 
				cout<<"\n\tIncorrect Expression"; 
				return; 
			} 
			top=top->epop(&first); 
			if(top==NULL) 
			{ 
				cout<<"\n\tIncorrect Expression"; 
				return; 
			} 
			top=top->epop(&second); 
			if(prefix[i]=='+') 
				result=first+second; 
			else if(prefix[i]=='-') 
				result=first-second; 
			else if(prefix[i]=='/') 
				result=first/second; 
			else if(prefix[i]=='*') 
				result=first*second; 
			else if(prefix[i]=='%') 
				result=first%second; 
			else if(prefix[i]=='^') 
				result=pow(first,second); 
				 
			top=ptr->epush(top,result); 
		} 
	} 
	 
	top=top->epop(&result); 
	cout<<"\n\tResult = "<<result; 
} 
int main() 
{ 
	int choice; 
	 
	do 
	{ 
	cout<<"\n--------------------MENU--------------------\n"; 
	cout<<"\n\t1:InFix-PostFix \n\t2:Infix-PreFix \n\t3:Postfix_Evaluation \n\t4:PreFix_Evaluation \n\t  0:EXIT  >>"; 
	cin>>choice; 
	 
	switch(choice) 
	{ 
	case 1: 
		in_post(); 
		break; 
	case 2: 
		in_pre(); 
		break; 
	case 3: 
		epost(); 
		break; 
	case 4: 
		epre(); 
		break; 
	} 
	}while(choice!=0); 
 
	cout<<"\n"; 
	return 0; 
} 
 
