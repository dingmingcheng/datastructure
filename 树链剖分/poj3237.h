/*
	POJ3237
	题目大意：指定一颗树上有3个操作：询问操作,询问a点和b点之间的路径上最长的那条边的长度；取反操作，将a点和b点之间的路径权值都取相反数；变化操作，把某条边的权值变成指定的值。
	Sample Input

		1

		3
		1 2 1
		2 3 2
		QUERY 1 2
		CHANGE 1 3
		QUERY 1 2
		DONE

	Sample Output

		1
		3
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
#define N 10100
#define M 10100
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
int n,m,p,s;
int val[N];

int tim;
int siz[N],top[N],son[N];
int dep[N],tid[N],rank1[N],fa[N];
struct Edge {
	int v, next,w;
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
	int maxx;
	int minn;
	int lazy;
}node;
node stu[N*8];
void pushudown(int rt)
{
    if(stu[rt].left==stu[rt].right) return;
	if (stu[rt].lazy)
	{
		stu[rt * 2].maxx*=-1;
		stu[rt * 2].minn*=-1;
		stu[rt * 2+1].maxx*=-1;
		stu[rt * 2+1].minn*=-1;
		swap(stu[rt * 2].maxx,stu[rt * 2].minn);
		swap(stu[rt * 2+1].maxx,stu[rt * 2+1].minn);
		stu[rt * 2].lazy ^= 1;
		stu[rt * 2 + 1].lazy ^= 1;
		stu[rt].lazy = 0;
	}
}
void CreateTree(int ii,int a,int b)
{
    stu[ii].left = a;
    stu[ii].right = b;
    stu[ii].lazy=0;
    if(a == b)
    {
        stu[ii].maxx=val[a];
        stu[ii].minn=val[a];
        if(a==1) {stu[ii].minn=INF;stu[ii].maxx=-INF;}
        return;
    }
    else
    {
        int mid = (a+b)>>1;
        CreateTree(ii*2,a,mid);
        CreateTree(ii*2+1,mid+1,b);
    }
    stu[ii].maxx=max(stu[ii*2].maxx,stu[ii*2+1].maxx);
    stu[ii].minn=min(stu[ii*2].minn,stu[ii*2+1].minn);

}
void negate1(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == b)
    {
        stu[ii].lazy ^= 1;
        stu[ii].maxx*=-1;
        stu[ii].minn*=-1;
        swap(stu[ii].maxx,stu[ii].minn);
    }
    else
    {
        pushudown(ii);
        int mid = (stu[ii].left + stu[ii].right)>>1;
        int ret;
        if(b <= mid)
        {
            negate1(ii*2,a,b);
        }
        else if(a > mid)
        {
            negate1(ii*2+1,a,b);
        }
        else
        {
            negate1(ii*2,a,mid);
            negate1(ii*2+1,mid+1,b);
        }
        stu[ii].maxx=max(stu[ii*2].maxx,stu[ii*2+1].maxx);
        stu[ii].minn=min(stu[ii*2].minn,stu[ii*2+1].minn);
    }
}
void updata(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == a)
    {
        stu[ii].lazy=0;
        stu[ii].maxx=b;
        stu[ii].minn=b;
    }
    else
    {
        pushudown(ii);
        int mid = (stu[ii].left+stu[ii].right)>>1;
        if(a <= mid)
        {
            updata(ii*2,a,b);
        }
        else
        {
            updata(ii*2+1,a,b);
        }
        stu[ii].maxx=max(stu[ii*2].maxx,stu[ii*2+1].maxx);
        stu[ii].minn=min(stu[ii*2].minn,stu[ii*2+1].minn);
    }
}

int find1(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == b)
    {
        return stu[ii].maxx;
    }
    else
    {
        pushudown(ii);
        int mid = (stu[ii].left + stu[ii].right)>>1;
        int ret;
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
            ret=max(find1(ii*2,a,mid),find1(ii*2+1,mid+1,b));
        }
        return ret;
    }

}
void change(int a,int b)
{
	int sum=-INF,ls;
	while(top[a]!=top[b])
    {
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
		sum=max(sum,find1(1,tid[top[a]],tid[a]));
		a=fa[top[a]];
    }
    if(tid[a]>tid[b]) swap(a,b);
    if(tid[a]==tid[b])
    {
        printf("%d\n",sum);
        return;
    }
	sum=max(sum,find1(1,tid[son[a]],tid[b]));
    printf("%d\n",sum);
    return;
}
void change1(int a,int b)
{
	while(top[a]!=top[b])
    {
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
		negate1(1,tid[top[a]],tid[a]);
		a=fa[top[a]];
    }
    if(tid[a]>tid[b]) swap(a,b);
    if(tid[a]==tid[b])
    {
        return;
    }
	negate1(1,tid[son[a]],tid[b]);
	return;
}
int main()
{
    int cas;
    char ju[20];
    scanf("%d",&cas);
    while(cas--)
    {
        scanf("%d",&n);
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
		printf("%d\n%d\n",stu[1].maxx,stu[5].maxx);*/
		//printf("%d %d\n",stu[4].minn,stu[4].maxx);
		int c1,c2,k;
		while(1)
		{
		    int a,b,c;
		    scanf("%s",ju);

		    if(ju[0]=='D')
                break;
		    else if(ju[0]=='Q')
            {
                scanf("%d%d",&a,&b);
                change(a,b);
            }
            else if(ju[0]=='N')
            {
                scanf("%d%d",&a,&b);
                change1(a,b);
            }
            else if(ju[0]=='C')
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
                //printf("%d**\n",t);
                updata(1,t,c);
            }
            //printf("%d %d\n",stu[5].minn,stu[5].maxx);
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
/*
1

3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
NEGATE 1 2
QUERY 1 2
*/
