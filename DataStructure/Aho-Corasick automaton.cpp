#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<functional>
using namespace std;
typedef long long LL;
const int alpNum = 2;
const int trieNum = 1 << 20;
int ed, root, fail[trieNum];
int alp2num[1 << 8];
struct node {
	int child[alpNum], tag;
	void init() {
		child[0] = child[1] = -1;
		tag = 0;
	}
} trie[trieNum];
void init() {
	fail[0] = 0;
	root = 0;
	trie[0].init();
	ed = 0;
}
int insert(char *s) {
	int i, now = root, index;

	for(i = 0; s[i]; i++) {
		index = alp2num[s[i]];

		if(trie[now].child[index] == -1) {
			trie[++ed].init();
			trie[now].child[index] = ed;
		}

		now = trie[now].child[index];
	}

	return now;
}

void build() {
	int i, p, now;
	queue<int> q;
	for(i = 0; i < alpNum; i++) {
		if(trie[0].child[i] != -1) {
			fail[trie[0].child[i]] = 0;
			q.push(trie[0].child[i]);
		} else trie[0].child[i] = 0;
	}

	while(!q.empty()) {
		p = q.front(); q.pop();
		trie[p].tag |= trie[fail[p]].tag;

		for(i = 0; i < alpNum; i++) {
			now = trie[p].child[i];

			if(now != -1) {
				fail[now] = trie[fail[p]].child[i];
				q.push(now);
			} else trie[p].child[i] = trie[fail[p]].child[i];
		}
	}
}
