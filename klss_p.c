#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

typedef struct node 
{
	int *data;
	struct node *next;
} Node;
typedef struct LinkList
{
	Node *first;
	Node *last;
} LinkList;

typedef unsigned long long boolstr;

LinkList subsets={NULL,NULL};

void printList(LinkList *list,int k)
{
	Node *tmp = list->first;
	int i =0;
	while(tmp)
	{
		i++;
		printf("%d:",i);
		for(int i = 0; i < k;i++)
		{
			printf("%d ",tmp->data[i]);
		}
		printf("\n");
		tmp=tmp->next;
	}
	printf("\n");
	
}

void LL_add(LinkList *list,int *d)
{
	Node *n = malloc(sizeof(Node));
	n->data=d;
	n->next=NULL;
	
	if(list->first==NULL)
	{
		list->first=n;
		list->last=n;
	}
	else
	{
		list->last->next=n;
		list->last=n;
	}
}

void subset(int A[],int s,int k,int start,int current,boolstr used,LinkList lists[])
{
	if(current == k )
	{
		int *tmp=calloc(k,sizeof(int));
		int f=0;
		long tu = used;
		for(int i=0;i<s&& f<k;i++,tu=tu>>1)
		{
			if(tu&1==1)
			{
				tmp[f]=A[i];
				f++;
			}
			
		}
		
		LL_add(&lists[omp_get_thread_num()],tmp);
		return;
	}
	
	if(start==s)
	{
		return;
	}
	
		#pragma omp task
		{
			subset(A,s,k,start+1,current+1,used|(1<<start),lists);
		}
		#pragma omp task
		{
			subset(A,s,k,start+1,current,used,lists);
		}
}
void joinLists(LinkList lists[],int N_T)
{
	subsets.first=lists[0].first;
	subsets.last=lists[0].last;
	LinkList T;
	for(int i = 0; i<N_T;i++)
	{
		T=lists[i];
		if(T.first)
		{
			subsets.last->next=T.first;
			subsets.last=T.last;
		}
	}
}
int main(int argc, char* args[])
{
	int n,k;
	scanf("%d",&n);
	scanf("%d",&k);
	int A[n],used[n];

	int N_T=omp_get_max_threads();
	clock_t start_t,end_t;
	
	LinkList lists[N_T];
	for(int i=0;i<N_T;i++)
	{
		lists[i].first=NULL;
		lists[i].last=NULL;
	}
	for(int i = 0; i<n;i++)
	{
		A[i]=i;
		used[i]=0;
	}
	start_t=clock();
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			subset(A,n,k,0,0,0,lists);
		}
	}
	#pragma omp taskwait
	joinLists(lists,N_T);
	end_t=clock();
	//printList(&subsets,k);
	
	printf("Clock Ticks: %ld\n",end_t-start_t);
	
}
