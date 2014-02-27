//http://codeforces.com/contest/396/submission/6133566
#include<map>
#include<set>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
const int N = 3e5+9;
const int mod = 1e9+7;
typedef long long LL;
void add(LL &a, LL b) {
    a += b;
    if(a>=mod) {
        a -= mod;
    }
}
struct SegNode {
    int left, right;
    LL add, mul;
    void init(int a, int b) {
        add=mul=0;
        left = a;
        right = b;
    }
} seg[N<<2];

int L(int n) {
    return n<<1;
}

int R(int n) {
    return n<<1|1;
}

void down(int N) {
    add(seg[L(N)].add, seg[N].add);
    add(seg[R(N)].add, seg[N].add);
    add(seg[L(N)].mul, seg[N].mul);
    add(seg[R(N)].mul, seg[N].mul);
    seg[N].add=seg[N].mul=0;
}

void build(int N, int a, int b) {
    seg[N].init(a, b);
    if(a == b) {
        return ;
    }
    int mid = (a+b)>>1;
    build(L(N), a, mid);
    build(R(N), mid+1, b);
}

void update(int N, int a, int b, LL ad, LL mul) {
    if(seg[N].left == a && seg[N].right == b) {
        add(seg[N].add, ad);
        add(seg[N].mul, mul);
        return ;
    }
    down(N);
    if(seg[L(N)].right >= b) {
        update(L(N), a, b, ad, mul);
    } else if(seg[R(N)].left<=a) {
        update(R(N), a, b, ad, mul);
    } else {
        update(L(N), a, seg[L(N)].right, ad, mul);
        update(R(N), seg[R(N)].left, b, ad, mul);
    }
}

pair<LL,LL> query(int N, int a) {
    if(seg[N].left == a && seg[N].right == a) {
        return make_pair(seg[N].add, seg[N].mul);
    }
    down(N);
    int mid = (seg[N].left + seg[N].right)>>1;
    if(mid >= a) {
        return query(L(N), a);
    } else {
        return query(R(N), a);
    }
}

vector<int> e[N];
int dep[N], id[N], en[N];
int timestamp;
void dfs(int u, int d) {
    dep[u]=d;
    id[u]=++timestamp;
    for(vector<int>::iterator vit=e[u].begin(); vit!=e[u].end(); ++vit) {
        dfs(*vit, d+1);
    }
    en[u]=timestamp;
}

int main() {
    int i, j, k, a, b, c, d, n, m, op;
    while(~scanf("%d", &n)) {
        for(i=1; i<=n; ++i) {
            e[i].clear();
        }
        for(i=2; i<=n; ++i) {
            scanf("%d", &a);
            e[a].push_back(i);
        }

        dfs(1, 0);

        build(1, 1, n);
        scanf("%d", &m);
        while(m--) {
            scanf("%d%d", &op, &a);
            d = dep[a];
            if(op==1) {
                scanf("%d%d", &b, &c);
                update(1, id[a], en[a], (b+1LL*dep[a]*c)%mod, c);
            } else {
                pair<LL,LL> p = query(1, id[a]);
                LL ans=(p.first + (mod-dep[a])*p.second)%mod;
                if(ans<0) {
                    ans += mod;
                }
                printf("%d\n", int(ans));

            }
        }

    }
    return 0;
}
