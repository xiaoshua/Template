ass Disjoint {
private:
    vector<int> parent;
public:
    void init(int n) {
        parent.resize(n);
        fill(parent.begin(), parent.end(), -1);
    }

    int find(int x) {
        return parent[x] < 0 ? x : parent[x] = find(parent[x]);
    }

    int getSubSetSize(int x) {
        int root = find(x);
        return -parent[root];
    }

    void merge(int a, int b) {
        int x = find(a), y = find(b);
        if (x != y) {
            parent[x] += parent[y];
            parent[y] = x;
        }
    }
};
