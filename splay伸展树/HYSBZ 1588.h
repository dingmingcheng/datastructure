/*
	HYSBZ 1588 (最小波动值)
	 第一行为正整数 ，表示该公司从成立一直到现在的天数，接下来的n行每行有一个整数(有可能有负数) ，表示第i天公司的营业额。
	天数n<=32767,
	每天的营业额ai <= 1,000,000。
	最后结果T<=2^31 
	case:
	6
	5
	1
	2
	5
	4
	6
	output:12
	hint:5+|1-5|+|2-1|+|5-5|+|4-5|+|6-5|=5+4+1+0+1+1=12
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
#define KT ch[ ch[root][1] ][0]
#define L ch[x][0]
#define R ch[x][1]
#define INF 0x7fffffff
const int maxn = 300012;
int num[maxn], n, m;
int k1, k2;
typedef long long ll;
struct node {
	int a, idx;
};
node a[maxn];
int cmp(node a, node b)
{
	if (a.a == b.a) return a.idx<b.idx;
	return a.a<b.a;
}
int zx = 0;
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
		if (z) ch[z][ch[z][1] == y] = x;
		ch[x][f] = y;
		pre[y] = x;
		up(y);
	}
	void splay(int &x, int g) {
		down(x);
		while (pre[x] != g) {
			int y = pre[x], z = pre[y];
			if (z == g) {
				down(y); down(x);rotate(x, ch[y][0] == x);
			}
			else {
				down(z); down(y); down(x);
				int f = (ch[z][0] == y);
				ch[y][!f] == x ? rotate(y, f) : rotate(x, !f);
				rotate(x, f);
			}
		}
		down(x);
		if (!g) root = x;
		up(x);
	}
	void rto(int k, int g) {
		int x = root;
		while (1) {
			down(x);
			if (sz[L] == k) break;
			if (sz[L] > k) x = L;
			else {
				k -= sz[L] + 1;
				x = R;
			}
		}
		splay(x, g);
	}
	void down(int x) {
		if (add[x]) {
			val[L] += add[x];
			val[R] += add[x];
			add[L] += add[x];
			add[R] += add[x];
			add[x] = 0;
		}
		if (flip[x]) {
			flip[L] ^= 1;
			flip[R] ^= 1;
			swap(L, R);
			flip[x] = 0;
		}
	}
	void up(int x) {
		sz[x] = sz[L] + sz[R] + 1;
	}

	void build(int &x, int l, int r, int fa) {
		if (l > r) return;
		int m = (l + r) >> 1;
		newNode(x, m, fa);
		build(L, l, m - 1, x);
		build(R, m + 1, r, x);
		up(x);
	}
	void newNode(int &x, int v, int fa) {
		if (top) x = sta[top--];	//内存回收
		else x = ++tot;
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
		/*newNode(root, 0, 0);
		newNode(ch[root][1], 0, root);
		sz[root] = 2;*/
		//        for(int i = 1; i <= n; i++)
		//        {scanf("%d",&a[i].a);}
		/*build(KT, 1, n, ch[root][1]);
		up(ch[root][1]);
		up(root);*/
	}
	ll erase(int k) { //删除第k个数
		rto(k, 0);
		rto(k - 1, root);
		sta[++top] = root;
		all--;
		ll ret = val[root];
		int ls = ch[root][0], rs = ch[root][1];
		root = ls;
		pre[ls] = 0;
		ch[ls][1] = rs;
		if (rs)pre[rs] = ls;
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
		if (rs) pre[ch[x][1]] = x;
		up(ch[root][1]);
		up(root);
	}
	int insert1(int k)
	{
		int ans = INF;
		int t = root,y;
		while (t)
		{
			ans = min(ans,(int)fabs(k-val[t]));
			//printf("%d %d %d\n",k,val[t],ans);
			y = t;
			if (k == val[t])
			{
				return 0;
			}
			t = ch[y][k>val[t]];
		}
		if (!t)
		{
			newNode(ch[y][k>val[y]],k,y);
			t = ch[y][k > val[y]];
		}
		splay(t,0);
		return ans;
	}
	int Get_kth(int r, int k)
	{
		down(r);
		int t = sz[ch[r][0]] + 1;
		if (t == k)return r;
		if (t > k)return Get_kth(ch[r][0], k);
		else return Get_kth(ch[r][1], k - t);
	}
	int Get_min(int r) {
		down(r);
		while (ch[r][0]) {
			r = ch[r][0];
			down(r);
		}
		return r;
	}
	void CUT(int a, int b, int c)//a,b区间除去，移至第c个后
	{
		int x = Get_kth(root, a);
		int y = Get_kth(root, b + 2);
		splay(x, 0);
		splay(y, root);
		int t = KT;
		KT = 0;
		up(ch[root][1]);
		up(root);
		int z = Get_kth(root, c + 1);
		splay(z, 0);
		int p = Get_min(ch[root][1]);
		splay(p, root);
		KT = t;
		pre[KT] = ch[root][1];
		up(ch[root][1]);
		up(root);
	}
	void move1() {
		int v = erase(all - 2);
		insert(0, v);
	}
	void move2() {
		int v = erase(1);
		insert(all - 2, v);
	}
	void update(int l, int r, int v) {
		rto(l - 1, 0);
		rto(r + 1, root);
		val[KT] += v;
		add[KT] += v;
		up(ch[root][1]);
		up(root);
	}
	void reverse(int l, int r) {
		rto(l - 1, 0);
		rto(r + 1, root);
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
		while (ch[r][1]) {
			r = ch[r][1];
			down(r);
		}
		return r;
	}
	void Remove(int rot) { // erase the root
		if (ch[rot][0] == 0) {
			rot = ch[rot][1];
			pre[rot] = 0;
		}
		else {
			int m = Get_Max(ch[rot][0]);
			splay(m, rot);
			ch[m][1] = ch[rot][1];
			pre[ch[rot][1]] = m;
			rot = m;
			root = m;
			pre[rot] = 0;
			up(rot);
		}
	}
	void print(int x) {
		down(L);
		if (L)print(L);
		//printf("node %d: ls=%d rs=%d lsz = %d rsz = %d val = %d\n", x, L, R, sz[L], sz[R], val[x]);
		if (x != 1 && x != 2)
		{
			zx++;
			if (zx == n)
				printf("%d\n", val[x]);
			else printf("%d ", val[x]);
		}
		down(R);
		if (R)print(R);
	}
	void debug() {
		//printf("root = %d\n", root);
		zx = 0;
		print(root);
	}
}spt;
int main() {
	int ca = 1;
	while (~scanf("%d", &n))
	{
		int sum=0;
		spt.init(n);
		for (int i = 1;i <= n;i++)
		{
			int z;
			scanf("%d",&z);
			if (i == 1)
			{
				spt.newNode(spt.root,z,0);
				sum = z;
				continue;
			}
			sum += spt.insert1(z);
			//printf("%d\n",spt.insert1(z));
		}
		printf("%d\n",sum);
	}
	return 0;
}