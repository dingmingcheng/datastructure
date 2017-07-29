/*
	HDU 2120 并查集
	查找一个图里面有几个环。
	8 10
	0 1
	1 2
	1 3
	2 4
	3 4
	0 5
	5 6
	6 7
	3 6
	4 7
	output:3

*/
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
int p[N];
int n, m;
void init()
{
	for (int i = 0;i < N;i++)
	{
		p[i] = i;
	}
}
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
int main()
{
	while (scanf("%d%d",&n,&m) != EOF)
	{
		int u, v;
		int sum = 0;
		init();
		while (m--)
		{
			scanf("%d%d", &u, &v);
			int x, y;
			x = find(u);
			y = find(v);
			if (x == y) sum++;
			else p[x] = y;
		}
		printf("%d\n",sum);
	}
	return 0;
}