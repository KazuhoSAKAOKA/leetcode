// leetcode_Q2371.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> minScore(vector<vector<int>>& grid) {
        vector<pair<int, int>> order;
        const auto HEIGHT = size(grid);
        const auto WIDTH = size(grid.front());
        order.reserve(HEIGHT * WIDTH);
        for (auto i = 0; i < HEIGHT; i++) {
            for (auto j = 0; j < WIDTH; j++) {
                order.emplace_back(make_pair(i,j));
            }
        }
        sort(begin(order), end(order), [&](auto a, auto b) { return grid[a.first][a.second] < grid[b.first][b.second]; });

        vector<vector<int>> ans(HEIGHT, vector<int>(WIDTH));

        vector<int> column_mins(WIDTH);
        vector<int> row_mins(HEIGHT);
        for (auto&& [y, x] : order) {
            const auto current_min = max(row_mins[y], column_mins[x]) + 1;
            ans[y][x] = current_min;
            row_mins[y] = column_mins[x] = current_min;
        }
        return ans;
    }
};

void test(vector<vector<int>>&& grid) {
    output_matrix( Solution().minScore(grid));
}
int main()
{
    test(get_matrix_int("[[3,1],[2,5]]"));
    test(get_matrix_int("[[10]]"));
    return 0;
}