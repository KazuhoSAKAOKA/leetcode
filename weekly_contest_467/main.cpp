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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
    class Solution {
    public:
        int earliestTime(vector<vector<int>>& tasks) {
            int min_time = INT_MAX;
            for (auto&& task : tasks) {
                min_time = min(min_time, task.front() + task.back());
            }
            return min_time;
        }
    };
    static void test(vector<vector<int>>&& tasks) {
        cout << Solution().earliestTime(tasks) << endl;
    }
static void run() {
    test(get_matrix_int("[[1,6],[2,3]]"));
    test(get_matrix_int("[[100,100],[100,100],[100,100]]"));
}
}
namespace problem2 {
class Solution {
public:
    vector<int> maxKDistinct(vector<int>& nums, int k) {
        set<int, greater<int>> exists;
        for (auto&& num : nums) {
            exists.insert(num);
        }
        vector<int> ans;
        ans.reserve(k);
        auto it = cbegin(exists);
        for (int i = 0; i < k; i++) {
            if (it == cend(exists)) {
                break;
            }
            ans.emplace_back(*it);
            ++it;
        }
        return ans;
    }
};
static void test(vector<int>&& nums, int k) {
    output(Solution().maxKDistinct(nums, k));
}
static void run() {
    test(get_list_int("[84,93,100,77,90]"), 3);
    test(get_list_int("[84,93,100,77,93]"), 3);
    test(get_list_int("[1,1,1,2,2,2]"), 6);
}
}
namespace problem3 {
class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        const auto n = size(nums);
        vector<bool> ans;
        ans.reserve(n);
        sort(begin(nums), end(nums));
        
        vector<vector<bool>> dp(n + 1, vector<bool>(k + 2));
        dp[0][0] = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                if (dp[i][j]) {
                    dp[i + 1][j] = true;
                    dp[i + 1][min(k + 1, j + nums[i])] = true;
                }
            }
        }


        for (int i = 0; i < n; i++) {
            const auto cur_x = i + 1;
            const auto limit_it = lower_bound(cbegin(nums), cend(nums), cur_x);
            const auto n_val_count = distance(limit_it, cend(nums));
            if (k % cur_x == 0 && k / cur_x <= n_val_count) {
                ans.emplace_back(true);
            }
            else {
                const auto index = distance(cbegin(nums), limit_it);
                bool exists = false;
                for (int j = k; j >=0; j--) {
                    const auto temp = k - j;
                    if (dp[index][j] && temp % cur_x == 0 && temp / cur_x <= n_val_count) {
                        exists = true;
                        break;
                    }
                }
                ans.emplace_back(exists);
            }
        }
        return ans;
    }
};
static void test(vector<int>&& nums, int k) {
    output(Solution().subsequenceSumAfterCapping(nums, k));
}
static void run() {
    test(get_list_int("[5,7,3,5,5,6,5]"), 16);
    test(get_list_int("[4,3,2,4]"), 5);
    test(get_list_int("[1,2,3,4,5]"), 3);
}
}
namespace problem4 {

class Solution {
public:


    int countStableSubsequences(vector<int>& nums) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(nums);
        if (n == 1) {
            return 1LL;
        }
        if (n == 2) {
            return 3;
        }
        long long even_count = 0LL;
        long long odd_count = 0LL;
        vector<vector<long long>> dp(n, vector<long long>(4));
        const auto ev0 = nums[0] % 2 == 0;
        const auto ev1 = nums[1] % 2 == 0;
        if (ev0 && ev1) {
            even_count = 2LL;
            dp[1][0] = 1LL;
        }
        else if (ev0 && !ev1) {
            even_count = 1LL;
            odd_count = 1LL;
            dp[1][1] = 1LL;
        }
        else if (!ev0 && ev1) {
            even_count = 1LL;
            odd_count = 1LL;
            dp[1][2] = 1LL;
        }
        else if (!ev0 && !ev1) {
            odd_count = 2LL;
            dp[1][3] = 1LL;
        }
        long long count = 3LL;

        for (long long i = 2; i < n; i++) {
            const auto even = nums[i] % 2 == 0;
            count += (i + 1);
            count %= MODULO;
            for (int j = 0; j < 4; j++) {
                dp[i][j] = dp[i - 1][j];
            }

            if (even) {
                count += dp[i - 1][1];
                count += dp[i - 1][2];
                count += dp[i - 1][3];

                dp[i][0] += (dp[i - 1][2] + even_count);
                dp[i][0] %= MODULO;
                dp[i][2] += (dp[i - 1][3] + dp[i - 1][1] + odd_count);
                dp[i][2] %= MODULO;
                even_count++;
                even_count %= MODULO;
            }
            else {
                count += dp[i - 1][0];
                count += dp[i - 1][1];
                count += dp[i - 1][2];

                dp[i][1] += (dp[i - 1][0] + dp[i - 1][2] + even_count);
                dp[i][1] %= MODULO;
                dp[i][3] += (dp[i - 1][1] + odd_count);
                dp[i][3] %= MODULO;
                odd_count++;
                odd_count %= MODULO;
            }
            count %= MODULO;
        }
        return static_cast<int>(count % MODULO);
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().countStableSubsequences(nums) << endl;
}
static void run() {
    test(get_list_int("[7,17,7,8]"));
    test(get_list_int("[4,19,9,13]"));
    test(get_list_int("[2,3,4,2]"));
    test(get_list_int("[1,3,5]"));
}
}
int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}