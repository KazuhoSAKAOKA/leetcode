﻿// leetcode_Q0684.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    struct union_find {

    std::vector<size_t> parents_;
    std::vector<size_t> sizes_;

    union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
        for (size_t i = 0; i < n; i++) {
            parents_[i] = i;
        }
    }

    size_t root(size_t x) {
        if (x == parents_[x]) { return x; }
        parents_[x] = root(parents_[x]);
        return parents_[x];
    }

    bool same(size_t x, size_t y) {
        return root(x) == root(y);
    }

    void unite(size_t x, size_t y) {
        const auto rootx = root(x);
        const auto rooty = root(y);
        if (rootx == rooty) { return; }
        if (sizes_[rootx] < sizes_[rooty]) {
            parents_[rootx] = rooty;
            sizes_[rooty] += sizes_[rootx];
        }
        else {
            parents_[rooty] = rootx;
            sizes_[rootx] += sizes_[rooty];
        }
    }

    size_t size(size_t x) {
        return sizes_[root(x)];
    }

    bool is_root(size_t x) {
        return root(x) == x;
    }
};
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        const auto N = size(edges);
        union_find uf(N);
        vector<vector<int>> redundants;

        for (int i = 0; i < N; i++) {
            const auto& edge = edges[i];
            const auto u = edge.front() - 1;
            const auto v = edge.back() - 1;
            if (!uf.same(u, v)) {
                uf.unite(u, v);
            }
            else {
                redundants.emplace_back(edge);
            }
        }

        return redundants.back();
    }
};

void test(vector<vector<int>>&& edges) {
    output(Solution().findRedundantConnection(edges));
}

int main()
{

    test(get_matrix_int("[[1,2],[1,3],[2,3]]"));
    test(get_matrix_int("[[1,2],[2,3],[3,4],[1,4],[1,5]]"));

    return 0;
}