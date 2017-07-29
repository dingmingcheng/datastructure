/**
*
*	POJ 1754
*
*	很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。
*	这让很多学生很反感。
*	不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。
*
*
*/
#include <iostream>
using namespace std;

#define MAX_N 200005

int big;
typedef struct node
{
    int left;
    int right;
    int data;
    int maxx;
}node;

node stu[MAX_N*4];
//int num[MAX_N+1];

int Max(int a,int b)
{
    return a>b?a:b;
}

void CreateTree(int ii,int a,int b)
{
    stu[ii].left = a;
    stu[ii].right = b;
    stu[ii].maxx = 0;
    stu[ii].data = 0;
    if(a == b)
    {
        return;
    }
    else
    {
        int mid = (a+b)>>1;
        CreateTree(ii*2,a,mid);
        CreateTree(ii*2+1,mid+1,b);
    }
}

void updata(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == a)
    {
        stu[ii].data = b;
        stu[ii].maxx = b;
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
        if(b > stu[ii].maxx)
            stu[ii].maxx = b;
    }
}

void find1(int ii,int a,int b)
{
    if(stu[ii].left == a && stu[ii].right == b)
    {
        //printf("%d/n",stu[ii].maxx);
        if(stu[ii].maxx > big)
            big = stu[ii].maxx;
    }
    else
    {
        int mid = (stu[ii].left + stu[ii].right)>>1;
        if(b <= mid)
        {
            find1(ii*2,a,b);
        }
        else if(a > mid)
        {
            find1(ii*2+1,a,b);
        }
        else
        {
            find1(ii*2,a,mid);
            find1(ii*2+1,mid+1,b);
        }
    }
}

int main()
{
    int n,m,num;
    int i;

    while(scanf("%d%d",&n,&m)!=EOF)
    {
        CreateTree(1,1,n);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&num);
            updata(1,i,num);
        }
        char c[5];
        int x1,x2;
        while(m--)
        {
            scanf("%s",&c);
            scanf("%d%d",&x1,&x2);
            if(c[0] == 'Q')
            {
                big = 0x80000000;
                find1(1,x1,x2);
                printf("%d\n",big);
            }
            else if(c[0]=='U')
            {
                updata(1,x1,x2);
            }
        }
    }
    return 0;
}
