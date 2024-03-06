#pragma once
#include <queue>
#include <vector>

std::vector<int> topologySort(int n, std::vector<std::vector<int>>& arr) {
    if (n < 2) {
        return std::vector<int>(n);
    }
    std::vector<int> sorted;
    std::vector<int> counts(n, 0);
    std::vector<std::vector<int>> point_to_arr(n);
    for (auto& p : arr) {
        point_to_arr[p[1]].push_back(p[0]);
        counts[p[0]] += 1;
    }
    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (counts[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int tp = q.front();
        sorted.push_back(tp);
        q.pop();
        for (auto& p : point_to_arr[tp]) {
            counts[p]--;
            if (counts[p] == 0) {
                q.push(p);
            }
        }
    }
    return sorted;
}