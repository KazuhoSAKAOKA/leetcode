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
    int maximizeExpressionOfThree(vector<int>& nums) {
        const auto n = size(nums);
        sort(begin(nums), end(nums));
        return nums[n - 1] + nums[n - 2] - nums[0];
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maximizeExpressionOfThree(nums) << endl;
}
static void run() {
    test(get_list_int("[1,4,2,5]"));
    test(get_list_int("[-2,0,5,-2,4]"));
}
}
namespace problem2 {
class Solution {
public:
    int minLengthAfterRemovals(string s) {
        long long a_count = 0LL;
        long long b_count = 0LL;
        for (auto&& c : s) {
            if (c == 'a') {
                a_count++;
            }
            else {
                b_count++;
            }
        }
        const auto rm_count = min(a_count, b_count);
        return (a_count + b_count) - 2 * rm_count;
    }
};
static void test(string&& s) {
    cout << Solution().minLengthAfterRemovals(s) << endl;
}
static void run() {
    test("aabbab");
    test("aaaa");
    test("aaabb");
}
}
namespace problem3 {
class Solution {
public:
    static vector<long long> get_digits(long long n) {
        if (n == 0) { return{ 0 }; }
        long long cur(n);
        vector<long long> digits;
        while (cur > 0) {
            digits.emplace_back(cur % 10);
            cur /= 10;
        }
        reverse(begin(digits), end(digits));
        return digits;
    }

    long long countDistinct(long long n) {
        const auto digits = get_digits(n);
        const auto cols = size(digits);
        vector<vector<long long>> dp(cols, vector<long long>(2));
        dp[0][0] = digits[0] - 1;
        dp[0][1] = 1;

        for (long long i = 1; i < cols; i++) {
            dp[i][0] += 9LL;
            dp[i][0] += dp[i - 1][0] * 9LL;
            if (digits[i] != 0) {
                dp[i][0] += dp[i - 1][1] * (digits[i] - 1);
                dp[i][1] = dp[i - 1][1];
            }
        }
        return dp.back()[0] + dp.back()[1];
    }
};
static void test(long long n) {
    cout << Solution().countDistinct(n) << endl;
}
static void run() {
    test(25);
    test(10);
    test(3);
}
}
namespace problem4 {
class Solution {
public:

    static long long sliding_window(const vector<int>& nums, size_t first, size_t last) {
        long long count = 0LL;
        long long l = first;
        for (long long r = first; r <= last; r++) {
            if (l < r) {
                if (nums[r - 1] > nums[r]) {
                    l = r;
                }
            }
            count += r - l + 1;
        }
        return count;
    }

    static vector<long long> tle(const vector<int>& nums, const vector<vector<int>>& queries) {
        const auto q = size(queries);
        vector<long long> ans;
        ans.reserve(q);
        for (auto&& query : queries) {
            ans.emplace_back(sliding_window(nums, query[0], query[1]));
        }
        return ans;
    }

    inline static long long get_count(long long len) {
        return len * (len + 1) / 2LL;
    }
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        const long long n = size(nums);
        vector<long long> segment_begin_indexes{ 0 };
        vector<long long> segment_lengths;
        for (long long i = 1; i < n; i++) {
            if (nums[i - 1] > nums[i]) {
                segment_lengths.emplace_back(i - segment_begin_indexes.back());
                segment_begin_indexes.emplace_back(i);
            }
        }
        segment_lengths.emplace_back(n - segment_begin_indexes.back());
        const long long m = size(segment_lengths);
        vector<long long> segment_len_prefix_sums(m + 1);
        for (long long i = 0; i < m; i++) {
            segment_len_prefix_sums[i + 1] = segment_len_prefix_sums[i] + get_count(segment_lengths[i]);
        }

        const auto q = size(queries);
        vector<long long> ans;
        ans.reserve(q);
        for (auto&& query : queries) {
            const long long l = query[0];
            const long long r = query[1];
            const long long seg_index_left = distance(cbegin(segment_begin_indexes), prev(upper_bound(cbegin(segment_begin_indexes), cend(segment_begin_indexes), l)));
            const long long seg_index_right = distance(cbegin(segment_begin_indexes), prev(upper_bound(cbegin(segment_begin_indexes), cend(segment_begin_indexes), r)));
            long long total = 0LL;
            if (seg_index_left == seg_index_right) {
                const auto len = r - l + 1;
                total = get_count(len);
            }
            else{
                const auto left_len = segment_begin_indexes[seg_index_left + 1] - l;
                total += get_count(left_len);
                const auto right_len = r - segment_begin_indexes[seg_index_right] + 1;
                total += get_count(right_len);
                if (seg_index_right - seg_index_left > 1) {
                    const auto mid = segment_len_prefix_sums[seg_index_right] - segment_len_prefix_sums[seg_index_left + 1];
                    total += mid;
                }
            }
            ans.emplace_back(total);
        }
        return ans;
    }
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    output(Solution().countStableSubarrays(nums, queries));
}
static void run() {
    test(get_list_int("[13,9,15,9]"), get_matrix_int("[[2,3],[0,3]]"));
    test(get_list_int("[3,1,2]"), get_matrix_int("[[0,1],[1,2],[0,2]]"));
    test(get_list_int("[2,2]"), get_matrix_int("[[0,1],[0,0]]"));
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