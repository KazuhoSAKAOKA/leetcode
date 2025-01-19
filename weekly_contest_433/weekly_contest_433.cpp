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
    int subarraySum(vector<int>& nums) {
        vector<int> prefix_sums(size(nums) + 1);
        for (int i = 0; i < size(nums); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }

        int total = 0;

        for (int i = 0; i < size(nums); i++) {
            const auto cur_sum = prefix_sums[i + 1] - prefix_sums[max(0, i - nums[i])];
            total += cur_sum;
        }
        return total;
    }
}; 

static void test(vector<int>&& nums) {
    cout << Solution().subarraySum(nums) << endl;
}
static void run() {
    test(get_list_int("[2,3,1]"));
    test(get_list_int("[3,1,1,2]"));
}
}
namespace problem2 {
constexpr size_t MODULO = 1e9 + 7;
class Solution {
public:

    static size_t factorial(int n, map<int, size_t>& memo) {
        if (n == 0) {
            return 1LL;
        }
        auto it = memo.find(n);
        if (it != cend(memo)) {
            return it->second;
        }
        auto v = static_cast<size_t>(n) * factorial(n - 1, memo);
        memo[n] = v;
        return v;
    }

    static size_t combination(int n, int k, map<int, size_t>& memo) {
        if (k > n) { return 0ULL; }
        return factorial(n, memo) / (factorial(k, memo) * factorial(n - k, memo));
    }

    static size_t get_conv_counts(int n, int k, map<int, size_t>& memo) {
        if (n <= 0) { return 0; }
        size_t count = 0;
        for (int i = 1; i <= k; i++) {
            count += combination(n, i, memo);
            count %= MODULO;
        }
        return count;
    }

    int minMaxSums(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        const size_t N = size(nums);
        size_t total = 0;
        map<int, size_t> memo;
        for (size_t i = 0; i < N; i++) {
            size_t min_values = 1ULL +  get_conv_counts(N - i - 1, k - 1, memo);
            min_values %= MODULO;
            size_t min_value_multiples = (static_cast<size_t>(nums[i]) * min_values);
            min_value_multiples %= MODULO;
            total += min_value_multiples;
            total %= MODULO;

            size_t max_values = 1ULL + get_conv_counts(i, k - 1, memo);
            max_values %= MODULO;
            size_t max_value_multiples = (static_cast<size_t>(nums[i]) * max_values);
            max_value_multiples %= MODULO;
            total += max_value_multiples;
            total %= MODULO;
        }

        total %= MODULO;
        return static_cast<int>(total);
    }
}; 
static void test(vector<int>&& nums, int k) {
    cout << Solution().minMaxSums(nums, k) << endl;
}
static void run() {
    test(get_list_int("[10,5,9,9,10,10,7,7,9,6,9,6,7,6,4,9,8,4,2,0,0,3,9,3,10,3,1,9,8,2,8,2,0,7,7,6,4,6,7,3,2,5,6,6,5,0,5,7,8,1]"), 29);
    test(get_list_int("[4,1,3]"), 3);
    test(get_list_int("[1,2,3]"), 2);
    test(get_list_int("[5,0,6]"), 1);
    test(get_list_int("[1,1,1]"), 2);
}
}
namespace problem3 {
static void run() {
}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    //problem1::run();
    problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}