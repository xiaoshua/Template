#include<map>
#include<set>
#include<queue>
#include<stack>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
const int N = 35 + 9;
const int M = 20;
struct ST {
    VI bin, log;
    VVI rmq;
    int n;
    ST() {
        int i;
        VI(M).swap(bin);
        VI(N).swap(log);
        VVI(N, VI(M)).swap(rmq);
        log[0] = -1;

        for(i = 1; i < N; ++i) {
            log[i] = log[i - 1] + !(i & (i - 1));
        }

        for(i = 0; i < M; ++i) {
            bin[i] = 1 << i;
        }
    }

    void init(int * a, int _n) {
        n = _n;
        int i, j;

        for(i = 0; i < n; ++i) {
            rmq[i][0] = a[i];
        }

        for(j = 1; bin[j] <= n; ++j) { // <= not <
            for(i = 0; i + bin[j] <= n; ++i) { // <= not <
                rmq[i][j] = min(rmq[i][j - 1], rmq[i + bin[j-1]][j - 1]);
            }
        }
    }

    int query(int s, int e) {
        if(s > e) {
            swap(s, e);
        }

        int len =  e - s + 1;
        int lg = log[len];
        int mi =  min(rmq[s][lg], rmq[e - bin[lg] + 1][lg]);
        return mi;
    }
} st;
