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


    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        constexpr long long MODULO = 12345;
        const auto n = size(grid);
        const auto m = size(grid.front());
        const auto N = n * m;
        vector<long long> prefix_prods_pre(N + 1, 1LL);
        vector<long long> prefix_prods_suf(N + 1, 1LL);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                const auto index1 = i * m + j;
                prefix_prods_pre[index1 + 1] = (prefix_prods_pre[index1] * grid[i][j]) % MODULO;
                const auto index2 = (n - i - 1) * m + (m - j - 1);
                prefix_prods_suf[index2] = (prefix_prods_suf[index2 + 1] * grid[n - i - 1][m - j - 1]) % MODULO;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                const auto index1 = i * m + j;
                grid[i][j] = (prefix_prods_pre[index1] * prefix_prods_suf[index1 + 1]) % MODULO;
            }
        }
        return grid;
    }
};
static void test(vector<vector<int>>&& grid) {
    output_matrix(Solution().constructProductMatrix(grid));
}

int main() {
    test(get_matrix_int("[[1,2],[3,4]]"));
    test(get_matrix_int("[[12345],[2],[1]]"));
    return 0;
}