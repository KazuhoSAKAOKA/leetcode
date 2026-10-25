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
#include <bitset>
#include <optional>
#include <sstream>
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

    int closedIsland(vector<vector<int>>& grid) {
        const long long h = size(grid);
        const long long w = size(grid[0]);
        const auto n = h * w;
        union_find uf(n);
        vector<long long> opends;


        for (long long i = 0; i < h; i++) {
            for (long long j = 0; j < w; j++) {
                if (grid[i][j] == 0) {
                    if (i < h - 1) {
                        if (grid[i + 1][j] == 0) {
                            uf.unite(i * w + j, (i + 1) * w + j);
                        }
                    }
                    if (j < w - 1) {
                        if (grid[i][j + 1] == 0) {
                            uf.unite(i * w + j, i * w + j + 1);
                        }
                    }

                    if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
                        opends.push_back(i * w + j);
                    }
                }
            }
        }

        vector<bool> opened_roots(n);
        for (auto&& index : opends) {
            opened_roots[uf.root(index)] = true;
        }
        long long count = 0;

        for (long long i = 0; i < h; i++) {
            for (long long j = 0; j < w; j++) {
                const auto index = i * w + j;
                if (grid[i][j] == 0 && uf.is_root(index) && !opened_roots[index]) {
                    count++;
                }
            }
        }


        return count;
    }
};
static void test(vector<vector<int>>&& grid) {
	cout << Solution().closedIsland(grid) << endl;
}

static void run() {
	test(get_matrix_int("[[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]"));
	test(get_matrix_int("[[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]"));
	test(get_matrix_int("[[1,1,1,1,1,1,1],[1,0,0,0,0,0,1],[1,0,1,1,1,0,1],[1,0,1,0,1,0,1],[1,0,1,1,1,0,1],[1,0,0,0,0,0,1],[1,1,1,1,1,1,1]]"));
}


int main() {
	run();
	return 0;
}
