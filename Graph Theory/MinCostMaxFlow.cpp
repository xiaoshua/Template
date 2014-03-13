#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>

using namespace std;

const int N = 105;
const int INF = 1e7;

struct Edge {
	int to, flow, cost, next;
	void init(int t, int f, int c, int n) {
		to = t;
		flow = f;
		cost = c;
		next = n;
	}
};

struct costFlow {
	int head[N], preV[N], preE[N], cost[N], src, des, eCnt;
	Edge e[N*N * 25];
	queue<int> q;
	bool inq[N];

	void init(int src, int des) {
		this->src = src;
		this->des = des;
		eCnt = 0;
		memset(head, -1, sizeof(head));
	}

	void addEdge(int a, int b, int c, int f) {
		e[eCnt].init(b, f, c, head[a]);
		head[a] = eCnt++;
		e[eCnt].init(a, 0, -c, head[b]);
		head[b] = eCnt++;
	}

	bool spfa() {
		fill(cost, cost + N, INF);
		cost[src] = 0;

		while(!q.empty()) q.pop();

		q.push(src);

		while(!q.empty()) {
			int f = q.front(), i, t;
			q.pop();
			inq[f] = false;

			for(i = head[f]; i != -1; i = e[i].next) {
				t = e[i].to;

				if(e[i].flow > 0 && cost[t] > cost[f] + e[i].cost) {
					cost[t] = cost[f] + e[i].cost;
					preV[t] = f;
					preE[t] = i;

					if(!inq[t]) {
						inq[t] = true;
						q.push(t);
					}
				}
			}
		}

		return cost[des] < INF;
	}

	int getMinCost() {
		if(src == des) {
			return INF;
		}

		int ret = 0;

		while(spfa()) {
			int maxF = INF, t = des, eId;

			while(t != src) {
				eId = preE[t];
				maxF = min(maxF, e[eId].flow);
				t = preV[t];
			}

			ret += cost[des] * maxF;

			for(t = des; t != src; t = preV[t]) {
				eId = preE[t];
				e[eId].flow -= maxF;
				e[eId ^ 1].flow += maxF;
			}
		}

		return ret;
	}

} cf;

