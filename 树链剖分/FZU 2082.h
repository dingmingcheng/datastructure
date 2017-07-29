/*
	FZU 2082
	有n座城市，由n-1条路相连通，使得任意两座城市之间可达。每条路有过路费，要交过路费才能通过。每条路的过路费经常会更新，现问你，当前情况下，从城市a到城市b最少要花多少过路费。 
	Sample Input

    2 3
    1 2 1
    1 1 2
    0 1 2
    1 2 1

Sample Output

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
#define N 50010
#define M 50010
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n,m,p,s;
ll val[N];

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
	int v,  next,w;
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

void addEdge(int u, int v,int w) {
	edge[cnt].v = v;
	edge[cnt].next = fir[u];
	edge[cnt].w=w;
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
        if(v!=fa[u])
            val[tid[v]]=edge[i].w;
    }
}

typedef struct node
{
	int left;
	int right;
	ll data;
}node;
node stu[N*8];
void CreateTree(int ii,int a,int b)
{
    stu[ii].left = a;
    stu[ii].right = b;
    if(a == b)
    {
        stu[ii].data=val[a];
        return;
    }
    else
    {
        int mid = (a+b)>>1;
        CreateTree(ii*2,a,mid);
        CreateTree(ii*2+1,mid+1,b);
    }
    stu[ii].data=stu[ii*2].data+stu[ii*2+1].data;
}

void updata(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == a)
    {
        stu[ii].data = (ll)b;
    }
    else
    {
        int mid = (stu[ii].left+stu[ii].right)>>1;
        if(a <= mid)
        {
            updata(ii*2,a,b);
        }
        else
        {
            updata(ii*2+1,a,b);
        }
        stu[ii].data=stu[ii*2].data+stu[ii*2+1].data;
    }
}

ll find1(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == b)
    {
        return stu[ii].data;
    }
    else
    {
        int mid = (stu[ii].left + stu[ii].right)>>1;
        ll ret=0;
        if(b <= mid)
        {
            ret=find1(ii*2,a,b);
        }
        else if(a > mid)
        {
            ret=find1(ii*2+1,a,b);
        }
        else
        {
            ret=find1(ii*2,a,mid)+find1(ii*2+1,mid+1,b);
        }
        return ret;
    }

}
void change(int a,int b)
{
	/*while(top[a]!=top[b])
	{
		if(dep[top[a]]<dep[top[b]]) swap(a,b);
		updata(1,tid[top[a]],tid[a],at);
		a=fa[top[a]];
	}
	if(dep[a]>dep[b]) swap(a,b);
	updata(1,tid[a],tid[b],at);*/
	ll sum=0,ls;
	while(top[a]!=top[b])
    {
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
		sum+=find1(1,tid[top[a]],tid[a]);
		a=fa[top[a]];
    }
    if(tid[a]>tid[b]) swap(a,b);
    if(tid[a]==tid[b])
    {
        printf("%lld\n",sum);
        return;
    }
	sum+=find1(1,tid[son[a]],tid[b]);
    printf("%lld\n",sum);
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
    {
		init();
		val[1]=0;
		for(int i=1;i<=n-1;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addEdge(u,v,w);addEdge(v,u,w);
		}
		dfs1(1,0,0);
		dfs2(1,1);
		CreateTree(1,1,n);
		/*for(int i=1;i<=n;i++)
            printf("%d ",val[i]);
        printf("\n");
		printf("%d\n%d\n",stu[1].data,stu[3].data);*/
		int c1,c2,k;
		for(int i=0;i<m;i++)
		{
		    int a,b,c;
		    scanf("%d",&a);
		    if(a==1)
            {
                scanf("%d%d",&b,&c);
                change(b,c);
            }
            else if(a==0)
            {
                scanf("%d%d",&b,&c);
                int u,v;
                u=edge[2*(b-1)].v;
                v=edge[2*(b-1)+1].v;
                int t;
                if(fa[u]==v)
                {
                    t=tid[u];
                }
                else if(fa[v]==u)
                {
                    t=tid[v];
                }
                updata(1,t,c);
            }
		}
    }
	return 0;
}
/*
7 5 2
1 3 3
1 5 2
3 2 2
3 4 4
5 7 8
5 6 1
*/
