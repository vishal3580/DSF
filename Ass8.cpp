/* 
A business house has several offices in different countries; they want to lease phone lines to 
connect them with each other and the phone company charges different rent to connect 
different pairs of cities. Business house want to connect all its offices with a minimum total 
cost. Solve the problem by suggesting appropriate data structures 
*/ 
 
 
#include<iostream> 
using namespace std; 
#include<stdlib.h> 
#define INFINITY 10000 
 
struct city 
{ 
	char name[10]; 
}; 
 
void accept(int *a,struct city c[],int n) 
{ 
    int i,j,temp; 
         
    for(i=0 ; i<n ; i++) 
    { 
        for(j=i ; j<n ; j++) 
        { 
            if(i==j) 
            	*(a+i*n+j)=0; 
            else 
            {     
                cout<<"\n\tRent between cities ["<<c[i].name<<"]["<<c[j].name<<"] : ₹ "; 
                cin>>temp; 
                *(a+i*n+j)=*(a+j*n+i)=temp; 
        	} 
        } 
    } 
} 
 
void display(int *a,struct city c[],int n) 
{ 
    int i,j; 
     
    for(i=0 ; i<n ; i++) 
    { 
        cout<<"\n\t"<<c[i].name<<"]"; 
        for(j=0 ; j<n ; j++) 
            cout<<"\t"<<*(a+i*n+j); 
    } 
} 
 
void spantree(int *a,struct city c[],int n) 
{ 
	int visit[n],dist[n],from[n],weight[n][n],*s; 
	int i,j,k,l,edges,mindist,cost,check1,check2; 
	 
	s=new int[n-1]; 
	 
	for(i=0;i<n;i++) 
	{ 
		for(j=0;j<n;j++) 
		{ 
			if(*(a+i*n+j)==0) 
				weight[i][j]=INFINITY; 
			else  
				weight[i][j]=*(a+i*n+j); 
			*(s+i*n+j)=0; 
		} 
	} 
	 
	dist[0]=0; 
	visit[0]=1; 
	 
	for(i=1;i<n;i++) 
	{ 
		dist[i]=weight[0][i]; 
		from[i]=0; 
		visit[i]=0; 
	}	 
	 
	cost=0; 
	edges=n-1; 
	 
	cout<<"\n\tStart Pt.\tEnd Pt.\t\tWeight"; 
	while(edges>0) 
	{ 
		mindist=INFINITY; 
		for(i=1;i<n;i++) 
		{ 
			if(dist[i]<mindist && visit[i]==0) 
			{ 
				l=i; 
				mindist=dist[i]; 
			} 
		} 
	 
		k=from[l]; 
		*(s+k*n+l)=dist[l]; 
		*(s+l*n+k)=dist[l]; 
		edges--; 
		visit[l]=1; 
	 
		for(i=1;i<n;i++) 
		{ 
			if(visit[i]==0 && weight[i][l] < dist[i]) 
			{ 
				dist[i]=weight[i][l]; 
				from[i]=l; 
			} 
		} 
		cout<<"\n\t"<<c[k].name<<"\t\t"<<c[l].name<<"\t\t"<<weight[k][l]; 
		cost+=weight[k][l]; 
	} 
	cout<<"\n\n\tMinimum total cost betweeen all cities is : ₹ "<<cost; 
} 
 
 
 
 
int main() 
{ 
    int *a,n,flag,choice,i; 
     
    cout<<"\n\t\t**Prim's alorithm**\n"; 
    cout<<"\n\tEnter the No.of Cities : "; 
    cin>>n; 
    a=new int[n*n]; 
    struct city c[n]; 
         
    for(i=0;i<n;i++) 
    { 
    	cout<<"\n\tEnter the name of "<<i<<"th city : "; 
    	cin>>c[i].name; 
    } 
    accept(a,c,n); 
     
    do 
    { 
		cout<<"\n--------------------MENU--------------------"; 
		cout<<"\n\t1:Display Adjacency matrix\n\t2:Min. Spanning Tree\n\t0:Exit : "; 
		cin>>choice; 
		 
		switch(choice) 
		{ 
		    case 1: 
		        display(a,c,n); 
		        break; 
		    case 2: 
		        spantree(a,c,n); 
		        break; 
		} 
    }while(choice!=0); 
     
    cout<<"\n"; 
    return 0; 
} 
