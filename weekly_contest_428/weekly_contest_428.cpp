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
    int buttonWithLongestTime(vector<vector<int>>& events) {
        map<int, int> duration_map;
        int before_time = 0;
        for (int i = 0; i < size(events); i++) {
            const auto& event = events[i];
            const auto button = event.front();
            const auto time = event.back();
            const auto duration = time - before_time;
            duration_map[button] = max(duration_map[button],duration);
            before_time = time;
        }
        int max_duration = 0;
        int longest_button = -1;
        for (auto&& [button, duration] : duration_map) {
            if (max_duration < duration) {
                longest_button = button;
                max_duration = duration;
            }
        }
        return longest_button;
    }
}; 
void test(vector<vector<int>>&& events) {
    cout << Solution().buttonWithLongestTime(events) << endl;
}
static void run() {
    test(get_matrix_int("[[7,1],[19,3],[9,4],[12,5],[2,8],[15,10],[18,12],[7,14],[19,16]]"));
    test(get_matrix_int("[[1,2],[2,5],[3,9],[1,15]]"));
    test(get_matrix_int("[[10,5],[1,7]]"));
}
}
namespace problem2 {
class Solution {
public:
    using MYLIST_T = vector<pair<vector<vector<string>>, vector<double>>>;

    static double rec(const MYLIST_T& list, int index, const string& initialCurrency, const string& currentCurrency, double current) {
        if (index == size(list)) {
            if (initialCurrency == currentCurrency) {
                return current;
            }
            return 0.0;
        }

        const auto& [curPairs, rates] = list[index];

        queue<pair<string, double>> qu;
        map<string, double> used_map;
        used_map[currentCurrency] = current;
        qu.push({ currentCurrency, current });
        while (!qu.empty()) {
            const auto [cur_curr, value] = qu.front();
            qu.pop();
            for (int i = 0; i < size(curPairs); i++) {
                const auto& p = curPairs[i];
                if (p.front() == cur_curr) {
                    const auto v = value * rates[i];
                    if (used_map[p.back()] < v) {
                        used_map[p.back()] = v;
                        qu.push({ p.back(), v });
                    }
                }
                if (p.back() == cur_curr) {
                    const auto v = value * (1 / rates[i]);
                    if (used_map[p.front()] < v) {
                        used_map[p.front()] = v;
                        qu.push({p.front(), v});
                    }
                }
            }
        }


        double max_currency = 0;
        for (auto&& [cur, value] : used_map) {
            max_currency = max(max_currency, rec(list, index + 1, initialCurrency, cur, value));
        }
        return max_currency;
    }

    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        MYLIST_T list{
            {pairs1,rates1 },
            {pairs2,rates2 },
        };

        return rec(list, 0, initialCurrency, initialCurrency, 1.0);
    }
};
static void test(string&& initialCurrency, vector<vector<string>>&& pairs1, vector<double>&& rates1, vector<vector<string>>&& pairs2, vector<double>&& rates2) {
    cout << Solution().maxAmount(initialCurrency, pairs1, rates1, pairs2, rates2) << endl;
}
static void run() {
    test("EUR", get_matrix_str(R"([["EUR","USD"],["USD","JPY"]])"), get_list_double("[2.0,3.0]"), get_matrix_str(R"([["JPY","USD"],["USD","CHF"],["CHF","EUR"]])"), get_list_double("[4.0,5.0,6.0]"));
    test("NGN", get_matrix_str(R"([["NGN","EUR"]])"), get_list_double("[9.0]"), get_matrix_str(R"([["NGN","EUR"]])"), get_list_double("[6.0]"));
    test("USD", get_matrix_str(R"([["USD","EUR"]])"), get_list_double("[1.0]"), get_matrix_str(R"([["EUR","JPY"]])"), get_list_double("[10.0]"));
}
}
namespace problem3 {
class Solution {
public:

    static bool check_prefix(const vector<int>& nums, int len, int s1, int s2) {
        for (int i = 0; i < len; i++) {
            if (size(nums) <= (s1 + i) || size(nums) <= (s2 + i)) { return false; }
            if (nums[s1 + i] != nums[s2 + i]) {
                return false;
            }
        }
        return true;
    }

    int sol(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool isValid1 =
                    (j - i >= i) &&
                    equal(nums.begin(), nums.begin() + i, nums.begin() + i);
                bool isValid2 =
                    (n - j >= j - i) &&
                    equal(nums.begin() + i, nums.begin() + j, nums.begin() + j);
                if (isValid1 || isValid2) {
                    cout << i << "," << j << endl;
                    count++;
                }
            }
        }
        return count;
    }


    int beautifulSplits(vector<int>& nums) {
        const auto N = size(nums);
        if (N < 3) {
            return 0;
        }
        vector<vector<int>> dp(N + 1, vector<int>(N + 1));
        for (int len = 1; len <= N; len++) {
            for (int index = N - len - 1; index >= 0; index--) {
                if (nums[index] == nums[index + len]) {
                    dp[len][index] = dp[len][index + 1] + 1;
                }
                else {
                    dp[len][index] = 0;
                }
            }
        }
        int count = 0;

        for (int num1_len = 1; num1_len <= N - 2; num1_len++) {
            if (dp[num1_len][0] >= num1_len) {
                int remain_length = N - 2 * num1_len;
                int cur_patterns = remain_length;
                count += cur_patterns;
                const auto num2_begin = num1_len;
                for (int num2_len = 1; num2_len < num1_len; num2_len++) {
                    if (dp[num2_len][num2_begin] >= num2_len) {
                        count++;
                    }
                }
            }
            else {
                const auto num2_begin = num1_len;
                for (int num2_len = 1; num2_len <= N - num1_len - 1; num2_len++) {
                    if (dp[num2_len][num2_begin] >= num2_len) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
}; 

void test(vector<int>&& nums) {
    cout << Solution().beautifulSplits(nums) << endl;
}
static void run() {
    test(get_list_int("[0,0,0,0,2,2,0,1,2,1,2]"));
    //test(get_list_int("[3,3,3,1,3]"));
    //test(get_list_int("[1,1,2]"));
    //test(get_list_int("[0]"));
    //test(get_list_int("[1,1,2,1]"));
    //test(get_list_int("[2,2,0,0,0,0,0,1,2,2,0,0,0,1,0]"));
    //test(get_list_int("[1,2,3,4]"));
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