/*
	hdu 2546
	Input
		多组数据。对于每组数据：
		第一行为正整数n，表示菜的数量。n<=1000。
		第二行包括n个正整数，表示每种菜的价格。价格不超过50。
		第三行包括一个正整数m，表示卡上的余额。m<=1000。
		n=0表示数据结束。
	Output
		对于每组输入,输出一行,包含一个整数，表示卡上可能的最小余额。
	Sample Input

		1
		50
		5
		10
		1 2 3 2 1 1 2 3 2 1
		50
		0
	Sample Output
		-45
		32
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
#define N 1005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n,w;
int val[N];
int dp[N][N];
int main()
{
    int cas;
    while(scanf("%d",&n))
    {
    	if(n==0)
    	{
    		break;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&val[i]);
		}
		MEM(dp,0);
		sort(val+1,val+n+1);
		scanf("%d",&w);
		if(w<5)
		{
			printf("%d\n",w);
			continue;
		}
		for(int i=1;i<n;i++)
		{
			for(int j=0;j<=w-5;j++)
			{
				if(j>=val[i])
				{
					dp[i][j]=max(dp[i-1][j],dp[i-1][j-val[i]]+val[i]);
				}
				else 
				{
					dp[i][j]=dp[i-1][j];
				}
			}
		}
		/*for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=w;j++)
			{
				printf("%d ",dp[i][j]);
			}
			printf("\n");
		}*/
		printf("%d\n",w-(dp[n-1][w-5]+val[n]));
    }
    return 0;
}





