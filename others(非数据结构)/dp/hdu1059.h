/*
	HDU 1059
	1、2、3、4、5、6的石头若干块，块数已知，问能否将这些石头分成两堆，且两堆价值相等。
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
#define ll long long
#define N 105
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)

const int MAX=100010;
int dp[MAX];
int val[MAX],num[MAX];
int v;
 
void ZeroOnePack(int cost,int wei)//01
{
    int i;
    for(i = v; i>=cost; i--)
    {
        dp[i] = max(dp[i],dp[i-cost]+wei);
    }
}
 
void CompletePack(int cost,int wei)//完全
{
    int i;
    for(i = cost; i<=v; i++)
    {
        dp[i] = max(dp[i],dp[i-cost]+wei);
    }
}
 
void MultiplePack(int cost,int wei,int cnt)//多重
{
    if(v<=cnt*cost)//如果总容量比这个物品的容量要小，那么这个物品可以直到取完，相当于完全背包
    {
        CompletePack(cost,wei);
        return ;
    }
    else//否则就将多重背包转化为01背包
    {
        int k = 1;
        while(k<=cnt)
        {
            ZeroOnePack(k*cost,k*wei);
            cnt = cnt-k;
            k = 2*k;
        }
        ZeroOnePack(cnt*cost,cnt*wei);
    }
}

int main()
{
	int n,m;
	int cas=0;
	for(int i=1;i<=6;i++)
	{
		val[i]=i;
	}
	while(1)
	{
		int flag=1;				
		int sum=0;
		for(int i=1;i<=6;i++)
		{
			scanf("%d",&num[i]);
			sum+=i*num[i];
		}
		
		for(int i=1;i<=6;i++)
		{
			if(num[i]!=0)
			{
				flag=0;
				break;
			}
		}
		if(flag==1) break;
		
		MEM(dp,0);
		
		v=sum/2;
		for(int i=1;i<=6;i++)
		{
			if(num[i]!=0)
				MultiplePack(val[i],val[i],num[i]);
		}
		if(sum-dp[v]==dp[v])
		{
			flag=0;
		}
		else flag=1;
		printf("Collection #%d:\n",++cas);
		if(flag==1)
		{
			printf("Can't be divided.\n\n");
		}
		else
		{
			printf("Can be divided.\n\n");
		}
	}
	return 0;
}