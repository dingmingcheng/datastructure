/**
*
*	POJ2828	
*	题意：有n个人，给出n个人要插入的位置与其价值，输出最后的价值
*	思路：由于整个队列是动态不断变化的，所以我们可以从最后一个插入的人开始逆推出所有人想要插入的队列并对线段树进行更新即可
*
*
*
*
**/
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
#define ll long long
#define N 200005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
#define MAX_N 200000

int big;
typedef struct node
{
    int left;
    int right;
    int data;
    int maxx;
}node;
int flag;
node stu[MAX_N*4];
//int num[MAX_N+1];

int Max(int a,int b)
{
    return a>b?a:b;
}
void pushup(int ii)
{
    stu[ii].data=stu[ii*2].data+stu[ii*2+1].data;
}
void CreateTree(int ii,int a,int b)
{
    stu[ii].left = a;
    stu[ii].right = b;
    stu[ii].maxx = 0;
    if(a == b)
    {
        stu[ii].data = 1;
        return;
    }
    else
    {
        int mid = (a+b)>>1;
        CreateTree(ii*2,a,mid);
        CreateTree(ii*2+1,mid+1,b);
        pushup(ii);
    }
}

void updata(int ii,int a,int b)
{
    if(stu[ii].left==stu[ii].right)
    {
        stu[ii].maxx=b;
        stu[ii].data--;
    }
    else
    {
        if(a<=stu[ii*2].data)
        {
            updata(ii*2,a,b);
        }
        else{
            updata(ii*2+1,a-stu[ii*2].data,b);
        }
        pushup(ii);
    }
}

void find1(int ii)
{
    if(stu[ii].left == stu[ii].right)
    {
        //printf("%d/n",stu[ii].maxx);
        if(flag) printf(" %d",stu[ii].maxx);
        else if(!flag) {printf("%d",stu[ii].maxx);flag=1;}
    }
    else
    {
        int mid = (stu[ii].left + stu[ii].right)>>1;
        find1(ii*2);
        find1(ii*2+1);
    }
}
int pos[MAX_N],val[MAX_N];
int main()
{
    int n,m,num;
    int i;

    while(scanf("%d",&n)!=EOF)
    {
        CreateTree(1,1,n);
        for(i=1;i<=n;i++)
        {
            scanf("%d%d",&pos[i],&val[i]);

        }
        flag=0;
        for(int i=n;i>=1;i--)
        {
            updata(1,pos[i]+1,val[i]);
        }
        find1(1);
        printf("\n");
    }
    return 0;
}
