#include<stdio.h>
#include<stdlib.h>
#include<time.h>
static int KEY=0;
typedef struct node 
{
	int *data;
	int id;
	struct node *next;
} Node;
typedef struct LinkList
{
	Node *first;
	Node *last;
} LinkList;

LinkList subsets={NULL,NULL};

void printList(LinkList *list,int k)
{
	Node *tmp = list->first;
	while(tmp)
	{
		printf("%d: ",tmp->id);
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
	n->id=KEY;
	KEY++;
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

void subset(int A[],int s,int k,int start,int current, int used[])
{
	if(current == k )
	{
		int *tmp=calloc(k,sizeof(int));
		int f=0;
		for(int i=0;i<s;i++)
		{
			if(used[i]==1)
			{
				tmp[f]=A[i];
				f++;
			}
		}
		LL_add(&subsets,tmp);
		return;
	}
	
	if(start==s)
	{
		return;
	}
	
	used[start]=1;
	subset(A,s,k,start+1,current+1,used);
	
	used[start]=0;
	subset(A,s,k,start+1,current,used);
	
	
}

int main(int argc, char* args[])
{
	int n,k;
	scanf("%d",&n);
	scanf("%d",&k);
	int A[n],used[n];
	clock_t start_t,end_t;
	for(int i = 0; i<n;i++)
	{
		A[i]=i;
		used[i]=0;
	}
	
	start_t=clock();
	subset(A,n,k,0,0,used);
	end_t=clock();
	//printList(&subsets,k);
	printf("Clock Ticks: %ld\n",end_t-start_t);
	
}
