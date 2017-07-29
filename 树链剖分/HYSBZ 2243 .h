/*
	HYSBZ 2243 
	给定一棵有n个节点的无根树和m个操作，操作有2类：

	1、将节点a到节点b路径上所有点都染成颜色c；

	2、询问节点a到节点b路径上的颜色段数量（连续相同颜色被认为是同一段），如“ 112221 ” 由3段组成：“ 11 ” 、“ 222 ” 和“ 1 ” 。

	请你写一个程序依次完成这m个操作。
	Sample Input
		6 5
		2 2 1 2 1 1
		1 2
		1 3
		2 4
		2 5
		2 6
		Q 3 5
		C 2 1 1
		Q 3 5
		C 5 1 2
		Q 3 5
	Sample Output
		3
		1
		2
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
#define N 100010
#define M 100010
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n,m,p;
int val[N];
int mark;
int tim;
int siz[N],top[N],son[N];
int dep[N],tid[N],rank1[N],fa[N];
int ct[2];
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
	int zuo,you,seg;
	int lazy;
}node;
node stu[N*8];
void pushudown(int rt)
{
	if (stu[rt].lazy)
	{
		stu[rt * 2].lazy = stu[rt].lazy;
		stu[rt * 2 + 1].lazy = stu[rt].lazy;
		stu[rt*2].seg=1;
		stu[rt*2+1].seg=1;
		stu[rt*2].zuo=stu[rt].lazy;
		stu[rt*2].you=stu[rt].lazy;
		stu[rt*2+1].zuo=stu[rt].lazy;
		stu[rt*2+1].you=stu[rt].lazy;
		stu[rt].lazy = 0;
	}
}
void pushup(int ii)
{
    stu[ii].zuo=stu[ii*2].zuo;
    stu[ii].you=stu[ii*2+1].you;
    stu[ii].seg=stu[ii*2].seg+stu[ii*2+1].seg;
    if(stu[ii*2].you==stu[ii*2+1].zuo)
        stu[ii].seg-=1;
}
void CreateTree(int ii, int a, int b)
{
	stu[ii].left = a;
	stu[ii].right = b;
	stu[ii].lazy = 0;
	if (a == b)
	{
		stu[ii].zuo = val[rank1[a]];
		stu[ii].you=val[rank1[a]];
		stu[ii].seg=1;
		return;
	}
	else
	{
		int mid = (a + b) >> 1;
		CreateTree(ii * 2, a, mid);
		CreateTree(ii * 2 + 1, mid + 1, b);
	}
	pushup(ii);
}
void updata(int ii, int a, int b, int at)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		stu[ii].lazy = at;
		stu[ii].you=at;
		stu[ii].zuo=at;
		stu[ii].seg=1;
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
	pushup(ii);
}
int find1(int ii, int a, int b)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		return stu[ii].seg;
	}
	pushudown(ii);
	int k;
	int mid = (stu[ii].left + stu[ii].right) >> 1;
	if (b <= mid)
	{
		k=find1(ii * 2, a, b);
	}
	else if (a > mid)
	{
		k=find1(ii * 2 + 1, a, b);
	}
	else
	{
	    k=find1(ii * 2, a, mid)+find1(ii * 2 + 1, mid + 1, b);
		if(stu[ii*2].you==stu[ii*2+1].zuo)
            k--;
	}
	pushup(ii);
	return k;
}
int find2(int ii, int a, int b)
{
	if (stu[ii].left == a && stu[ii].right == b)
	{
		return stu[ii].you;
	}
	pushudown(ii);
	int k;
	int mid = (stu[ii].left + stu[ii].right) >> 1;
	if (b <= mid)
	{
		k=find2(ii * 2, a, b);
	}
	else
	{
		k=find2(ii * 2 + 1, a, b);
	}
	pushup(ii);
	return k;
}
void change(int a,int b,int at)
{
    int sum;
    mark=0;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]<dep[top[b]]) swap(a,b);
		updata(1,tid[top[a]],tid[a],at);
		a=fa[top[a]];
	}
	if(dep[a]>dep[b]) swap(a,b);
	updata(1,tid[a],tid[b],at);
}
void change1(int a,int b)
{
    int sum=0;
    mark=0;    ct[1]=-1;
	while(top[a]!=top[b])
	{
		if(dep[top[a]]<dep[top[b]]) {swap(a,b);}
		sum+=find1(1,tid[top[a]],tid[a]);
		if(find2(1,tid[fa[top[a]]],tid[fa[top[a]]])==find2(1,tid[top[a]],tid[top[a]])) sum--;
		a=fa[top[a]];

	}
	if(dep[a]>dep[b]) swap(a,b);
	sum+=find1(1,tid[a],tid[b]);
	printf("%d\n",sum);
}
int main()
{
	scanf("%d%d",&n,&m);
		init();
		for(int i=1;i<=n;i++) scanf("%d",&val[i]);
		for(int i=1;i<=n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			addEdge(u,v);addEdge(v,u);
		}
		dfs1(1,0,0);
		dfs2(1,1);
		CreateTree(1,1,n);
		int a,b,c;
		for(int i=0;i<m;i++)
		{
			char xt[2];
			scanf("%s",xt);
			if(xt[0]=='C')
			{
                scanf("%d%d%d",&a,&b,&c);
                change(a,b,c);
			}
			else if(xt[0]=='Q')
			{
				scanf("%d%d",&a,&b);
				change1(a,b);
			}
		}
	
	return 0;
}

