#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:

    static int mle(vector<int>& nums, int p) {
        if (p == 0) {
            return 0;
        }
        const auto n = size(nums);
        sort(begin(nums), end(nums));
        if (n == 2) {
            return nums[1] - nums[0];
        }
        vector<vector<int>> dp(n - 1, vector<int>(p + 1, INT_MAX));
        dp[0][0] = 0;
        dp[0][1] = nums[1] - nums[0];
        dp[1][0] = 0;
        dp[1][1] = min(dp[0][1], nums[2] - nums[1]);
        for (int i = 2; i < n - 1; i++) {
            dp[i][0] = 0;
            const auto diff = nums[i + 1] - nums[i];
            for (int j = 1; j <= p; j++) {
                dp[i][j] = min(max(dp[i - 2][j - 1], diff), dp[i - 1][j]);
            }
        }
        return min(dp[n - 3][p], dp[n - 2][p]);
    }

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
    int minimizeMax(vector<int>& nums, int p) {
        if (p == 0) {
            return 0;
        }
        const auto n = size(nums);
        sort(begin(nums), end(nums));
        if (n == 2) {
            return nums[1] - nums[0];
        }
        int ok = 0;
        for (int i = 0; i < n / 2; i++) {
            ok = max(ok, nums[i * 2 + 1] - nums[i * 2]);
        }
        auto check = [&](int v) {
            int prev2 = nums[1] - nums[0] <= v ? 1 : 0;
            int prev1 = max(prev2, nums[2] - nums[1] <= v ? 1 : 0);
            for (int i = 2; i < n - 1; i++) {
                int cur = max(prev2 + (nums[i + 1] - nums[i] <= v ? 1 : 0), prev1);
                prev2 = prev1;
                prev1 = cur;
            }
            return prev1 >= p || prev2 >= p;
            };

        const auto ans = binary_search_meguru<int>(ok, -1, check);

        return ans;
    }
};

void test(vector<int>&& nums, int p) {
    cout << Solution().minimizeMax(nums, p) << endl;
}
int main() {
    test(get_list_int("[6,2,6,2,6,6,3]"), 3);
    test(get_list_int("[10,1,2,7,1,3]"), 2);
    test(get_list_int("[0,0,4,1,7]"), 1);
    test(get_list_int("[1,2]"), 1);
    test(get_list_int("[3,3,5,1,0,5,6,6]"), 4);
    test(get_list_int("[4,2,1,2]"), 1);
    return 0;
}