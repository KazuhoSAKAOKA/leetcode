// leetcode_Q1579.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    };

    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int use_count = 0;
        union_find common_uf(n);
        for (auto&& edge : edges) {
            if (edge[0] == 3 && !common_uf.same(edge[1] - 1, edge[2] - 1)) {
                common_uf.unite(edge[1] - 1, edge[2] - 1);
                use_count++;
                if (common_uf.size(edge[1] - 1) == n) {
                    return edges.size() - use_count;
                }
            }
        }
        union_find alice_uf(common_uf);
        union_find bob_uf(common_uf);

        int alice_use_count = 0;
        int bob_use_count = 0;
        for (auto&& edge : edges) {
            if (edge[0] == 1 && !alice_uf.same(edge[1] - 1, edge[2] - 1)) {
                alice_uf.unite(edge[1] - 1, edge[2] - 1);
                alice_use_count++;
            }
            else if(edge[0] == 2 && !bob_uf.same(edge[1] - 1, edge[2] - 1)) {
                bob_uf.unite(edge[1] - 1, edge[2] - 1);
                bob_use_count++;
            }
        }

        if (alice_uf.size(0) != n || bob_uf.size(0) != n) {
            return -1;
        }

        return edges.size() - use_count - alice_use_count - bob_use_count;
    }
};

void test(int n, vector<vector<int>>&& edges) {
    cout << Solution().maxNumEdgesToRemove(n, edges) << endl;
}

int main()
{
    test(4, get_matrix_int("[[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]"));
    test(4, get_matrix_int("[[3,1,2],[3,2,3],[1,1,4],[2,1,4]]"));
    test(4, get_matrix_int("[[3,2,3],[1,1,2],[2,3,4]]"));
}