// leetcode_Q2852.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
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

    long long sumRemoteness(vector<vector<int>>& grid) {
        const auto n = size(grid);
        const auto N = n * n;
        union_find uf(N);

        //const vector<pair<int, int>> directions{ {1,0},{-1,0}, {0,1}, {0,-1}, };

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (grid[y][x] < 0) { continue; }
                const auto index = y * n + x;
                if (y < n - 1 && grid[y + 1][x] >= 0) {
                    uf.unite(index, (y + 1) * n + x);
                }
                if (x < n - 1 && grid[y][x + 1] >= 0) {
                    uf.unite(index, y * n + x + 1);
                }
            }
        }
        long long total_sum = 0;
        map<int, long long> group_map;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (grid[y][x] < 0) { continue; }
                const auto index = y * n + x;
                const auto root = uf.root(index);
                group_map[root] += static_cast<long long>(grid[y][x]);
                total_sum += static_cast<long long>(grid[y][x]);
            }
        }

        long long ans = 0;
        for (auto&& [root, s] : group_map) {
            const auto cur_group_score_each = total_sum - s;
            const auto cur_group_score = cur_group_score_each * uf.size(root);
            ans += cur_group_score;
        }

        return ans;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().sumRemoteness(grid) << endl;
}

int main()
{
    test(get_matrix_int("[[-1,1,-1],[5,-1,4],[-1,3,-1]]"));
    test(get_matrix_int("[[-1,3,4],[-1,-1,-1],[3,-1,-1]]"));
    test(get_matrix_int("[[1]]"));
    return 0;
}