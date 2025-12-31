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
    vector<int> get_digits(int n) {
        if (n == 0) {
            return { 0 };
        }
        vector<int> digits;
        int current(n);
        while (current > 0) {
            digits.emplace_back(current % 10);
            current /= 10;
        }
        return vector<int>(crbegin(digits), crend(digits));
    }
    vector<int> decimalRepresentation(int n) {
        vector<int> digits = get_digits(n);
        long long base = 1;
        vector<int> ans;
        for (int i = 0; i < size(digits); i++) {
            if (digits[size(digits) - i - 1] != 0) {
                ans.emplace_back(digits[size(digits) - i - 1] * base);
            }
            base *= 10;
        }
        reverse(begin(ans), end(ans));
        return ans;
    }
};
static void test(int n) {
    output(Solution().decimalRepresentation(n));
}
static void run() {
    test(537);
    test(102);
    test(6);
}
}
namespace problem2 {

class Solution {
public:
    //static long long bt(const vector<int>& nums, int index, long long left_sum, long long right_sum, int left_val, int right_val) {
    //    if (size(nums) == index) {
    //        if (left_val == INT_MIN || right_val == INT_MAX) {
    //            return INT_MAX;
    //        }
    //        return abs(left_sum - right_sum);
    //    }
    //    long long min_value = LLONG_MAX;
    //    if (left_val < nums[index]) {
    //        min_value = min(min_value, bt(nums, index + 1, left_sum + nums[index], right_sum, nums[index], right_val));
    //    }

    //    if (right_val > nums[index]) {
    //        min_value = min(min_value, bt(nums, index + 1, left_sum , right_sum + nums[index], left_val, nums[index]));
    //    }
    //    return min_value;
    //}


    long long splitArray(vector<int>& nums) {
        const int n = size(nums);
        vector<long long> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }
        auto get_increase_len = [&]()->int {
            for (int i = 1; i < n; i++) {
                if (nums[i - 1] >= nums[i]) {
                    return i;
                }
            }
            return n;
            };
        const int increaselen = get_increase_len();
        auto get_decrease_len = [&]()->int {
            for (int i = 1; i < n; i++) {
                if (nums[n - i - 1 + 1] >= nums[n - i - 1]) {
                    return i;
                }
            }
            return n;
            };
        const int decreaselen = get_decrease_len();
        if (increaselen + decreaselen < n) {
            return -1;
        }
        long long min_diff = LLONG_MAX;
        const auto b = max(1, n - decreaselen);
        const auto e = min(n - 1, increaselen);
        for (int i = b; i <= e; i++) {
            const auto leftsum = prefix_sums[i] - prefix_sums[0];
            const auto rightsum = prefix_sums[n] - prefix_sums[i];
            const auto diff = abs(leftsum - rightsum);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        if (min_diff == LLONG_MAX) { return -1; }
        return min_diff;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().splitArray(nums) << endl;
}
static void run() {
    test(get_list_int("[10,11,5,3]"));
    test(get_list_int("[1,3,2]"));
    test(get_list_int("[1,2,4,3]"));
    test(get_list_int("[3,1,2]"));
}
}
namespace problem3 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const long long digit_ranges = r - l + 1;

        vector<vector<long long>> dp(n, vector<long long>(digit_ranges));
        for (int j = 0; j < digit_ranges - 1; j++) {
            dp[0][j] = 1LL;
        }

        for (int i = 1; i < n; i++) {
            if (i % 2 == 1) {
                long long cur_total = 0LL;
                for (int j = 0; j < digit_ranges - 1; j++) {
                    cur_total += dp[i - 1][j];
                    cur_total %= MODULO;
                    dp[i][j + 1] = cur_total;
                }
            }
            else {
                long long cur_total = 0LL;
                for (int j = digit_ranges - 1; j > 0; j--) {
                    cur_total += dp[i - 1][j];
                    cur_total %= MODULO;
                    dp[i][j - 1] = cur_total;
                }
            }
        }
        long long total = 0LL;
        for (auto&& v : dp.back()) {
            total += v;
            total %= MODULO;
        }
        total *= 2;
        total %= MODULO;
        return static_cast<int>(total);
    }
};
static void test(int n, int l, int r) {
    cout << Solution().zigZagArrays(n, l, r) << endl;
}
static void run() {
    test(3, 4, 5);
    test(3, 1, 3);
}
}
namespace problem4 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const long long digit_ranges = r - l + 1;
        vector<long long> befores(digit_ranges, 1LL);
        vector<long long> nexts(digit_ranges);

        for (int i = 1; i < n; i++) {
            fill(begin(nexts), end(nexts), 0LL);
            if (i % 2 == 1) {
                long long cur_total = 0LL;
                for (int j = 0; j < digit_ranges - 1; j++) {
                    cur_total += befores[j];
                    cur_total %= MODULO;
                    nexts[j + 1] = cur_total;
                }
            }
            else {
                long long cur_total = 0LL;
                for (int j = digit_ranges - 1; j > 0; j--) {
                    cur_total += befores[j];
                    cur_total %= MODULO;
                    nexts[j - 1] = cur_total;
                }
            }
            swap(nexts, befores);
        }
        long long total = 0LL;
        for (auto&& v : befores) {
            total += v;
            total %= MODULO;
        }
        total *= 2;
        total %= MODULO;
        return static_cast<int>(total);
    }
};
static void test(int n, int l, int r) {
    cout << Solution().zigZagArrays(n, l, r) << endl;
}
static void run() {
    test(3, 4, 5);
    test(3, 1, 3);
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