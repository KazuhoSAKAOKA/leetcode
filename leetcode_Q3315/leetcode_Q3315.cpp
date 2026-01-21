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
    vector<int> minBitwiseArray(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> ans;
        ans.reserve(n);
        auto get_ans = [](int num)-> int {
            int ones_len = 0;
            while ((num & (1 << ones_len)) != 0) {
                ones_len++;
            }
            if (ones_len == 0) {
                return -1;
            }
            if (ones_len == 1) {
                return num & (~1);
            }
            const auto v1 = ((1 << (ones_len - 1)) - 1);
            const auto v2 = (num & (~((1 << (ones_len)) - 1)));
            return v1 | v2;
            };
        for (auto&& num : nums) {
            ans.push_back(get_ans(num));
        }
        return ans;
    }
};

static void test(vector<int>&& nums) {
    output(Solution().minBitwiseArray(nums));
}

int main()
{
    test(get_list_int("[2,3,5,7]"));
    test(get_list_int("[11,13,31]"));
    return 0;
}