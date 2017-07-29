/*
	HDU 3966
	题意：给一棵树，并给定各个点权的值，然后有3种操作：
	I C1 C2 K: 把C1与C2的路径上的所有点权值加上K
	D C1 C2 K：把C1与C2的路径上的所有点权值减去K
	Q C：查询节点编号为C的权值
	树链剖分+线段树
	Sample Input

		3 2 5
		1 2 3
		2 1
		2 3
		I 1 3 5
		Q 2
		D 1 2 2
		Q 1 
		Q 3

	Sample Output

		7
		4
		8
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
#define UP(i,x,y) for(int i=x;i<=y;i++)
#define DOWN(i,x,y) for(int i=x;i>=y;i--)
#define MEM(a,x) memset(a,x,sizeof(a))
#define W(a) while(a)
#define gcd(a,b) __gcd(a,b)
#define ll long long
#define N 80000
#define M 80000
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n, m, p;
struct Edge {
	int v, next;
};
Edge edge[(N + M) << 1];
int fir[N + M];
int cnt,tim;

int siz[N], top[N], son[N];//N代表节点个数
int dep[N], tid[N], rank1[N], fa[N];
void init() {
	cnt = 0;
	tim = 0;
	memset(fir, -1, sizeof(fir));
	memset(son, -1, sizeof(son));
}

void addEdge(int u, int v) {
	edge[cnt].v = v;
	edge[cnt].next = fir[u];
	fir[u] = cnt++;
}


/*siz[]数组，用来保存以x为根的子树节点个数
top[]数组，用来保存当前节点的所在链的顶端节点
son[]数组，用来保存重儿子
dep[]数组，用来保存当前节点的深度
fa[]数组，用来保存当前节点的父亲
tid[]数组，用来保存树中每个节点剖分后的新编号
rank[]数组，用来保存当前节点在线段树中的位置*/

void dfs1(int u, int father, int d)
{
	dep[u] = d;
	fa[u] = father;
	siz[u] = 1;
	for (int i = fir[u];~i;i = edge[i].next)
	{
		int v = edge[i].v;
		if (v != father)
		{
			dfs1(v, u, d + 1);
			siz[u] += siz[v];
			if (son[u] == -1 || siz[v]>siz[son[u]])
				son[u] = v;
		}
	}
}

void dfs2(int u, int tp)
{
	top[u] = tp;
	tid[u] = ++tim;
	rank1[tid[u]] = u;
	if (son[u] == -1) return;
	dfs2(son[u], tp);
	for (int i = fir[u];~i;i = edge[i].next)
	{
		int v = edge[i].v;
		if (v != son[u] && v != fa[u])
			dfs2(v, v);
	}
}
__int64 val[N];
char op[5];
#define MAX_N 100005

int big;
typedef struct node
{
	int left;
	int right;
	__int64 data;
	int maxx;
	__int64 lazy;
}node;
int a1[MAX_N];
node stu[MAX_N * 4];

void pushudown(int rt)
{
	if (stu[rt].lazy)
	{
		stu[rt * 2].lazy += stu[rt].lazy;
		stu[rt * 2 + 1].lazy += stu[rt].lazy;
		stu[rt * 2].data += (stu[rt * 2].right - stu[rt * 2].left + 1)*stu[rt].lazy;
		stu[rt * 2 + 1].data += (stu[rt * 2 + 1].right - stu[rt * 2 + 1].left + 1)*stu[rt].lazy;
		stu[rt].lazy = 0;
	}
}
void CreateTree(int ii, int a, int b)
{
	stu[ii].left = a;
	stu[ii].right = b;
	stu[ii].lazy = 0;

	if (a == b)
	{
		stu[ii].data = val[rank1[a]];
		return;
	}
	else
	{
		int mid = (a + b) >> 1;
		CreateTree(ii * 2, a, mid);
		CreateTree(ii * 2 + 1, mid + 1, b);
	}
	stu[ii].data = stu[ii * 2].data + stu[ii * 2 + 1].data;
}

void updata(int ii, int a, int b, int at)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		stu[ii].lazy += at;
		stu[ii].data += (__int64)(b - a + 1)*at;
		return;
	}
	pushudown(ii);
	int mid = (stu[ii].left + stu[ii].right) >> 1;
	if (b <= mid)
	{
		updata(ii * 2, a, b, at);
	}
	else if (a>mid)
	{
		updata(ii * 2 + 1, a, b, at);
	}
	else
	{
		updata(ii * 2, a, mid, at);
		updata(ii * 2 + 1, mid + 1, b, at);
	}
	stu[ii].data = stu[ii * 2].data + stu[ii * 2 + 1].data;
}
__int64 find1(int ii, int a, int b)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		return stu[ii].data;
	}
	pushudown(ii);
	int mid = (stu[ii].left + stu[ii].right) >> 1;
	if (b <= mid)
	{
		return find1(ii * 2, a, b);
	}
	else if (a > mid)
	{
		return find1(ii * 2 + 1, a, b);
	}
	else
	{
		return find1(ii * 2, a, mid) + find1(ii * 2 + 1, mid + 1, b);
	}
	stu[ii].data = stu[ii * 2].data + stu[ii * 2 + 1].data;
}
void change(int a, int b, int at)
{
	while (top[a] != top[b])
	{
		if (dep[top[a]]<dep[top[b]]) swap(a, b);
		//printf("%d %d\n", tid[top[a]], tid[a]);
		updata(1, tid[top[a]], tid[a], at);
		a = fa[top[a]];
	}
	if (dep[a]>dep[b]) swap(a, b);
	//printf("%d %d\n", tid[a], tid[b]);
	updata(1, tid[a], tid[b], at);
}
int main()
{
	while (scanf("%d%d%d", &n, &m, &p) != EOF)
	{
		UP(i, 1, n) scanf("%I64d",&val[i]);
		init();
		for (int i = 0;i < m;i++)
		{
			int u, v;
			scanf("%d%d",&u,&v);
			addEdge(u,v);
			addEdge(v,u);
		}
		dfs1(1, 0, 0);
		dfs2(1, 1);
		CreateTree(1,1,n);
		while (p--)
		{
			scanf("%s", op);
			if (op[0] == 'I')
			{
				int c1, c2, k;
				scanf("%d%d%d",&c1,&c2,&k);
				change(c1,c2,k);
			}
			else if (op[0] == 'D')
			{
				int c1, c2, k;
				scanf("%d%d%d", &c1, &c2, &k);
				change(c1, c2, -k);
			}
			else if (op[0] == 'Q')
			{
				int c1;
				scanf("%d",&c1);
				printf("%lld\n",find1(1,tid[c1],tid[c1]));
			}
		}
	}
	return 0;
}
/*
3 2 5
1 2 3
2 1
2 3
I 1 3 5
Q 2
D 1 2 2
Q 1
Q 3
*/