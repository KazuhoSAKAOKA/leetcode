#include <iostream>
#include <vector>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static int naive(vector<int>& nums, int k) {
        constexpr size_t MODULO = 1e9 + 7;
        const auto n = size(nums);
        vector<map<pair<int, int>, long long>> dp(n - 1);
        {
            const auto cur_min = min(nums[0], nums[1]);
            const auto cur_max = max(nums[0], nums[1]);
            if (cur_max - cur_min <= k) {
                dp[0][{cur_min, cur_max }] += 1LL;
            }
            dp[0][{nums[1], nums[1]}] += 1;
        }
        for (int i = 1; i < n - 1; i++) {
            for (auto&& [p1, count] : dp[i - 1]) {
                const auto& [cur_min, cur_max] = p1;
                const auto new_min = min(cur_min, nums[i + 1]);
                const auto new_max = max(cur_max, nums[i + 1]);
                if (new_max - new_min <= k) {
                    dp[i][{new_min, new_max }] += count;
                    dp[i][{new_min, new_max }] %= MODULO;
                }
                dp[i][{nums[i + 1], nums[i + 1]}] += count;
                dp[i][{nums[i + 1], nums[i + 1]}] %= MODULO;

            }
        }

        long long ans = 0;
        for (auto&& [_, count] : dp.back()) {
            ans += count;
            ans %= MODULO;
        }

        return ans;
    }

    int countPartitions(vector<int>& nums, int k) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(nums);
        vector<long long> dp(n + 1);
        vector<long long> prefix_sums(n + 2);
        dp[0] = 1;
        prefix_sums[1] = dp[0];
        map<int, int> min_max_map;
        int l = 0;
        for (int r = 0; r < n; r++) {
            min_max_map[nums[r]]++;
            while ( l < r && ((crbegin(min_max_map)->first - cbegin(min_max_map)->first) > k)) {
                auto it = min_max_map.find(nums[l]);
                if (it->second == 1) {
                    min_max_map.erase(it);
                }
                else {
                    it->second--;
                }
                l++;
            }
            dp[r + 1] = (prefix_sums[r + 1] - prefix_sums[l] + MODULO) % MODULO;
            prefix_sums[r + 2] = prefix_sums[r + 1] + dp[r + 1];
        }
        return static_cast<int>(dp.back());
    }
};

static void test(vector<int>&& nums, int k) {
    cout << Solution().countPartitions(nums, k) << endl;
}
int main()
{
    test(get_list_int("[9,4,1,3,7]"), 4);
    test(get_list_int("[3,3,4]"), 0);


    return 0;
}