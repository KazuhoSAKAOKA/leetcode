// leetcode_Q0947.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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



    int removeStones(vector<vector<int>>& stones) {
        unordered_map<size_t, int> cols;
        unordered_map<size_t, int> rows;
        union_find uf(size(stones));

        for (size_t index = 0; index < size(stones); index++) {
            const auto& stone = stones[index];
            const auto x = stone[0];
            const auto y = stone[1];
            const auto it_col = cols.find(x);
            if (it_col != cend(cols)) {
                uf.unite(index, it_col->second);
            }
            const auto it_row = rows.find(y);
            if (it_row != cend(rows)) {
                uf.unite(index, it_row->second);
            }
            cols[x] = index;
            rows[y] = index;
        }

        int result = 0;
        for (size_t index = 0; index < size(stones); index++) {
            if (uf.is_root(index)) {
                result++;
            }
        }
        return static_cast<int>(size(stones)) - result;
    }
};

void test(vector<vector<int>>&& stones) {
    cout << Solution().removeStones(stones) << endl;
}
int main()
{
    test(get_matrix_int("[[0,1],[1,2],[1,3],[3,3],[2,3],[0,2]]"));
    test(get_matrix_int("[[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]"));
    test(get_matrix_int("[[0,0],[0,2],[1,1],[2,0],[2,2]]"));
    test(get_matrix_int("[[0,0]]"));
    return 0;
}