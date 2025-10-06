#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>
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

    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }


    int swimInWater(vector<vector<int>>& grid) {
        const auto n = size(grid);
        set<int> vals{ 0 };

        for (auto&& cols : grid) {
            vals.insert(cbegin(cols), cend(cols));
        }
        vector<int> values(cbegin(vals), cend(vals));
        
        auto check = [&](int value)->bool {
            const auto height = values[value];
            union_find uf(n * n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i < n - 1) {
                        if (grid[i][j] <= height && grid[i + 1][j] <= height) {
                            uf.unite(i * n + j, (i + 1) * n + j);
                        }
                    }
                    if (j < n - 1) {
                        if (grid[i][j] <= height && grid[i][j + 1] <= height) {
                            uf.unite(i * n + j, i * n + j + 1);
                        }
                    }
                }
            }
            return uf.same(0, n * n - 1);
            };

        if (check(0)) {
            return 0;
        }
        auto index = binary_search_meguru<int>(size(values) - 1, 0, check);
        return values[index];
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().swimInWater(grid) << endl;
}
int main() {
    test(get_matrix_int("[[0,2],[1,3]]"));
    test(get_matrix_int("[[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]"));
    return 0;
}