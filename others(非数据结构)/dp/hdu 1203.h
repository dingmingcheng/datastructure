/*
	HDU 1203
	Input
    输入有若干组数据，每组数据的第一行有两个正整数n,m(0<=n<=10000,0<=m<=10000)
    后面的m行，每行都有两个数据ai(整型),bi(实型)分别表示第i个学校的申请费用和可能拿到offer的概率。
    输入的最后有两个0。
	Output
		每组数据都对应一个输出，表示Speakless可能得到至少一份offer的最大概率。用百分数表示，精确到小数点后一位。
	Sample Input

		10 3
		4 0.1
		4 0.2
		5 0.3
		0 0

	Sample Output
		44.0%


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
#define N 100005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n,w;
double dp[N];
int val[N];
double num[N];
int main()
{
    int cas;
    while(scanf("%d%d",&w,&n))
    {
    	if(n==0 && w==0)
    	{
    		break;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d%lf",&val[i],&num[i]);
			num[i]=1-num[i];
		}
		for(int i=0;i<N;i++)
		{
			dp[i]=1;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=w;j>=val[i];j--)
			{
				dp[j]=min(dp[j],dp[j-val[i]]*num[i]);
			}
		}
		printf("%.1lf%%\n",(1-dp[w])*100);
    }
    return 0;
}





