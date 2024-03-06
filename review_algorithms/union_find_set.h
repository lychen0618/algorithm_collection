#pragma once
#include <vector>

class UnionSet {
public:
    UnionSet(const int& n) {
        fa = std::vector<int>(n);
        rank = std::vector<int>(n);
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        if (fa[x] == x) {
            return x;
        }
        fa[x] = find(fa[x]);
        return fa[x];
    }

    void merge(int i, int j) {
        int x = find(i), y = find(j);
        if (x == y) {
            return;
        }
        if (rank[x] <= rank[y]) {
            fa[x] = y;
        } else {
            fa[y] = x;
        }
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }

private:
    std::vector<int> fa;
    std::vector<int> rank;
};
