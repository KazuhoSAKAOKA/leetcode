#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
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

    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        const auto n = size(source);
        union_find uf(n);
        for (auto&& uv : allowedSwaps) {
            uf.unite(uv[0], uv[1]);
        }
        unordered_map<size_t, unordered_multiset<int>> root_map;
        for (size_t i = 0; i < n; i++) {
            root_map[uf.root(i)].insert(source[i]);
        }

        int count = 0;

        for (size_t i = 0; i < n; i++) {
            auto& inner_set = root_map[uf.root(i)];
            auto it = inner_set.find(target[i]);
            if (it != cend(inner_set)) {
                inner_set.erase(it);
            }
            else {
                count++;
            }
        }
        return count;
    }
};

static void test(vector<int>&& source, vector<int>&& target, vector<vector<int>>&& allowedSwaps) {
    cout << Solution().minimumHammingDistance(source, target, allowedSwaps) << endl;
}

int main() {
    test(get_list_int("[1,2,3,4]"), get_list_int("[2,1,4,5]"), get_matrix_int("[[0,1],[2,3]]"));
    test(get_list_int("[1,2,3,4]"), get_list_int("[1,3,2,4]"), get_matrix_int("[]"));
    test(get_list_int("[5,1,2,4,3]"), get_list_int("[1,5,4,2,3]"), get_matrix_int("[[0,4],[4,2],[1,3],[1,4]]"));
    return 0;
}
