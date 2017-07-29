/**
*		poj 3481 Double Queue 
*
*	一些数据分别有名字K和优先级P，要求维护一个数据结构可以执行三种操作：插入数据；弹出优先级最高的数据；弹出优先级最低的数据。
*	输入：
* 	0. 0，结束操作
*	1. 1 k p，把一个客户k加入到队列中，优先级为p
*	2. 2， 把队列中优先级最高的客户取出来
*	3. 3， 把队列中优先级最低的客户取出来
*	可用堆实现，这里用了splay tree
**/

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
#define MAXN 100005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)

int cnt, rt;
int Add[MAXN];

struct Tree{
	int key, num, size, fa, son[2],ans;
}T[MAXN];

inline void PushUp(int x)
{
	T[x].size=T[T[x].son[0]].size+T[T[x].son[1]].size+T[x].num;
}

inline void PushDown(int x)
{
	if(Add[x])
	{
		if(T[x].son[0])
		{
			T[T[x].son[0]].key+=Add[x];
			Add[T[x].son[0]]+=Add[x];
		}
		if(T[x].son[1])
		{
			T[T[x].son[1]].key+=Add[x];
			Add[T[x].son[1]]+=Add[x];
		}
		Add[x]=0;
	}
}

inline int Newnode(int key, int fa,int num) //新建一个节点并返回
{
	++cnt;
	T[cnt].key=key;
	T[cnt].num=T[cnt].size=1;
	T[cnt].ans=num;
	T[cnt].fa=fa;
	T[cnt].son[0]=T[cnt].son[1]=0;
	return cnt;
}

inline void Rotate(int x, int p) //0左旋 1右旋
{
	int y=T[x].fa;
	PushDown(y);
	PushDown(x);
	T[y].son[!p]=T[x].son[p];
	T[T[x].son[p]].fa=y;
	T[x].fa=T[y].fa;
	if(T[x].fa)
		T[T[x].fa].son[T[T[x].fa].son[1] == y]=x;
	T[x].son[p]=y;
	T[y].fa=x;
	PushUp(y);
	PushUp(x);
}

void Splay(int x, int To) //将x节点移动到To的子节点中
{
	while(T[x].fa != To)
	{
		if(T[T[x].fa].fa == To)
			Rotate(x, T[T[x].fa].son[0] == x);
		else
		{
			int y=T[x].fa, z=T[y].fa;
			int p=(T[z].son[0] == y);
			if(T[y].son[p] == x)
				Rotate(x, !p), Rotate(x, p); //之字旋
			else
				Rotate(y, p), Rotate(x, p); //一字旋
		}
	}
	if(To == 0) rt=x;
}

int GetPth(int p, int To) //返回第p小的节点 并移动到To的子节点中
{
	if(!rt || p > T[rt].size) return 0;
	int x=rt;
	while(x)
	{
		PushDown(x);
		if(p >= T[T[x].son[0]].size+1 && p <= T[T[x].son[0]].size+T[x].num)
			break;
		if(p > T[T[x].son[0]].size+T[x].num)
		{
			p-=T[T[x].son[0]].size+T[x].num;
			x=T[x].son[1];
		}
		else
			x=T[x].son[0];
	}
	Splay(x, 0);
	return x;
}

int Find(int key) //返回值为key的节点 若无返回0 若有将其转移到根处
{
	if(!rt) return 0;
	int x=rt;
	while(x)
	{
		PushDown(x);
		if(T[x].key == key) break;
		x=T[x].son[key > T[x].key];
	}
	if(x) Splay(x, 0);
	return x;
}

int Prev() //返回根节点的前驱 非重点
{
	if(!rt || !T[rt].son[0]) return 0;
	int x=T[rt].son[0];
	while(T[x].son[1])
	{
		PushDown(x);
		x=T[x].son[1];
	}
	Splay(x, 0);
	return x;
}

int Succ() //返回根结点的后继 非重点
{
	if(!rt || !T[rt].son[1]) return 0;
	int x=T[rt].son[1];
	while(T[x].son[0])
	{
		PushDown(x);
		x=T[x].son[0];
	}
	Splay(x, 0);
	return x;
}

void Insert(int key,int num) //插入key值
{
	if(!rt)
		rt=Newnode(key, 0,num);
	else
	{
		int x=rt, y=0;
		while(x)
		{
			PushDown(x);
			y=x;
			if(T[x].key == key)
			{
				T[x].num++;
				T[x].size++;
				break;
			}
			T[x].size++;
			x=T[x].son[key > T[x].key];
		}
		if(!x)
			x=T[y].son[key > T[y].key]=Newnode(key, y,num);
		Splay(x, 0);
	}
}

void Delete(int key) //删除值为key的节点1个
{
	int x=Find(key);
	if(!x) return;
	if(T[x].num>1)
	{
		T[x].num--;
		PushUp(x);
		return;
	}
	int y=T[x].son[0];
	while(T[y].son[1])
		y=T[y].son[1];
	int z=T[x].son[1];
	while(T[z].son[0])
		z=T[z].son[0];
	if(!y && !z)
	{
		rt=0;
		return;
	}
	if(!y)
	{
		Splay(z, 0);
		T[z].son[0]=0;
		PushUp(z);
		return;
	}
	if(!z)
	{
		Splay(y, 0);
		T[y].son[1]=0;
		PushUp(y);
		return;
	}
	Splay(y, 0);
	Splay(z, y);
	T[z].son[0]=0;
	PushUp(z);
	PushUp(y);
}

int main()
{
    int n;
    int cas=0,x;
    while(scanf("%d",&n))
    {
        if(n==0) break;
        else if(n==1)
        {
            int k,p;
            scanf("%d%d",&k,&p);
            Insert(p,k);
        }
        else if(n==2)
        {
            x;
            x=GetPth(T[rt].size,0);
            if(x)
            {
                printf("%d\n",T[x].ans);
                Delete(T[x].key);
            }
            else
                printf("0\n");
        }
        else if(n==3)
        {
            x=GetPth(1,0);			
            if(x)
            {
                printf("%d\n",T[x].ans);
                Delete(T[x].key);
            }
            else
                printf("0\n");
        }
    }
    return 0;
}
