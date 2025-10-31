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
    template <typename T>
    static T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

    static void update(map<int, int>& dpmp, int key, int value) {
        auto it = dpmp.find(key);
        if (it == cend(dpmp)) {
            dpmp.insert({ key, value });
        }
        else {
            it->second = min(it->second, value);
        }
    }

    int validSubarraySplit(vector<int>& nums) {
        if (nums.front() == 1 || nums.back() == 1) {
            return -1;
        }
        const auto n = size(nums);
        if (n == 1) {
            return 1;
        }
        vector<map<int, int>> dp(n - 1);
        dp[0].insert({ nums[0],0 });
        if (nums[1] > 1 && nums[0] != nums[1]) {
            dp[0].insert({ nums[1],1 });
        }

        for (int i = 1; i < n - 1; i++) {
            if (nums[i + 1] == 1) {
                dp[i] = dp[i - 1];
            }
            else {
                for (auto&& [current, count] : dp[i - 1]) {
                    update(dp[i], current, count);
                    const auto gcdval = gcd(nums[i], current);
                    if (gcdval > 1) {
                        update(dp[i], nums[i + 1], count + 1);
                    }
                }
            }
        }
        int min_val = INT_MAX;
        for (auto&& [current, count] : dp.back()) {
            const auto gcdval = gcd(nums.back(), current);
            if (gcdval > 1) {
                min_val = min(min_val, count + 1);
            }
        }
        if (min_val == INT_MAX) { return -1; }
        return min_val;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().validSubarraySplit(nums) << endl;
}
int main() {
    test(get_list_int("[2,6,3,4,3]"));
    test(get_list_int("[3,5]"));
    test(get_list_int("[1,2,1]"));
    return 0;
}