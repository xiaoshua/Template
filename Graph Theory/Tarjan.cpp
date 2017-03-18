//tarjan, zoj2588, 求割边
#include<stack>
#include<cstdio>
#include<cstring>

#define maxn 10009
#define maxm 100009
#define min(a, b) a<b? a : b
using namespace std;

struct edge {
    int u, v;

    edge(int a = 0, int b = 0) {
        u = a;
        v = b;
    }
} e[maxm];

struct node {
    int to, next;
} nod[maxm << 1];
int ed, head[maxn], n, m,
        dfn[maxn], tmpdfn, low[maxn],
        belong[maxn], cnt;
bool vis[maxn];

void add(int a, int b) {
    nod[ed].to = b;
    nod[ed].next = head[a];
    head[a] = ed++;
}

stack<int> st;
int out[maxm], len;

void init() {
    ed = tmpdfn = cnt = len = 0;
    fill(vis, vis + 1 + n, false);
    fill(head, head + 1 + n, -1);
    fill(belong, belong + 1 + n, -1);
}

void tarjan(int u, int p) {
    int v, i, f = 0;
    dfn[u] = low[u] = tmpdfn++;
    vis[u] = 1;
    st.push(u);
    for (i = head[u]; i != -1; i = nod[i].next) {
        v = nod[i].to;
        if (v == p && f == 0) {
            f = 1;
            continue;
        }
        if (!vis[v]) tarjan(v, u);
        low[u] = min(low[u], low[v]);
    }
    if (dfn[u] != low[u]) return;
    do {
        v = st.top();
        st.pop();
        belong[v] = cnt;
    } while (v != u);
    cnt++;
}

int main() {
    int re, ri, i, a, b;
    scanf("%d", &re);
    for (ri = 1; ri <= re; ri++) {
        scanf("%d%d", &n, &m);
        init();
        for (i = 1; i <= m; i++) {
            scanf("%d%d", &a, &b);
            add(a, b);
            add(b, a);
            e[i] = edge(a, b);
        }
        tarjan(1, -1);
        for (i = 1; i <= m; i++) {
            if (belong[e[i].u] != belong[e[i].v]) out[len++] = i;
        }
        printf("%d\n", len);
        for (i = 0; i < len; i++) printf("%d%c", out[i], i == len - 1 ? '\n' : ' ');
        if (ri != re) puts("");
    }
    return 0;
}

