// leetcode_Q0861.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    static int get_value(const vector<int>& columns) {
        int value = 0;
        for (int j = 0; j < columns.size(); j++) {
            if (columns[j] != 0) {
                value += (1 << (columns.size() - 1 - j));
            }
        }
        return value;
    }

    static int calculate(const vector<vector<int>>& grid) {
        int total = 0;
        for (int i = 0; i < grid.size(); i++) {
            total += get_value(grid[i]);
        }
        return total;
    }

    static void flip_rows(vector<vector<int>>& grid, int index) {
        for (int i = 0; i < grid.size(); i++) {
            grid[i][index] = grid[i][index] == 0 ? 1 : 0;
        }
    }
    static void flip_columns(vector<vector<int>>& grid, int index) {
        for (int j = 0; j < grid.front().size(); j++) {
            grid[index][j] = grid[index][j] == 0 ? 1 : 0;
        }
    }

    static int tle(vector<vector<int>>& grid) {
        int max_value = 0;

        const int rows_bit_max = 1 << grid.size();
        const int columns_bit_max = 1 << grid.front().size();
        for (int row_bits = 0; row_bits < rows_bit_max; row_bits++) {
            for (int column_bits = 0; column_bits < columns_bit_max; column_bits++) {
                for (int i = 0; i < grid.size(); i++) {
                    if ((row_bits & (1 << i)) != 0) {
                        flip_columns(grid, i);
                    }
                }
                for (int j = 0; j < grid.front().size(); j++) {
                    if ((column_bits & (1 << j)) != 0) {
                        flip_rows(grid, j);
                    }
                }
                max_value = max(max_value, calculate(grid));
                for (int i = 0; i < grid.size(); i++) {
                    if ((row_bits & (1 << i)) != 0) {
                        flip_columns(grid, i);
                    }
                }
                for (int j = 0; j < grid.front().size(); j++) {
                    if ((column_bits & (1 << j)) != 0) {
                        flip_rows(grid, j);
                    }
                }
            }
        }
        return max_value;
    }

    static int tle2(vector<vector<int>>& grid) {
        const int H = grid.size();
        const int W = grid.front().size();

        for (int i = 0; i < H; i++) {
            if (grid[i][0] == 0) {
                flip_columns(grid, i);
            }
        }

        const int columns_bit_max = 1 << (grid.front().size() - 1);
        int total = 0;
        for (int column_bits = 0; column_bits < columns_bit_max; column_bits++) {
            for (int j = 0; j < grid.front().size() - 1; j++) {
                if ((column_bits & (1 << j)) != 0) {
                    flip_rows(grid, j + 1);
                }
            }
            total = max(total, calculate(grid));
            for (int j = 0; j < grid.front().size() - 1; j++) {
                if ((column_bits & (1 << j)) != 0) {
                    flip_rows(grid, j + 1);
                }
            }
        }
        return total;
    }

    int matrixScore(vector<vector<int>>& grid) {
        const int H = grid.size();
        const int W = grid.front().size();

        for (int i = 0; i < H; i++) {
            if (grid[i][0] == 0) {
                flip_columns(grid, i);
            }
        }
        auto counting = [&](int index) {
            int count = 0;
            for (int i = 0; i < grid.size(); i++) {
                if (grid[i][index] != 0) {
                    count++;
                }
            }
            return count;
            };

        for (int j = 1; j < W; j++) {
            const auto count = counting(j);
            if (count < (H + 1) / 2) {
                flip_rows(grid, j);
            }
        }

        return calculate(grid);
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().matrixScore(grid) << endl;
}

int main()
{
    test({ {0,0,1,1,},{1,0,1,0,},{1,1,0,0,}, });
    test({ {0} });
}