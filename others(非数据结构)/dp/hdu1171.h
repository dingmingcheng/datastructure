/*
	HDU 1171
	题意：给出每个物体的价值和物体的数量，如何分使得A,B所得价值最接近并且A的价值不能小于B
	思路：将总和平分后，就是一道01背包题了
	Sample Input

	2
	10 1
	20 1
	3
	10 1 
	20 2
	30 1
	-1

	 

	Sample Output

	20 10
	40 40


*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int val[5005];
int dp[255555];

int main()
{
    int n,i,j,a,b,l,sum;
    while(~scanf("%d",&n),n>0)
    {
        memset(val,0,sizeof(val));
        memset(dp,0,sizeof(dp));
        l = 0;
        sum = 0;
        for(i = 0;i<n;i++)
        {
            scanf("%d%d",&a,&b);
            while(b--)
            {
                val[l++] = a;//将价值存入数组
                sum+=a;
            }
        }
        for(i = 0;i<l;i++)
        {
            for(j = sum/2;j>=val[i];j--)//01背包
            {
                dp[j] = max(dp[j],dp[j-val[i]]+val[i]);
            }
        }
        printf("%d %d\n",sum-dp[sum/2],dp[sum/2]);
    }

    return 0;
}
