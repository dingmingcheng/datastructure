/**
	HDU 1247
	给定一些单词（按字典序给出）， 按字典序输出所有满足条件的单词（条件：该单词由其它两个单词构成）
	a
	ahat
	hat
	hatword
	hziee
	word
	输出:
	ahat
	hatword
*/



#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <ctime>
#include <set>
#include <functional>
using namespace std;

#define LS 2*i
#define RS 2*i+1
#define UP(i,x,y) for(i=x;i<=y;i++)
#define DOWN(i,x,y) for(i=x;i>=y;i--)
#define MEM(a,x) memset(a,x,sizeof(a))
#define W(a) while(a)
#define gcd(a,b) __gcd(a,b)

#define N 200005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)

#define ll int
#define Word_Len 50005
#define Sigma_size 27

struct node{
	int val;
	int num;
	int flag;
	node *next[Sigma_size];
	node()
	{
		num=0;
		flag=0;
		MEM(next,NULL);
	}
};

node *head;
node *bj;
node *ls;
char In[Word_Len][55];
int idx(char x){return x-'a';}
void init()
{
	head=new node();
}
void insert(char *s)
{
	bj=head;
	for(int i=0;s[i];i++)
	{
		int c=idx(s[i]);
		if(bj->next[c]==NULL)
		{
			bj->next[c]=new node();
		}
		bj=bj->next[c];
		bj->num++;
		bj->val=c;
	}
	bj->flag=1;
}

int query(char *s)
{
	bj=head;
	int flag1=0,dx;
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int c=idx(s[i]);
		if(bj->next[c]==NULL && flag1==0) return 0;
		else if(bj->next[c]==NULL && flag1==1){
			bj=ls;i=dx;
			flag1=0;continue;
		}			
		bj=bj->next[c];
		if(bj->flag==1 && flag1==0) {
			ls=bj;
			bj=head;
			dx=i;
			flag1=1;continue;
		}
		if(i==len-1 && flag1==1)
		{
			if(bj->flag==1)
				return 1;
			else 
			{
				bj=ls;
				i=dx;
				flag1=0;
			}
		}
	}		
	return 0;
}
int cmp1(const void *a,const void*b){  
    char *s1=(char *)a;  
    char *s2=(char *)b;  
    return strcmp(s1,s2);  
}
int main()
{
	int k=0;
	init();
	while(scanf("%s",In[k])!=EOF)
	{
		insert(In[k]);
		k++;
	}
	bj=head;
	//printf("%d %d %d %d %d %d\n",bj->next[0]->flag,bj->next[0]->next[1]->flag,bj->next[0]->next[1]->next[2]->flag,bj->next[1]->flag,bj->next[1]->next[2]->flag,bj->next[1]->next[2]->next[3]->flag);
	qsort(In,k,sizeof(char)*55,cmp1);
	for(int i=0;i<k;i++)
	{
		if(query(In[i]))
		{
			printf("%s",In[i]);
			printf("\n");
		}
	}
	return 0;
}



/*
abcde
abc
de
a
bcd
*/







