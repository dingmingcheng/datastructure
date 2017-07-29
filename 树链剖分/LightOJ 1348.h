/*
	LightOJ 1348
	题意：一棵树，有n个点，每个点都有一个权值，有两种操作，0 a b ，问从节点a到节点b路径上所有点权值和，1 a b，把节点a权值改为b。 
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
    int cas;
    scanf("%d",&cas);
    for(int _t=1;_t<=cas;_t++)
    {
        scanf("%d",&n);
		init();
        for(int i=1;i<=n;i++) scanf("%d",&val[i]);
		for(int i=1;i<=n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			u+=1;v+=1;
			addEdge(u,v);addEdge(v,u);
		}

		dfs1(1,0,0);
		dfs2(1,1);
		CreateTree(1,1,n);
		int c1,c2,k;
		int p;
		scanf("%d",&p);
		printf("Case %d:\n",_t);
		for(int i=0;i<p;i++)
		{
		    int a,b,c;
			char xt[10];
			scanf("%d",&c);
			scanf("%d%d",&a,&b);
			if(c==0)
			{
			    a++;
			    b++;
				change1(a,b);
			}

			else if(c==1)
			{
			    a++;
				updata(1,tid[a],tid[a],b);
			}
		}
    }
	return 0;
}
