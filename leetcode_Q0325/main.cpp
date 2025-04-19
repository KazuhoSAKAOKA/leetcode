#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        const auto n = size(nums);
        vector<long long> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }
        int max_len = 0;
        unordered_map<long long, int> exist_map{ {0,0} };
        for (int i = 0; i < n; i++) {
            const auto remain = prefix_sums[i + 1] - static_cast<long long>(k);
            const auto it = exist_map.find(remain);
            if (it != cend(exist_map)) {
                max_len = max(max_len, i - it->second + 1);
            }
            exist_map.insert({ prefix_sums[i + 1] , i + 1 });
        }
        return max_len;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maxSubArrayLen(nums, k) << endl;
}

int main() {
    test(get_list_int("[1,-1,5,-2,3]"), 3);
    test(get_list_int("[-2,-1,2,1]"), 1);
    return 0;
}