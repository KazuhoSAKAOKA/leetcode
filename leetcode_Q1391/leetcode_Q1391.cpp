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

    bool hasValidPath(vector<vector<int>>& grid) {
        const auto n = size(grid);
        const auto m = size(grid.front());
        const auto N = n * m;
        union_find uf(N);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                const auto source = grid[i][j];
                if (i < n - 1) {
                    if (source == 2 || source == 3 || source == 4) {
                        const auto dest = grid[i + 1][j];
                        if (dest == 2 || dest == 5 || dest == 6) {
                            uf.unite(i * m + j, (i + 1) * m + j);
                        }
                    }
                }

                if (j < m - 1) {
                    if (source == 1 || source == 4 || source == 6) {
                        const auto dest = grid[i][j + 1];
                        if (dest == 1 || dest == 3 || dest == 5) {
                            uf.unite(i * m + j, i * m + j + 1);
                        }
                    }
                }
            }
        }

        return uf.same(0, N - 1);
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().hasValidPath(grid) << endl;
}

int main() {
    test(get_matrix_int("[[2,4,3],[6,5,2]]"));
    test(get_matrix_int("[[1,2,1],[1,2,1]]"));
    test(get_matrix_int("[[1,1,2]]"));
    return 0;
}