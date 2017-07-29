/*
	POJ 2001
	给出n个单词（1<=n<=1000），求出每个单词的非公共前缀，如果没有，则输出自己。
	
	Sample Input

		carbohydrate
		cart
		carburetor
		caramel
		caribou
		carbonic
		cartilage
		carbon
		carriage
		carton
		car
		carbonate

	Sample Output

		carbohydrate carboh
		cart cart
		carburetor carbu
		caramel cara
		caribou cari
		carbonic carboni
		cartilage carti
		carbon carbon
		carriage carr
		carton carto
		car car
		carbonate carbona


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
#define Word_Len 1000005
#define Sigma_size 27
string b;
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

void query(char *s)
{
	bj=head;
	b="";
	int k=0;
	int flag1=0,dx;
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int c=idx(s[i]);
		bj=bj->next[c];
		if(bj->num==1)
        {
            b+=bj->val+'a';
            break;
        }
        b+=bj->val+'a';
	}
}
char a[1005][30];
int main()
{
    init();
    int k=0;
    while(scanf("%s",a[k++])!=EOF)
    {
        insert(a[k-1]);
    }
    for(int i=0;i<k;i++)
    {
        query(a[i]);
        printf("%s ",a[i]);
        cout<<b;
        printf("\n");
    }
    return 0;
}
