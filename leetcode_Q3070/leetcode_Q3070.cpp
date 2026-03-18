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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
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

    int countSubmatrices(vector<vector<int>>& grid, int k) {
        const int n = static_cast<int>(size(grid));
        const int m = static_cast<int>(size(grid.front()));

        vector<vector<long long>> sums(n + 1, vector<long long>(m + 1, 0));

        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < m; j++) {
                sums[i + 1][j + 1] = sums[i + 1][j] + grid[i][j];
            }
        }
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < m; j++) {
                sums[i + 1][j + 1] += sums[i][j + 1];
            }
        }

        int count = 0;
        for (auto i = 0; i < n; i++) {
            const auto maxsize = sums[i + 1][m];
            const auto minsize = sums[i + 1][1];
            if (maxsize <= k) {
                count += m;
            }
            else if (k < minsize) {

            }
            else {
                int ok = 1;
                int ng = m;
                auto cur_count = binary_search_meguru<int>(ok, ng, [&](int v)->bool {
                    return sums[i + 1][v] <= k;
                    });
                count += cur_count;
            }
        }
        return count;
    }
};
static void test(vector<vector<int>>&& grid, int k) {
    cout << Solution().countSubmatrices(grid, k) << endl;
}
int main()
{
    test(get_matrix_int("[[7,6,3],[6,6,1]]"), 18);
    test(get_matrix_int("[[7,2,9],[1,5,0],[2,6,6]]"), 20);
    return 0;
}