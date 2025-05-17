#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


class Solution {
public:


    int maxKilledEnemies(vector<vector<char>>& grid) {
        const auto n = size(grid);
        const auto m = size(grid.front());

        vector<vector<int>> wall_prefix_sums_listy(n, vector<int>(m + 1));
        vector<vector<int>> enemy_prefix_sums_listy(n, vector<int>(m + 1));
        vector<vector<int>> wall_prefix_sums_listx(m, vector<int>(n + 1));
        vector<vector<int>> enemy_prefix_sums_listx(m, vector<int>(n + 1));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                wall_prefix_sums_listy[i][j + 1] = wall_prefix_sums_listy[i][j] + (grid[i][j] == 'W' ? 1 : 0);
                enemy_prefix_sums_listy[i][j + 1] = enemy_prefix_sums_listy[i][j] + (grid[i][j] == 'E' ? 1 : 0);
            }
        }
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                wall_prefix_sums_listx[j][i + 1] = wall_prefix_sums_listx[j][i] + (grid[i][j] == 'W' ? 1 : 0);
                enemy_prefix_sums_listx[j][i + 1] = enemy_prefix_sums_listx[j][i] + (grid[i][j] == 'E' ? 1 : 0);
            }
        }

        auto calc = [](const vector<int>& wall_prefix_sums, const vector<int>& enemy_prefix_sums, int index)-> int {
            const auto cur_range_val = wall_prefix_sums[index];
            const auto itbegin = lower_bound(cbegin(wall_prefix_sums), cend(wall_prefix_sums), cur_range_val);
            const auto itend = upper_bound(cbegin(wall_prefix_sums), cend(wall_prefix_sums), cur_range_val);
            const auto range_begin = distance(cbegin(wall_prefix_sums), itbegin);
            const auto range_end = distance(cbegin(wall_prefix_sums), itend) - 1;
            return enemy_prefix_sums[range_end] - enemy_prefix_sums[range_begin];
            };

        int max_value = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '0') {
                    const auto yenemy = calc(wall_prefix_sums_listy[i], enemy_prefix_sums_listy[i], j);
                    const auto xenemy = calc(wall_prefix_sums_listx[j], enemy_prefix_sums_listx[j], i);
                    max_value = max(max_value, yenemy + xenemy);
                }
            }
        }
        return max_value;
    }
};

void test(vector<vector<char>>&& grid) {
    cout << Solution().maxKilledEnemies(grid) << endl;
}
int main() {
    test(get_matrix_char(R"([["0","0","0"]])"));
    test(get_matrix_char(R"([["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]])"));
    test(get_matrix_char(R"([["W","W","W"],["0","0","0"],["E","E","E"]])"));
    return 0;
}