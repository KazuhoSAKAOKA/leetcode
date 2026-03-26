#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        const auto rows = size(grid);
        const auto cols = size(grid.front());
        vector<vector<long long>> prefix_sums(rows + 1, vector<long long>(cols + 1, 0LL));
        unordered_map<long long, set<int>> y_value_map;
        unordered_map<long long, set<int>> x_value_map;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                y_value_map[grid[i][j]].insert(i);
                x_value_map[grid[i][j]].insert(j);
            }
        }


        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + static_cast<long long>(grid[i][j]);
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto get_sum = [&](int ybegin, int xbegin, int yend, int xend) -> long long {
            return prefix_sums[yend][xend] - prefix_sums[yend][xbegin] - prefix_sums[ybegin][xend] + prefix_sums[ybegin][xbegin];
            };
        const auto total = prefix_sums[rows][cols];


        const auto half = total %2 == 0 ? total / 2 : total;

        auto exist_high = [](const set<int>& indexes, int index)->bool {
            auto it1 = indexes.lower_bound(index);
            return it1 != cend(indexes);
            };

        auto exist_low = [](const set<int>& indexes, int index)->bool {
            auto it1 = indexes.lower_bound(index);
            return it1 != cbegin(indexes);
            };

        for (int i = 1; i < rows; i++) {
            const auto cur_sum = get_sum(0, 0, i, cols);
            if (cur_sum == half) {
                return true;
            }
            auto diff = total - 2 * cur_sum;
            const auto it = y_value_map.find(abs(diff));
            if (it != cend(y_value_map)) {
                auto& y_indexes = it->second;
                if (0 < diff) {
                    if (i == rows - 1) {
                        if (grid[rows - 1][0] == diff || grid[rows - 1][cols - 1] == diff) {
                            return true;
                        }
                    }
                    else if (cols == 1) {
                        if (grid[i][0] == diff || grid[rows - 1][0] == diff) {
                            return true;
                        }
                    }
                    else {
                        if (exist_high(y_indexes, i)) {
                            return true;
                        }
                    }
                }
                else {
                    diff *= -1;
                    if (i == 1) {
                        if (grid[0][0] == diff || grid[0][cols - 1] == diff) {
                            return true;
                        }
                    }
                    else if (cols == 1) {
                        if (grid[0][0] == diff || grid[i - 1][0] == diff) {
                            return true;
                        }
                    }
                    else {
                        if (exist_low(y_indexes, i)) {
                            return true;
                        }
                    }
                }
            }
        }
        for (int i = 1; i < cols; i++) {
            const auto cur_sum = get_sum(0, 0, rows, i);
            if (get_sum(0, 0, rows, i) == half) {
                return true;
            }
            auto diff = total - 2 * cur_sum;
            const auto it = x_value_map.find(abs(diff));
            if (it != cend(x_value_map)) {
                auto& x_indexes = it->second;
                if (0 < diff) {
                    if (i == cols - 1) {
                        if (grid[0][cols - 1] == diff || grid[rows - 1][cols - 1] == diff) {
                            return true;
                        }
                    }
                    else if (rows == 1) {
                        if (grid[0][i] == diff || grid[0][cols - 1] == diff) {
                            return true;
                        }
                    }
                    else {
                        if (exist_high(x_indexes, i)) {
                            return true;
                        }
                    }
                }
                else {
                    diff *= -1;
                    if (i == 1) {
                        if (grid[0][0] == diff || grid[rows - 1][0] == diff) {
                            return true;
                        }
                    }
                    else if (rows == 1) {
                        if (grid[0][0] == diff || grid[0][i - 1] == diff) {
                            return true;
                        }
                    }
                    else {
                        if (exist_low(x_indexes, i)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().canPartitionGrid(grid) << endl;
}
int main() {
    test(get_matrix_int("[[25372],[100000],[100000]]"));
    test(get_matrix_int("[[5,5,6,2,2,2]]"));
    test(get_matrix_int("[[1,4],[2,3]]"));
    test(get_matrix_int("[[1,2],[3,4]]"));
    test(get_matrix_int("[[1,2,4],[2,3,5]]"));
    test(get_matrix_int("[[4,1,8],[3,2,6]]"));
    test(get_matrix_int("[[54756,54756]]"));
    return 0;
}