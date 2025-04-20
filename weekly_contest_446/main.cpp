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
    long long calculateScore(vector<string>& instructions, vector<int>& values) {
        const auto n = size(instructions);
        vector<bool> visited(n, false);
        int cur = 0;
        long long cur_score = 0LL;
        while (0 <= cur && cur < n) {
            if (visited[cur]) {
                break;
            }
            visited[cur] = true;
            if (instructions[cur] == "add") {
                cur_score += static_cast<long long>(values[cur]);
                cur++;
            }
            else { //"jump
                cur += values[cur];
            }
        }
        return cur_score;
    }
};
void test(vector<string>&& instructions, vector<int>&& values) {
    cout << Solution().calculateScore(instructions, values) << endl;
}
static void run() {
    test(get_list_str(R"(["jump","add","add","jump","add","jump"])"), get_list_int("[2,1,3,1,-2,-3]"));
    test(get_list_str(R"(["jump","add","add"])"), get_list_int("[3,1,1]"));
    test(get_list_str(R"(["jump"])"), get_list_int("[0]"));
}
}
namespace problem2 {
class Solution {
public:
    int maximumPossibleSize(vector<int>& nums) {
        int count = 1;
        int prev = nums[0];
        for (int i = 1; i < size(nums); i++) {
            if (prev <= nums[i]) {
                count++;
                prev = max(prev, nums[i]);
            }
        }
        return count;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().maximumPossibleSize(nums) << endl;
}
static void run() {
    test(get_list_int("[4,2,5,3,5]"));
    test(get_list_int("[1,2,3]"));
}
}
namespace problem3 {
class Solution {
public:

    static vector<long long> re(const vector<int>& nums, int k) {
        const auto n = size(nums);
        vector<long long> prefix_products(n + 1);
        prefix_products[0] = 1;
        for (int i = 0; i < n; i++) {
            prefix_products[i + 1] = prefix_products[i] * static_cast<long long>(nums[i]);
        }
        vector<long long> ans(k);
        for (int i = 0; i < k; i++) {
            if (i == 0) {
                long long cur_value = 1;
                int l = 0;
                long long cur_count = 0;
                for (int r = 0; r < n; r++) {
                    cur_value *= static_cast<long long>(nums[r]);
                    while (l < r && (((cur_value / nums[l]) % k) == 0)) {
                        cur_value /= nums[l];
                        l++;
                    }
                    if (cur_value % k == 0) {
                        cur_count += static_cast<long long>(l + 1);
                    }
                }
                ans[i] = cur_count;
            }
            else {
                long long cur_count = 0;
                for (int j = 0; j < n; j++) {
                    for (int l = j + 1; l <= n; l++) {
                        if ((prefix_products[l] / prefix_products[j]) % k == i) {
                            cur_count++;
                        }
                    }
                }
                ans[i] = cur_count;
            }
        }
        return ans;
    }


    vector<long long> resultArray(vector<int>& nums, int k) {
        const auto n = size(nums);
        vector<vector<long long>> dp(n, vector<long long>(k));
        vector<long long> ans(k);
        dp[0][nums[0] % k] = 1;
        ans[nums[0] % k] = 1;

        for (long long i = 1; i < n; i++) {
            for (long long j = 0; j < k; j++) {
                dp[i][(j * nums[i]) % k] += dp[i - 1][j];
            }
            dp[i][nums[i] % k]++;

            for (int j = 0; j < k; j++) {
                ans[j] += dp[i][j];
            }
        }
        return ans;
    }
};
void test(vector<int>&& nums, int k) {
    output(Solution().resultArray(nums, k));
}
static void run() {
    test(get_list_int("[1,2,3,4,5]"), 3);
    test(get_list_int("[1,2,4,8,16,32]"), 4);
    test(get_list_int("[1,1,2,1,1]"), 2);

}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}