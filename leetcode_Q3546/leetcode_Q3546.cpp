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

    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        const auto m = size(grid);
        const auto n = size(grid.front());
        vector<vector<long long>> prefix_sums(m + 1, vector<long long>(n + 1, 0LL));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + static_cast<long long>(grid[i][j]);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto get_sum = [&](int ybegin, int xbegin, int yend, int xend) -> long long {
            return prefix_sums[yend][xend] - prefix_sums[yend][xbegin] - prefix_sums[ybegin][xend] + prefix_sums[ybegin][xbegin];
            };
        const auto total = prefix_sums[m][n];
        if (total % 2 != 0) {
            return false;
        }
        const auto half = total / 2;

        {
            auto ok = m - 1;
            auto ng = 0;
            auto check = [&](int y)->bool {
                return half <= get_sum(0, 0, y, n);
                };
            if (check(ok)) {
                const auto v = binary_search_meguru<int>(ok, ng, check);
                if (get_sum(0, 0, v, n) == half) {
                    return true;
                }
            }
        }
        {
            auto ok = n - 1;
            auto ng = 0;
            auto check = [&](int x)->bool {
                return half <= get_sum(0, 0, m, x);
                };
            if (check(ok)) {
                const auto v = binary_search_meguru<int>(ok, ng, check);
                if (get_sum(0, 0, m, v) == half) {
                    return true;
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
    test(get_matrix_int("[[54756,54756]]"));
    test(get_matrix_int("[[1,4],[2,3]]"));
    test(get_matrix_int("[[1,3],[2,4]]"));
    return 0;
}