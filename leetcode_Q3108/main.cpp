#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
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

    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        union_find uf(n);
        for (auto&& edge : edges) {
            uf.unite(edge[0], edge[1]);
        }
        map<int, int> cost_map;
        for (auto&& edge : edges) {
            const auto root = uf.root(edge[0]);
            auto it = cost_map.find(root);
            if (it == cend(cost_map)) {
                cost_map.insert({root, edge[2]});
            }
            else {
                it->second &= edge[2];
            }
        }

        vector<int> ans;
        ans.reserve(size(query));
        for (auto&& q : query) {
            if (uf.same(q.front(), q.back())) {
                ans.emplace_back(cost_map[uf.root(q.front())]);
            }
            else {
                ans.emplace_back(-1);
            }
        }
        return ans;


    }
};
int main() {
	return 0;
}