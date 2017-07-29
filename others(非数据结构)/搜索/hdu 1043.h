/*
	HDU 1043
	题意：
	给定一个序列，由1~8数字和字母x组成，表示的是一个3*3的矩形。每次操作x都能与相邻的数字交换，问如何操作才能使得序列为{1,2,3,4,5,6,7,8,x}。
	
	A* + 康拓展开
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
string Start,End;
int vis[400005];
string ans[400005];
int fx[4][2]={1,0,-1,0,0,1,0,-1};
int  fac[] = {1,1,2,6,24,120,720,5040,40320}; //i的阶乘为fac[i]
// 康托展开-> 表示数字a是 a的全排列中从小到大排，排第几
// n表示1~n个数  a数组表示数字。
int kangtuo(int n,string a)
{
    int i,j,t,sum;
    sum=0;
    for( i=0; i<n ;++i)
    {
        t=0;
        for(j=i+1;j<n;++j)
            if( a[i]>a[j] )
                ++t;
        sum+=t*fac[n-i-1];
    }
    return sum;
}
struct node
{
    string ans;
    string bj;
    int x;
    int y;
};
void bfs(string s)
{
    queue<node> q;
    node t1;
    t1.ans="";
    t1.bj=s;
    t1.x=2;
    t1.y=2;
    q.push(t1);
    
    int weizhi;
    weizhi=kangtuo(9,t1.bj);
    ans[weizhi]=t1.ans;
    vis[weizhi]=1;
    
    while(!q.empty())
    {
    	
        node t2,t3;
        t2=q.front();
        q.pop();
        t3=t2;
        int x,y;
        //cout<<t2.bj<<endl;
        for(int i=1;i<=4;i++)
        {
            t2=t3;
            string k,k1="";
            k=t2.bj;
            int len=k.length();
            x=t2.x;
            y=t2.y;
			x+=fx[i-1][0];
			y+=fx[i-1][1];

			if(x<0 || x>=3 || y<0 || y>=3)
				continue;
			swap(k[3*x+y],k[3*t2.x+t2.y]);
			t2.x=x;
			t2.y=y;
            if(i==1)
            {            	
                t2.bj=k;
                t2.ans+="u";
            }
            else if(i==2)
            {
                t2.bj=k;
                t2.ans+="d";
            }
            else if(i==3)
            {
                t2.bj=k;
                t2.ans+="l";
            }
            else if(i==4)
            {
            	t2.bj=k;
                t2.ans+="r";
			}
			weizhi=kangtuo(9,t2.bj);
			
			if(vis[weizhi]) continue;
            if(!vis[weizhi])
            {            	
                vis[weizhi]=1;
                q.push(t2);
                ans[weizhi]=t2.ans;
                //cout<<t2.bj<<" "<<t2.ans<<endl;
                int yt;
                //scanf("%d",&yt);
            }
        }
    }
}
int F[10];
void qiuF(string a)
{
    int len=a.length();
    for(int i=0;i<len;i++)
    {
        F[a[i]-'0']=i+1;
    }
}
void zhuanF(string &a)
{
    for(int i=0;i<9;i++)
    {
        a[i]=F[a[i]-'0']+'0';
    }
}
int main()
{
    string a="123456789";
    memset(vis,0,sizeof(vis));
    bfs(a);
    char z[2];
    while(scanf("%s",&z)!=EOF)
    {
    	Start="";
    	if(z[0]=='x')
    	{
    		Start+='9';
		}
		else Start+=z[0];
    	for(int i=1;i<=8;i++)
    	{
    		scanf("%s",&z);
    		if(z[0]=='x')
	    	{
	    		Start+='9';
			}
			else Start+=z[0];
		}
		
        int weizhi;
        weizhi=kangtuo(9,Start);
        if(!vis[weizhi])
        	printf("unsolvable\n");
        else 
        {
        	for(int i=ans[weizhi].length()-1;i>=0;i--)
        	{
        		printf("%c",ans[weizhi][i]);
			}
			printf("\n");
		}
    }
    return 0;
}