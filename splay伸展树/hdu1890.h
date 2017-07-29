/**
*
*	hdu 1890
*	
*	将一列数字排序  排序规则是  每次找到最小值的位置loc  将1~loc所有数字颠倒  然后删掉第一位  直到排好序  排序要求是稳定的
*	寻找区间最小值位置  翻转区间  的操作  因此可以想到用splay
*	input case:
*	6
*	3 4 5 1 6 2
*	4
*	3 3 2 1
*	output case:
*	4 6 4 5 6 6
*	4 2 4 4
*
**/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define KT ch[ ch[root][1] ][0]
#define L ch[x][0]
#define R ch[x][1]
const int maxn = 100015;
int num[maxn], n, m;
int k1, k2;
typedef long long ll;
struct node{
    int a,idx;
};
node a[maxn];
int cmp(node a,node b)
{
    if(a.a==b.a) return a.idx<b.idx;
    return a.a<b.a;
}
struct splayTree {
    int ch[maxn][2], sz[maxn], pre[maxn];
    int root, tot, all; // all：节点总数， tot：最大标号

    int add[maxn], val[maxn];
    bool flip[maxn]; //翻转标记
    int sta[maxn], top;
    void rotate(int &x, int f) {
           int y = pre[x], z = pre[y];
           down(y); down(x);
           ch[y][!f] = ch[x][f];
           pre[ch[x][f]] = y;
           pre[x] = pre[y];
           if(z) ch[z][ch[z][1] == y] = x;
           ch[x][f] = y;
           pre[y] = x;
           up(y);
       }
       void splay(int &x, int g) {
           down(x);
           while(pre[x] != g) {
               int y = pre[x], z = pre[y];
               if(z == g) {
                   down(y); down(x);rotate(x, ch[y][0] == x);
               }
               else {
                    down(z); down(y); down(x);
                   int f = (ch[z][0] == y);
                   ch[y][!f] == x ? rotate(y, f) : rotate(x, !f);
                   rotate(x, f);
               }
           }
           if(!g) root = x;
           up(x);
       }
       void rto(int k, int g) {
           int x = root;
           while(1) {
               down(x);

               if(sz[L] == k) break;
               if(sz[L] > k) x = L;
               else {
                   k -= sz[L] + 1;
                   x = R;
               }
           }
           splay(x, g);
       }
    void down(int x){
        if(add[x]) {
            val[L] += add[x];
            val[R] += add[x];
            add[L] += add[x];
            add[R] += add[x];
            add[x] = 0;
        }
        if(flip[x]) {
            flip[L] ^= 1;
            flip[R] ^= 1;
            swap(L, R);
            flip[x] = 0;
        }
    }
    void up(int x) {
        sz[x] = sz[L] + sz[R] +1;
    }

    void build(int &x, int l, int r, int fa) {
        if(l > r) return;
        int m = (l+r) >> 1;
        newNode(x, m, fa);
        build(L, l, m-1, x);
        build(R, m+1, r, x);

        up(x);
    }
    void newNode(int &x, int v, int fa) {
//        if(top) x = sta[top--];	//内存回收
//        else x = ++tot;
        x=v;
        all++;
        pre[x] = fa;
        sz[x] = 1;
        L = R = 0;
        val[x] = v;
        add[x] = 0;
        flip[x] = 0;
    }
    void init(int n) {
        all = tot = top = 0;
//        newNode(root, 0, 0);
//        newNode(ch[root][1], 0, root);
        for(int i = 1; i <= n; i++)
        {scanf("%d",&a[i].a);a[i].idx=i;}
        root=0;
        sort(a+1,a+n+1,cmp);
        build(root, 1, n, 0);
        up(root);
    }
    ll erase(int k) { //删除第k个数
        rto(k, 0);
        rto(k-1, root);
        sta[++top] = root;
        all--;
        ll ret = val[root];
        int ls = ch[root][0], rs = ch[root][1];
        root = ls;
        pre[ls] = 0;
        ch[ls][1] = rs;
        if(rs)pre[rs] = ls;
        up(root);
        return ret;
    }
    void insert(int k, int v) { //在第k个数后面插入一个数v
        rto(k, 0);
        int x;
        int rs = ch[root][1];
        newNode(x, v, root);
        ch[root][1] = x;
        ch[x][1] = rs;
        if(rs) pre[ch[x][1]] = x;
        up(ch[root][1]);
        up(root);
    }
    void move1() {
        int v = erase(all-2);
        insert(0, v);
    }
    void move2() {
        int v = erase(1);
        insert(all-2, v);

    }
    void update(int l, int r, int v) {
        rto(l-1, 0);
        rto(r+1, root);
        val[KT] += v;
        add[KT] += v;
        up(ch[root][1]);
        up(root);
    }
    void reverse(int l, int r) {
        rto(l-1, 0);
        rto(r+1, root);
        flip[KT] ^= 1;
        up(ch[root][1]);
        up(root);
    }
    int query() {
        rto(1, 0);
        return val[root];
    }
    int Get_Max(int r)
    {
        //Push_Down(r);
        down(r);
        while(ch[r][1]){
            r=ch[r][1];
            down(r);
        }
        return r;
    }
    void Remove(int rot){ // erase the root
        if(ch[rot][0]==0){
            rot=ch[rot][1];
            pre[rot]=0;
        }
        else{
            int m=Get_Max(ch[rot][0]);
                splay(m,rot);
            ch[m][1]=ch[rot][1];
            pre[ch[rot][1]]=m;
            rot=m;
            root=m;
            pre[rot]=0;
            up(rot);
        }
    }
}spt;
int main() {
    int ca = 1;
        int n;
        while(scanf("%d",&n))
        {

            if(n==0) break;
            spt.init(n);
            for(int i=1;i<n;i++)
            {
                spt.splay(a[i].idx,0);
                spt.root=a[i].idx;
                spt.flip[spt.ch[spt.root][0]]^=1;
                printf("%d ",i+spt.sz[spt.ch[spt.root][0]]);
                spt.Remove(spt.root);
            }
            printf("%d\n",n);
        }
    return 0;
}
/*
5 100000 2 4
1 2 3 4 5
*/
