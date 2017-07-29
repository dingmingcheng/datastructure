/*
	HDU 4825
	给你n个数，然后给你m组询问，每组询问给你一个数，输出n个数中与该数异或
	的最大的那个数，输出的是被异或的那个数，不是亦或后的结果。

	Sample Input

    2
    3 2
    3 4 5
    1
    5
    4 1
    4 6 5 6
    3

	Sample Output

    Case #1:
    4
    3
    Case #2:
    4
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define ll int
#define Word_Len 3000005
#define Sigma_size 2
int at;
struct Trie{
	ll ch[Word_Len][Sigma_size], sz;	 //Word_Len是字典树的节点数 若都是小写字母Sigma_size=26 sz为当前节点数
	ll Have_word[Word_Len];		 //这个节点下有几个单词
	ll val[Word_Len];				 // 这个节点附带的信息，初始化为0表示这个节点不存在单词，所以节点带的信息必须!=0
	ll pre[Word_Len];
	int Num[Word_Len];  
	char he[Word_Len];
	int len[Word_Len];
	ll Newnode()
	{
		memset(ch[sz], 0, sizeof(ch[sz])); 
		val[sz]=Have_word[sz]=0; 
		return sz++;
	}
	void init()							 //初始化字典树
	{ 
		sz = 0; 
		Newnode();
	}//初始化
	ll idx(char c){return c-'0';}	 //字符串编号

	int insert(char *s){	 //把v数字加给 s单词最后一个字母
		ll u = 0;
		for(ll i = 0; s[i]; i++){
			ll c = idx(s[i]);
			
			if(!ch[u][c])		     //节点不存在就新建后附加
			{
				ch[u][c] = Newnode();	
				he[sz-1] = s[i]-'0';
				val[sz-1] = val[u]+1;
				pre[sz-1] = u;
			}		
			u = ch[u][c];
			Have_word[u]++;	
		}
		len[u]=strlen(s);
		Num[u]=at;
		return u;
	}
	ll find_word(char *s){
		ll u = 0;
		for(ll i = 0; s[i]; i++){
			ll c = idx(s[i]);
			if(!ch[u][c])return 0;		//节点不存在
			u = ch[u][c];
		}
		return Have_word[u];
	}
	void Have_name(char *s, ll now){  
		ll len = val[now], cc = now;  
		s[len--] = 0;  
		while(cc)  
		{
			s[len--] = he[cc];  
			cc = pre[cc];  
		}  
	}
	int findans(char *s)
	{
		ll u = 0;
		for(ll i = 0; s[i]; i++){
			ll c = idx(s[i]);
			
			if(c==0)
			{
				if(ch[u][1]) u=ch[u][1];
				else u=ch[u][0];
			}
			else if(c==1)
			{
				if(ch[u][0]) u=ch[u][0];
				else u=ch[u][1];
			}
			//printf("%d %d\n",c,he[u]);
		}
		return Num[u];
	}
} ac;
char a[40];
void change(int t)
{
	int k=0,k1=0;
	int z=t;
	while(z)
	{
		k++;
		z/=2;
	}
	for(int i=1;i<=32-k;i++)
	{
		a[k1++]=0+'0';
	}
	k1=31;
	while(t)
	{
		a[k1--]=t%2+'0';
		t/=2;
	}
/*	for(int i=0;i<32;i++)
	{
		printf("%c",a[i]);
	}
	printf("\n")*/
}
int main()
{
	int t,cas=0;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		ac.init();
		for(int i=0;i<n;i++)
		{
			scanf("%d",&at);
			change(at);
			ac.insert(a);
		}
		printf("Case #%d:\n",++cas);
		for(int j=0;j<m;j++)
		{
			scanf("%d",&at);
			change(at);
			int ans=ac.findans(a);
			printf("%d\n",ans);
		}
		
		
	}
	return 0;
}
