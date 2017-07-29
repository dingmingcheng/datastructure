/*
	HDU 2102
	
	5 5 14
	S*#*.
	.#...
	.....
	****.
	...#.

	..*.P
	#.*..
	***..
	...*.
	*.#..
	yes
	Input
    输入的第一行C表示共有C个测试数据，每个测试数据的前一行有三个整数N，M，T。 N，M迷宫的大小N*M（1 <= N,M <=10)。T如上所意。接下去的前N*M表示迷宫的第一层的布置情况，后N*M表示迷宫第二层的布置情况。
	Output
		如果骑士们能够在T时刻能找到公主就输出“YES”，否则输出“NO”。
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
#define N 200005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
char mat[2][20][20];
int vis[2][20][20];
struct node
{
    int x,y;
    int cen;
    int sum;
};
node start,End;
int dir[4][2]={1,0,-1,0,0,1,0,-1};
int t,n,m;
int bfs()
{
    node t1,t2;
    queue<node> q;
    t1=start;
    t1.cen=0;
    t1.x=0;
    t1.y=0;
    t1.sum=0;
    vis[t1.cen][t1.x][t1.y]=1;
    q.push(t1);
    while(!q.empty())
    {
        t2=q.front();
        q.pop();
        //printf("%d %d %d\n",t2.cen,t2.x,t2.y);
        int x,y,cen;
        if(t2.cen==End.cen && t2.x==End.x && t2.y==End.y)
            return t2.sum;
        for(int i=0;i<4;i++)
        {
            x=t2.x+dir[i][0];
            y=t2.y+dir[i][1];
            cen=t2.cen;
            if(x<0 || x>=n || y<0 || y>=m)
                continue;
            if(mat[cen][x][y]=='#')
            {vis[cen][x][y]=1;cen^=1;}
            if(mat[cen][x][y]=='*' || mat[cen][x][y]=='#')
                continue;
            if(vis[cen][x][y]==1)
                continue;
            int sum;
            sum=t2.sum+1;
            t1.cen=cen;
            t1.sum=sum;
            t1.x=x;
            t1.y=y;
            //printf("%d %d %d *\n",cen,x,y);
            vis[cen][x][y]=1;
            q.push(t1);
        }
    }
    return 999999;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&t);
        for(int i=0;i<n;i++)
        {
            scanf("%s",mat[0][i]);
            for(int j=0;j<m;j++)
            {
                if(mat[0][i][j]=='S')
                {
                    start.cen=0;start.x=i;start.y=j;
                }
                else if(mat[0][i][j]=='P')
                {
                    End.cen=0;End.x=i;End.y=j;
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            scanf("%s",mat[1][i]);
            for(int j=0;j<m;j++)
            {
                if(mat[1][i][j]=='S')
                {
                    start.cen=1;start.x=i;start.y=j;
                }
                else if(mat[1][i][j]=='P')
                {
                    End.cen=1;End.x=i;End.y=j;
                }
            }
        }
        memset(vis,0,sizeof(vis));
        int z=bfs();
        if(z<=t) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
/*
5 5 13
S*#*.
.#...
.....
****.
...#.

..*.P
#.*..
***..
...*.
*.##.
*/
