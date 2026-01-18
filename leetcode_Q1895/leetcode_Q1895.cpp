#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <climits>
#include <cassert>
#include <tuple>
#include <chrono>
#include <optional>
#include <queue>
#include <memory>
#include <random>
#include <exception>
#include <functional>
#include <ranges>
#include <iomanip>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        const auto n = size(grid);
        const auto m = size(grid[0]);
        vector<vector<long long>> prefix_sums(n + 1, vector<long long>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + grid[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto get_sum = [&](int y1, int x1, int y2, int x2)-> long long {
            return prefix_sums[y2][x2] - prefix_sums[y1][x2] - prefix_sums[y2][x1] + prefix_sums[y1][x1];
            };

        int max_len = 1;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < m - 1; j++) {
                const auto limit = min(n - i, m - j);
                int len = 2;
                while (len <= limit) {
                    const int total = get_sum(i, j, i + len, j + len);
                    if (total % len == 0) {
                        const int each_sum = total / len;
                        bool ng = false;
                        long long diag1 = 0LL;
                        long long diag2 = 0LL;
                        for (int k = 0; k < len; k++) {
                            const auto rsum = get_sum(i + k, j, i + k + 1, j + len);
                            if (rsum != each_sum) {
                                ng = true;
                                break;
                            }
                            const auto csum = get_sum(i, j + k, i + len, j + k + 1);
                            if (csum != each_sum) {
                                ng = true;
                                break;
                            }
                            diag1 += grid[i + k][j + k];
                            diag2 += grid[i + k][j + len - 1 - k];
                        }
                        if (!ng && (diag1 == each_sum) && (diag2 == each_sum)) {
                            max_len = max(max_len, len);
                        }
                    }
                    len++;
                }


            }
        }

        return max_len;
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().largestMagicSquare(grid) << endl;
}

int main()
{
    test(get_matrix_int("[[1,17,15,17,5,16,8,9],[1,19,11,18,8,18,3,18],[6,6,5,8,3,15,6,11],[19,5,6,11,9,2,14,13],[12,16,16,15,14,18,10,7],[3,11,15,15,7,1,9,8],[15,5,11,17,18,20,14,17],[13,17,7,20,12,2,13,19]]"));
    test(get_matrix_int("[[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]"));
    test(get_matrix_int("[[5,1,3,1],[9,3,3,1],[1,3,3,8]]"));
    return 0;
}