// leetcode_Q1905.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
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

    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        const auto N = size(grid1);
        const auto M = size(grid1.front());
        const auto SIZE = N * M;

        union_find uf2(SIZE);
        auto get_index = [M](size_t i, size_t j) {
            return i * M + j;
            };

        vector<size_t> indexes;

        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                if (grid2[i][j] == 1) {
                    const auto index = get_index(i, j);
                    indexes.emplace_back(index);
                    if (j < M - 1) {
                        if (grid2[i][j + 1] == 1) {
                            uf2.unite(index, get_index(i, j + 1));
                        }
                    }
                    if (i < N - 1) {
                        if (grid2[i + 1][j] == 1) {
                            uf2.unite(index, get_index(i + 1, j));
                        }
                    }
                }
            }
        }
        unordered_map<size_t, size_t> island_count_map;
        for (auto&& index:indexes) {
            const auto i = index / M;
            const auto j = index % M;
            if (grid1[i][j] == 1) {
                island_count_map[uf2.root(index)]++;
            }
        }

        size_t result = 0;
        for (auto&& [r, count] : island_count_map) {
            if (uf2.size(r) == count) {
                result++;
            }
        }
        return result;
    }
};

void test(vector<vector<int>>&& grid1, vector<vector<int>>&& grid2) {
    cout << Solution().countSubIslands(grid1, grid2) << endl;
}

int main()
{
    test(get_matrix_int("[[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]]"), get_matrix_int("[[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]"));
    test(get_matrix_int("[[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]]"), get_matrix_int("[[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]"));
    return 0;
}