/* 
Construct and expression tree from postfix/prefix expression and perform recursive and non- 
recursive In-order, pre-order and post-order traversals. 
*/ 
#include<iostream> 
using namespace std; 
#include<stdlib.h> 
#include<string.h> 
 
class TREE 
{ 
	char *data; 
	TREE **left; 
	TREE **right; 
	public: 
	TREE() 
	{ 
		data=new char; 
		left=new TREE*; 
		right=new TREE*; 
	} 
	void insert(char key); 
	TREE * setleft(TREE *ptr); 
	TREE * setright(TREE *ptr); 
	 
	void display(); 
	TREE * checkleft(); 
	TREE * checkright(); 
	 
	void in_display(); 
	void pre_display(); 
	void post_display(); 
}; 
 
class STACK 
{ 
	TREE **address; 
	STACK **next; 
	public: 
	STACK() 
	{ 
		address=new TREE*; 
		next=new STACK*; 
	} 
	void setnext(STACK *ptr); 
	STACK * push(TREE *root,STACK *top); 
	TREE * pop(); 
	STACK * retnext(); 
}; 
 
int check(char str[50]); 
void reverse(char *str); 
void display_in(TREE *root); 
void display_pre(TREE *root); 
void display_post(TREE *root); 
 
void postfix(); 
void prefix(); 
 
//	//	//	//	//	//	//	//	//	//	TREE 
 
void TREE::insert(char key) 
{ 
	*data=key; 
	*left=NULL; 
	*right=NULL; 
} 
TREE * TREE::setleft(TREE *ptr) 
{ 
	if(*left==NULL) 
	{ 
		*left=ptr; 
		return NULL; 
	} 
	else  
		return *left; 
} 
TREE * TREE::setright(TREE *ptr) 
{ 
	if(*right==NULL) 
	{ 
		*right=ptr; 
		return NULL; 
	} 
	else  
		return *right; 
} 
 
void TREE::display() 
{ 
	cout<<*data<<"  "; 
} 
TREE * TREE::checkleft() 
{		 
	if(*left==NULL) 
		return NULL; 
	return *left; 
} 
TREE * TREE::checkright() 
{ 
	if(*right==NULL) 
		return NULL; 
	return *right; 
} 
 
void TREE::in_display()			//Recursive Inorder Traversal 
{ 
	TREE *temp; 
	 
	if(*left!=NULL) 
	{ 
		temp=*left; 
		temp->in_display(); 
	} 
	cout<<*data<<"  "; 
	if(*right!=NULL) 
	{ 
		temp=*right; 
		temp->in_display(); 
	} 
} 
void TREE::pre_display()		//Recursive Preorder Traversal 
{ 
	TREE *temp; 
	 
	cout<<*data<<"  "; 
	if(*left!=NULL) 
	{ 
		temp=*left; 
		temp->pre_display(); 
	} 
	if(*right!=NULL) 
	{ 
		temp=*right; 
		temp->pre_display(); 
	} 
} 
void TREE::post_display()		//Recursive Postorder Traversal 
{ 
	TREE *temp; 
	 
	if(*left!=NULL) 
	{ 
		temp=*left; 
		temp->post_display(); 
	} 
	if(*right!=NULL) 
	{ 
		temp=*right; 
		temp->post_display(); 
	} 
	cout<<*data<<"  "; 
} 
 
//	//	//	//	//	//	//	//	//	//	STACK 
 
void STACK::setnext(STACK *ptr) 
{ 
	*next=ptr; 
} 
STACK * STACK::push(TREE *root,STACK *top) 
{ 
	*address=root; 
	*next=top; 
	return this; 
} 
TREE * STACK::pop() 
{ 
	return *address; 
} 
STACK * STACK::retnext() 
{ 
	return *next; 
} 
 
//	//	//	//	//	//	//	//	//	//	Functions: 
 
int check(char str[50])			//Checks Validity of Expression 
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
 
void reverse(char *str)			//Reverses the string 
{ 
	char newstr[50]; 
	int i,k; 
	 
	i=strlen(str)-1;	k=0; 
	 
	for( ; i>=0 ; i--,k++) 
		newstr[k]=*(str+i); 
	   
	newstr[k]='\0'; 
	strcpy(str,newstr); 
} 
 
void display_in(TREE *root)		//Non-recursive Inorder Traversal 
{ 
	STACK *top=NULL,*stackptr; 
	int flag=0; 
	 
	while(1) 
	{ 
	if(flag==0) 
	{ 
		if(root->checkleft()!=NULL) 
		{ 
			stackptr=new STACK; 
			top=stackptr->push(root,top); 
			 
			root=root->checkleft(); 
		} 
		else 
			flag=1; 
	} 
	else if(flag==1) 
	{	 
		root->display(); 
 
		if(root->checkright()!=NULL) 
		{ 
			flag=0; 
			root=root->checkright(); 
		} 
		else 
		{ 
			flag=1; 
			if(top!=NULL) 
			{ 
				root=top->pop(); 
				top=top->retnext(); 
			} 
			else  
				break; 
		} 
	} 
	} 
} 
 
void display_pre(TREE *root)		//Non-recursive Preorder Traversal 
{ 
	STACK *top=NULL,*stackptr; 
	int flag=0; 
	 
	while(1) 
	{ 
	if(flag==0) 
	{ 
		root->display(); 
		if(root->checkleft()!=NULL) 
		{ 
			stackptr=new STACK; 
			top=stackptr->push(root,top); 
			 
			root=root->checkleft(); 
		} 
		else 
			flag=1; 
	} 
	else if(flag==1) 
	{ 
		if(root->checkright()!=NULL) 
		{ 
			flag=0; 
			root=root->checkright(); 
		} 
		else 
		{ 
			flag=1; 
			if(top!=NULL) 
			{ 
				root=top->pop(); 
				top=top->retnext(); 
			} 
			else  
				break; 
		} 
	} 
	} 
} 
 
void display_post(TREE *root)		//Non-recursive Postorder Traversal 
{ 
    TREE *temp; 
	STACK *top=NULL,*stackptr; 
	int flag=0; 
	 
	while(1) 
	{ 
	if(flag==0) 
	{ 
		if(root->checkleft()!=NULL) 
		{ 
			stackptr=new STACK; 
			top=stackptr->push(root,top); 
			 
			root=root->checkleft(); 
			flag=0; 
		} 
		else 
			flag=1; 
	} 
	else if(flag==1) 
	{ 
		if(root->checkright()!=NULL) 
		{ 
			stackptr=new STACK; 
			top=stackptr->push(root,top); 
			 
			root=root->checkright(); 
			flag=0; 
		} 
		else 
			flag=2; 
	} 
	else if(flag==2) 
	{ 
	    root->display(); 
	    temp=root; 
	    if(top!=NULL) 
		{ 
			root=top->pop(); 
			top=top->retnext(); 
			 
	        if(root->checkleft()==temp) 
	            flag=1; 
	        else if(root->checkright()==temp) 
	            flag=2; 
		} 
		else  
			break; 
	} 
	} 
} 
 
void postfix()						//postfix 
{ 
	TREE *root=NULL,*ptr,*temp; 
	STACK *top=NULL,*stackptr; 
	char expression[50]; 
	int i; 
	 
	while(1) 
	{ 
	cout<<"\n\tEnter the postfix Expression : "; 
	cin>>expression; 
	if(check(expression)==1) 
		break; 
	cout<<"\n\tInvalid Expression :("; 
	} 
	 
	for(i=0;expression[i]!='\0';i++) 
	{ 
		if(expression[i]>=48&&expression[i]<=57 || expression[i]>=65&&expression[i]<=90 || expression[i]>=97&&expression[i]<=122) 
		{ 
			ptr=new TREE; 
			ptr->insert(expression[i]); 
			 
			stackptr=new STACK; 
			top=stackptr->push(ptr,top); 
		} 
		else  
		{ 
			ptr=new TREE; 
			ptr->insert(expression[i]); 
			 
			if(top==NULL) 
			{ 
				cout<<"\n\tInvalid Expression"; 
				return; 
			} 
			temp=top->pop();		//1st pop 
			ptr->setright(temp); 
			top=top->retnext(); 
			 
			if(top==NULL) 
			{ 
				cout<<"\n\tInvalid Expression"; 
				return; 
			} 
			temp=top->pop();		//2nd pop 
			ptr->setleft(temp); 
			top=top->retnext(); 
			 
			stackptr=new STACK; 
			top=stackptr->push(ptr,top); 
		} 
	} 
	root=top->pop(); 
 
	cout<<"\n\t\b\b\u1368 Resursive"; 
	cout<<"\n\tInOrder:\n\t"; 
	root->in_display(); 
	cout<<"\n\tPreOrder:\n\t"; 
	root->pre_display(); 
	cout<<"\n\tPostOrder:\n\t"; 
	root->post_display(); 
	 
	cout<<"\n\t\b\b\u1368 Non-Resursive"; 
	cout<<"\n\tInOrder:\n\t"; 
	display_in(root); 
	cout<<"\n\tPreOrder:\n\t"; 
	display_pre(root); 
	cout<<"\n\tPostOrder:\n\t"; 
	display_post(root);		 
} 
 
void prefix()						//prefix 
{ 
	TREE *root=NULL,*ptr,*temp; 
	STACK *top=NULL,*stackptr; 
	char expression[50]; 
	int i; 
 
	while(1)		 
	{ 
	cout<<"\n\tEnter the prefix Expression : "; 
	cin>>expression; 
	if(check(expression)==1) 
		break; 
	cout<<"\n\tInvalid Expression"; 
	} 
	 
	reverse(expression); 
			 
	for(i=0;expression[i]!='\0';i++) 
	{ 
		if(expression[i]>=48&&expression[i]<=57 || expression[i]>=65&&expression[i]<=90 || expression[i]>=97&&expression[i]<=122) 
		{ 
			ptr=new TREE; 
			ptr->insert(expression[i]); 
			 
			stackptr=new STACK; 
			top=stackptr->push(ptr,top); 
		} 
		else  
		{ 
			ptr=new TREE; 
			ptr->insert(expression[i]); 
				 
			if(top==NULL) 
			{ 
				cout<<"\n\tInvalid Expression"; 
				return; 
			} 
			temp=top->pop();		//1st pop 
			ptr->setleft(temp); 
			top=top->retnext(); 
			 
			if(top==NULL) 
			{ 
				cout<<"\n\tInvalid Expression"; 
				return; 
			} 
			temp=top->pop();		//2nd pop 
			ptr->setright(temp); 
			top=top->retnext(); 
			 
			 
			stackptr=new STACK; 
			top=stackptr->push(ptr,top); 
		} 
	} 
	root=top->pop(); 
 
	cout<<"\n\t\b\b\u1368 Resursive"; 
	cout<<"\n\tInOrder:\n\t"; 
	root->in_display(); 
	cout<<"\n\tPreOrder:\n\t"; 
	root->pre_display(); 
	cout<<"\n\tPostOrder:\n\t"; 
	root->post_display(); 
	 
	cout<<"\n\t\b\b\u1368 Non-Resursive"; 
	cout<<"\n\tInOrder:\n\t"; 
	display_in(root); 
	cout<<"\n\tPreOrder:\n\t"; 
	display_pre(root); 
	cout<<"\n\tPostOrder:\n\t"; 
	display_post(root); 
} 
 
int main() 
{ 
	int choice; 
	 
	do 
	{ 
	cout<<"\n--------------------MENU--------------------\n"; 
	cout<<"\n\t1:PostFix\n\t2:PreFix\n\t0:EXIT  >>"; 
	cin>>choice; 
	 
	switch(choice) 
	{ 
		case 1: 
			postfix(); 
			break; 
		case 2: 
			prefix(); 
			break; 
	} 
	}while(choice!=0); 
	 
	cout<<"\n"; 
	return 0; 
} 
 
