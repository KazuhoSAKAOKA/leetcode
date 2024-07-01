// leetcode_Q1101.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

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

    int earliestAcq(vector<vector<int>>& logs, int n) {

        union_find uf(n);

        sort(begin(logs), end(logs), [](const auto& a, const auto& b) {
            return a.front() < b.front();
            });

        for (auto&& ev : logs) {
            uf.unite(ev[1], ev[2]);
            if (uf.size(0) == n) {
                return ev.front();
            }
        }
        return -1;
    }
};

void test(vector<vector<int>>&& logs, int n) {
    cout << Solution().earliestAcq(logs, n) << endl;
}

int main()
{
    test(get_matrix_int("[[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]]"), 6);
    test(get_matrix_int("[[0,2,0],[1,0,1],[3,0,3],[4,1,2],[7,3,1]]"), 4);
}