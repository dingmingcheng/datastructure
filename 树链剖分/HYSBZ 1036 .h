/*
	HYSBZ 1036
	一棵树上有n个节点，编号分别为1到n，每个节点都有一个权值w。我们将以下面的形式来要求你对这棵树完成
	一些操作： I. CHANGE u t : 把结点u的权值改为t II. QMAX u v: 询问从点u到点v的路径上的节点的最大权值 I
	II. QSUM u v: 询问从点u到点v的路径上的节点的权值和 注意：从点u到点v的路径上的节点包括u和v本身
	Sample Input
		4
		1 2
		2 3
		4 1
		4 2 1 3
		12
		QMAX 3 4
		QMAX 3 3
		QMAX 3 2
		QMAX 2 3
		QSUM 3 4
		QSUM 2 1
		CHANGE 1 5
		QMAX 3 4
		CHANGE 3 6
		QMAX 3 4
		QMAX 2 4
		QSUM 3 4

	Sample Output

		4
		1
		2
		2
		10
		6
		5
		6
		5
		16
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
#define N 30005
#define M 30005
#define MOD 1000000007
#define INF 0x7FFFFFFF
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n,m,p;
int val[N];

int tim;
int siz[N],top[N],son[N];
int dep[N],tid[N],rank1[N],fa[N];
/*siz[]数组，用来保存以x为根的子树节点个数
top[]数组，用来保存当前节点的所在链的顶端节点
son[]数组，用来保存重儿子
dep[]数组，用来保存当前节点的深度
fa[]数组，用来保存当前节点的父亲
tid[]数组，用来保存树中每个节点剖分后的新编号
rank[]数组，用来保存当前节点在线段树中的位置*/
struct Edge {
	int v,  next;
};
Edge edge[(N + M) << 1];
int fir[N + M];
int cnt;

void init() {
	cnt = 0;
	tim=0;
	memset(fir, -1, sizeof(fir));
	memset(son,-1,sizeof(son));
}

void addEdge(int u, int v) {
	edge[cnt].v = v;
	edge[cnt].next = fir[u];
	fir[u] = cnt++;
}
void dfs1(int u,int father,int d)
{
    dep[u]=d;
    fa[u]=father;
    siz[u]=1;
    for(int i=fir[u];~i;i=edge[i].next)
    {
        int v=edge[i].v;
        if(v!=father)
        {
            dfs1(v,u,d+1);
            siz[u]+=siz[v];
            if(son[u]==-1||siz[v]>siz[son[u]])
                son[u]=v;
        }
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    tid[u]=++tim;
    rank1[tid[u]]=u;
    if(son[u]==-1) return;
    dfs2(son[u],tp);
    for(int i=fir[u];~i;i=edge[i].next)
    {
        int v=edge[i].v;
        if(v!=son[u]&&v!=fa[u])
            dfs2(v,v);
    }
}

typedef struct node
{
	int left;
	int right;
	ll data;
	int maxx;
}node;
node stu[N*8];
void CreateTree(int ii, int a, int b)
{
	stu[ii].left = a;
	stu[ii].right = b;
	if (a == b)
	{
		stu[ii].data = val[rank1[a]];
		stu[ii].maxx=val[rank1[a]];
		return;
	}
	else
	{
		int mid = (a + b) >> 1;
		CreateTree(ii * 2, a, mid);
		CreateTree(ii * 2 + 1, mid + 1, b);
	}
	stu[ii].data = stu[ii * 2].data + stu[ii * 2 + 1].data;
	stu[ii].maxx=max(stu[ii*2].maxx,stu[ii*2+1].maxx);
}
void updata(int ii, int a, int b, int at)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		stu[ii].data=(ll)at;
		stu[ii].maxx=at;
		return;
	}
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
    stu[ii].maxx=max(stu[ii*2].maxx,stu[ii*2+1].maxx);
}
ll find1(int ii, int a, int b)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		return stu[ii].data;
	}
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
		return find1(ii * 2, a, mid)+find1(ii * 2 + 1, mid + 1, b);
	}
}
int find2(int ii, int a, int b)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		return stu[ii].maxx;
	}
	int mid = (stu[ii].left + stu[ii].right) >> 1;
	if (b <= mid)
	{
		return find2(ii * 2, a, b);
	}
	else if (a > mid)
	{
		return find2(ii * 2 + 1, a, b);
	}
	else
	{
		return max(find2(ii * 2, a, mid),find2(ii * 2 + 1, mid + 1, b));
	}
}
void change1(int x,int y)
{
    ll sum=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        sum+=find1(1,tid[top[x]],tid[x]);
        x=fa[top[x]];
    }
    if(tid[x]>tid[y]) swap(x,y);
    sum+=find1(1,tid[x],tid[y]);
    printf("%lld\n",sum);
}
void change2(int x,int y)
{
    int sum=-INF;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        sum=max(sum,find2(1,tid[top[x]],tid[x]));
        x=fa[top[x]];
    }
    if(tid[x]>tid[y]) swap(x,y);
    sum=max(sum,find2(1,tid[x],tid[y]));
    printf("%d\n",sum);
}
int main()
{
	scanf("%d",&n);
		init();

		for(int i=1;i<=n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			addEdge(u,v);addEdge(v,u);
		}
		for(int i=1;i<=n;i++) scanf("%d",&val[i]);
		dfs1(1,0,0);
		dfs2(1,1);
		CreateTree(1,1,n);
		int c1,c2,k;
		int p;
		scanf("%d",&p);
		for(int i=0;i<p;i++)
		{
		    int a,b,c;
			char xt[10];
			scanf("%s",xt);
			scanf("%d%d",&a,&b);
			if(xt[1]=='S')
			{
				change1(a,b);
			}
			else if(xt[1]=='M')
			{
				change2(a,b);
			}
			else if(xt[1]=='H')
			{
				updata(1,tid[a],tid[a],b);
			}
		}

	return 0;
}

