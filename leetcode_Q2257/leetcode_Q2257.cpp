// leetcode_Q2257.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static pair<int, int> get_range(const vector<int>& prefix_sum, int value) {
        const auto it_low = lower_bound(cbegin(prefix_sum), cend(prefix_sum), value);
        const auto low_index = distance(cbegin(prefix_sum), it_low);
        const auto it_up = upper_bound(cbegin(prefix_sum), cend(prefix_sum), value);
        const auto up_index = distance(cbegin(prefix_sum), prev(it_up));
        return { low_index, up_index };
    }

    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<bool>> matrix(m, vector<bool>(n));
        vector<vector<int>> prefix_sums_guards_vertical(n, vector<int>(m + 1));
        vector<vector<int>> prefix_sums_guards_horizontal(m, vector<int>(n + 1));
        vector<vector<int>> prefix_sums_walls_vertical(n, vector<int>(m + 1));
        vector<vector<int>> prefix_sums_walls_horizontal(m, vector<int>(n + 1));

        for (auto&& guard : guards) {
            matrix[guard.front()][guard.back()] = true;
            prefix_sums_guards_vertical[guard.back()][guard.front() + 1] = 1;
            prefix_sums_guards_horizontal[guard.front()][guard.back() + 1] = 1;
        }
        for (auto&& wall : walls) {
            matrix[wall.front()][wall.back()] = true;
            prefix_sums_walls_vertical[wall.back()][wall.front() + 1] = 1;
            prefix_sums_walls_horizontal[wall.front()][wall.back() + 1] = 1;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix_sums_guards_vertical[j][i + 1] += prefix_sums_guards_vertical[j][i];
                prefix_sums_walls_vertical[j][i + 1] += prefix_sums_walls_vertical[j][i];

                prefix_sums_guards_horizontal[i][j + 1] += prefix_sums_guards_horizontal[i][j];
                prefix_sums_walls_horizontal[i][j + 1] += prefix_sums_walls_horizontal[i][j];
            }
        }
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!matrix[i][j]) {
                    const auto [h_lower, h_upper] = get_range(prefix_sums_walls_horizontal[i], prefix_sums_walls_horizontal[i][j + 1]);
                    if (prefix_sums_guards_horizontal[i][h_lower] == prefix_sums_guards_horizontal[i][h_upper]) {
                        const auto [v_lower, v_upper] = get_range(prefix_sums_walls_vertical[j], prefix_sums_walls_vertical[j][i + 1]);
                        if (prefix_sums_guards_vertical[j][v_lower] == prefix_sums_guards_vertical[j][v_upper]) {
                            count++;
                            cout << i << "," << j << endl;
                        }
                    }
                }
            }
        }
        return count;
    }
};

void test(int m, int n, vector<vector<int>>&& guards, vector<vector<int>>&& walls) {
    cout << Solution().countUnguarded(m, n, guards, walls) << endl;
}

int main()
{
    test(2, 7, get_matrix_int("[[1,5],[1,1],[1,6],[0,2]]"), get_matrix_int("[[0,6],[0,3],[0,5]]"));
    test(3, 3, get_matrix_int("[[1,1]]"), get_matrix_int("[[0,1],[1,0],[2,1],[1,2]]"));
    test(4, 6, get_matrix_int("[[0,0],[1,1],[2,3]]"), get_matrix_int("[[0,1],[2,2],[1,4]]"));
    return 0;
}