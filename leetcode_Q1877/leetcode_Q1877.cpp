#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <climits>
#include <cassert>
#include <tuple>
#include <chrono>
#include <optional>
#include <queue>
#include <memory>
#include <random>
#include <exception>
#include <functional>
#include <ranges>
#include <iomanip>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        const auto n = size(nums);
        sort(begin(nums), end(nums));
        int max_sum = INT_MIN;
        for (int i = 0; i < n / 2; i++) {
            max_sum = max(max_sum, nums[i] + nums[n - 1 - i]);
        }
        return max_sum;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().minPairSum(nums) << endl;
}
int main()
{
    return 0;
}