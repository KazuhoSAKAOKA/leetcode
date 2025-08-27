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
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        const auto h = size(grid);
        const auto w = size(grid.front());

        vector<vector<vector<int>>> memo(h, vector<vector<int>>(w, vector<int>(4, -1)));

        const vector<pair<int, int>> dirs{
            {-1,1},
            {1,1},
            {1,-1},
            {-1,-1},
        };

        auto get_side_len = [&](auto get_side_len, int y, int x, int index, int cur_value)->int {
            if (memo[y][x][index] >= 0) {
                return memo[y][x][index];
            }
            const auto nexty = y + dirs[index].first;
            const auto nextx = x + dirs[index].second;
            if (nexty < 0 || h <= nexty || nextx < 0 || w <= nextx) {
                return 0;
            }
            if ((grid[nexty][nextx] == 1) ||
                (((cur_value == 1) || (cur_value == 0)) && grid[nexty][nextx] != 2) ||
                (cur_value == 2 && grid[nexty][nextx] != 0)) {
                return 0;
            }
            memo[y][x][index] = get_side_len(get_side_len, nexty, nextx, index, grid[nexty][nextx]) + 1;
            return memo[y][x][index];
            };

        auto get_len = [&](auto get_len, int y, int x, int index, int cur_value)->int{
            const auto nexty = y + dirs[index].first;
            const auto nextx = x + dirs[index].second;
            if (nexty < 0 || h <= nexty || nextx < 0 || w <= nextx) {
                return 0;
            }
            if ((grid[nexty][nextx] == 1) ||
                (((cur_value == 1) || (cur_value == 0)) && grid[nexty][nextx] != 2) ||
                (cur_value == 2 && grid[nexty][nextx] != 0)) {
                return 0;
            }
            int cur_len = get_len(get_len, nexty, nextx, index, grid[nexty][nextx]) + 1;
            int side_len = get_side_len(get_side_len, nexty, nextx, (index + 1) % 4, grid[nexty][nextx]) + 1;
            return max(cur_len, side_len);
        };
        int max_len = 0;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (grid[i][j] == 1) {
                    for (int dirindex = 0; dirindex < 4; dirindex++) {
                        const auto cur_len = get_len(get_len, i, j, dirindex, 1) + 1;
                        max_len = max(max_len, cur_len);
                    }
                }
            }
        }
        return max_len;
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().lenOfVDiagonal(grid) << endl;
}

int main() {
    test(get_matrix_int("[[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]"));
    test(get_matrix_int("[[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]"));
    test(get_matrix_int("[[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]"));
    return 0;
}