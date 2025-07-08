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

    int maxValue(vector<vector<int>>& events, int k) {
        sort(begin(events), end(events),
            [](const vector<int>& a, const vector<int>& b) {
                return a.front() < b.front();
            });
        const auto n = size(events);
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            const auto startday = events[i][0];
            const auto endday = events[i][1];
            const auto value = events[i][2];

            auto check = [&](int index)->bool {
                return endday < events[index][0];
                };
            const auto after_index = binary_search_meguru<int>(n, i, check);
            for (int j = 0; j < k; j++) {
                if (dp[i][j] >= 0) {
                    dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
                    dp[after_index][j + 1] = max(dp[after_index][j + 1], dp[i][j] + value);
                }
            }
            dp[i + 1][k] = max(dp[i][k], dp[i + 1][k]);
        }

        int max_value = 0;
        for (auto&& v : dp.back()) {
            max_value = max(max_value, v);
        }
        return max_value;
    }
};

void test(vector<vector<int>>&& events, int k) {
    cout << Solution().maxValue(events, k) << endl;
}

int main() {
    test(get_matrix_int("[[1,2,4],[3,4,3],[2,3,10]]"), 2);
    test(get_matrix_int("[[1,2,4],[3,4,3],[2,3,1]]"), 2);
    test(get_matrix_int("[[1,1,1],[2,2,2],[3,3,3],[4,4,4]]"), 3);
    return 0;
}