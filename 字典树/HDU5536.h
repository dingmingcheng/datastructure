/*
	HDU5536
	max{(i,j,k)(si+sj)⊕sk}
	先把所有的数保存下来，然后删去要用的i和j，再在里面找出能和a[i]+a[j]异或出的最大值。相当于值需要枚举i和j即可。
	Sample Input

    2
    3
    1 2 3
    3
    100 200 300

	Sample Output

    6
    400

*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define ll int
#define Word_Len 100005
#define Sigma_size 2
int at,flag;
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
				if(Have_word[ch[u][1]]) u=ch[u][1];
				else if(Have_word[ch[u][0]]) u=ch[u][0];
			}
			else if(c==1)
			{
				if(Have_word[ch[u][0]]) u=ch[u][0];
				else if(Have_word[ch[u][1]]) u=ch[u][1];
			}
		}
		return Num[u];
	}
	void Delete(char *s)
	{
		ll u=0,last,c;
		for(ll i = 0; s[i]; i++){
			c = idx(s[i]);
			last=u;		
			u=ch[u][c];
			Have_word[u]--;	
		}
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
}
int ft[1005];
int main()
{
	int t,cas=0;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		ac.init();
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",&ft[i]);
			at=ft[i];
			change(ft[i]);
			flag=i;
			ac.insert(a);
		}
		
		int index;int Max=0;
		for(int i=0;i<n;i++)
		{at=ft[i];
				change(ft[i]);
				flag=i;
				ac.Delete(a);
			for(int j=i+1;j<n;j++)
			{
				index=ft[i]+ft[j];												
				
				at=ft[j];
				change(ft[j]);
				flag=j;
				ac.Delete(a);
								
				change(index);
				int ans=ac.findans(a);			
				ans=ans^index;
				Max=max(Max,ans);				
				
				at=ft[j];
				change(ft[j]);
				flag=j;
				ac.insert(a);
			}
			at=ft[i];
				change(ft[i]);
				flag=i;
				ac.insert(a);
		}
		printf("%d\n",Max);
	}
	return 0;
}
