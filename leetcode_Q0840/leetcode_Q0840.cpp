// leetcode_Q0840.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

constexpr size_t SIZE = 3;
constexpr size_t COUNT = SIZE * SIZE;
constexpr size_t EXPECT_SUM = ((1 + COUNT) * COUNT / 2) / SIZE;
class Solution {
public:
    static bool check(const int& s) {
        return s == EXPECT_SUM;
    }
    static bool is_magic_square(const vector<vector<int>>& grid, int begin_y, int begin_x) {
        vector<bool> exists(SIZE * SIZE, false);
        vector<int> rows_sum(SIZE, 0);
        vector<int> cols_sum(SIZE, 0);
        vector<int> diagonal_sum(2, 0);

        for (size_t y = 0; y < SIZE; y++) {
            for (size_t x = 0; x < SIZE; x++) {
                const auto value = grid[y + begin_y][x + begin_x];
                if (value < 1 || 9 < value) { return false; }
                if (exists[value - 1]) {
                    return false;
                }
                exists[value - 1] = true;
                cols_sum[x] += value;
                rows_sum[y] += value;
            }
        }
        for (size_t y = 0; y < SIZE; y++) {
            diagonal_sum[0] += grid[y + begin_y][y + begin_x];
            diagonal_sum[1] += grid[y + begin_y][(SIZE - y - 1) + begin_x];
        }

        if (!all_of(cbegin(rows_sum), cend(rows_sum), check)) {
            return false;
        }
        if (!all_of(cbegin(cols_sum), cend(cols_sum), check)) {
            return false;
        }
        if (!all_of(cbegin(diagonal_sum), cend(diagonal_sum), check)) {
            return false;
        }
        return true;
    }

    int numMagicSquaresInside(vector<vector<int>>& grid) {
        const auto height = size(grid);
        const auto width = size(grid.front());
        if (height < SIZE || width < SIZE) {
            return 0;
        }
        int result = 0;
        for (size_t y = 0; y <= height - SIZE; y++) {
            for (size_t x = 0; x <= width - SIZE; x++) {
                if (is_magic_square(grid, y, x)) {
                    result += 1;
                }
            }
        }
        return result;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().numMagicSquaresInside(grid) << endl;
}
int main()
{
    test(get_matrix_int("[[4,7,8],[9,5,1],[2,3,6]]"));
    test(get_matrix_int("[[4,3,8,4],[9,5,1,9],[2,7,6,2]]"));
    test(get_matrix_int("[[8]]"));
    return 0;
}
