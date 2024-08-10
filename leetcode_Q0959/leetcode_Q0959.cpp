// leetcode_Q0959.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
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

        bool is_root(size_t x) {
            return root(x) == x;
        }
    };

    int regionsBySlashes(vector<string>& grid) {
        const int n = size(grid);
        if (n != size(grid.front())) {
            cerr << "unexpected data" << endl;
            return 0;
        }
        const int TOP = 0;
        const int LEFT = 1;
        const int RIGHT = 2;
        const int BOTTOM = 3;
        union_find uf(n * n * 4);
        const int N = n * 4;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                const auto c = grid[i][j];
                const int current_base = i * N + j * 4;
                switch (c) {
                case ' ':
                    uf.unite(current_base + TOP, current_base + LEFT);
                    uf.unite(current_base + LEFT, current_base + RIGHT);
                    uf.unite(current_base + RIGHT, current_base + BOTTOM);
                    break;
                case '/':
                    uf.unite(current_base + TOP, current_base + LEFT);
                    uf.unite(current_base + RIGHT, current_base + BOTTOM);
                    break;
                case '\\':
                    uf.unite(current_base + TOP, current_base + RIGHT);
                    uf.unite(current_base + LEFT, current_base + BOTTOM);
                    break;
                default:
                    cerr << "unexpected data" << endl;
                    return 0;
                }
                if (i < n - 1) {
                    const int bottom_base = (i + 1) * N + j * 4;
                    uf.unite(current_base + BOTTOM, bottom_base + TOP);
                }
                if (j < n - 1) {
                    const int right_base = i * N + (j + 1) * 4;
                    uf.unite(current_base + RIGHT, right_base + LEFT);
                }
            }
        }
        int count = 0;
        for (int i = 0; i < n * n * 4; i++) {
            if (uf.is_root(i)) {
                count++;
            }
        }

        return count;
    }
};

void test(vector<string>&& grid) {
    cout << Solution().regionsBySlashes(grid) << endl;
}
int main()
{
    test(get_list_str(R"([" /","/ "])"));
    test(get_list_str(R"([" /","  "])"));
    test(get_list_str(R"(["/\","\/"])"));
    return 0;
}