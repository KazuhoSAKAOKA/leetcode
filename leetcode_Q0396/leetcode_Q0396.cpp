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
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        const auto n = size(nums);
        vector<long long> prefix_sums(n + 1);
        int cur_sum = 0;
        for (size_t i = 0; i < n; i++) {
            cur_sum += nums[i] * i;
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }
        int max_val = cur_sum;

        for (size_t i = 1; i < n; i++) {
            cur_sum -= static_cast<int>(prefix_sums[n] - prefix_sums[i]);
            cur_sum -= static_cast<int>(prefix_sums[i - 1] - prefix_sums[0]);
            cur_sum += static_cast<int>(n - 1) * nums[i - 1];
            max_val = max(max_val, cur_sum);
        }
        return max_val;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maxRotateFunction(nums) << endl;
}

int main() {
    test(get_list_int("[4,3,2,6]"));
    test(get_list_int("[100]"));
    return 0;
}
