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
const int N = 1e7 + 9;
typedef long long LL;
int p[N / 5], pn;
bool notP[N];
int mu[N];
bool getMu(int n = N) {
	int i, j;
	mu[1]=1;
    for(i = 2; i < n; ++i) {
		if(!notP[i]) {
			p[pn++] = i;
			mu[i]=-1;
		}

		for(j = 0; j < pn && i * p[j] < n; ++j) {
			notP[i * p[j]] = true;

			if(i % p[j] == 0) {
				break;
			} else {
				mu[i*p[j]]=-mu[i];
			}
		}
	}
}
