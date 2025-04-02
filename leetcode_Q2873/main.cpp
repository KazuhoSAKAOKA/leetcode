#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        map<int, int, greater<int>> freq_map;
        for (auto i = 1; i < size(nums); i++) {
            const auto& num = nums[i];
            freq_map[num]++;
        }
        long long max_value = 0;
        int past_max = nums[0];
        for (auto i = 1; i < size(nums) - 1; i++) {
            auto it = freq_map.find(nums[i]);
            it->second--;
            if (it->second == 0) {
                freq_map.erase(it);
            }
            const auto cur_diff = past_max - nums[i];
            if (cur_diff > 0) {
                auto future_max = cbegin(freq_map)->first;
                max_value = max(max_value, static_cast<long long>(cur_diff) * static_cast<long long>(future_max));
            }
            past_max = max(past_max, nums[i]);
        }
        return max_value;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maximumTripletValue(nums) << endl;
}

int main() {
    test(get_list_int("[1,10,3,4,19]"));
	return 0;
}