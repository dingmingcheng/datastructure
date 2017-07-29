/*
	HDU2955
	
	先是给出几组数据，每组数据第一行是总被抓概率p(最后求得的总概率必须小于他，否则被抓)，然后是想抢的银行数n。
	然后n行，每行分别是该银行能抢的钱数m[i]和被抓的概率p[i]，求最大逃跑概率。被抓的概率越大，逃跑概率越小。
	Sample Input

		3
		0.04 3
		1 0.02
		2 0.03
		3 0.05
		0.06 3
		2 0.03
		2 0.03
		3 0.05
		0.10 3
		1 0.03
		2 0.02
		3 0.05

	Sample Output

		2
		4
		6
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
int mon[N],n;
double cath[N],dp[N*N],pro;
int main()
{
    int cas;
    scanf("%d",&cas);
    while(cas--)
    {
    	MEM(dp,0);
    	scanf("%lf%d",&pro,&n);
    	pro=1-pro;
    	int sum=0;
    	for(int i=1;i<=n;i++)
    	{
    		scanf("%d%lf",&mon[i],&cath[i]);
    		cath[i]=1-cath[i];
    		sum+=mon[i];
		}
		dp[0]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=sum;j>=mon[i];j--)
			{
				dp[j]=max(dp[j],dp[j-mon[i]]*cath[i]);
			}
		}
		for(int i=sum;i>=0;i--)
		{
			if(dp[i]>pro)
			{
				printf("%d\n",i);
				break;
			}
		}
    }
    return 0;
}

