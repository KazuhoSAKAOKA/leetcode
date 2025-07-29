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
    vector<int> smallestSubarrays(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> most_lefts(32, -1);
        vector<int> ans(n);
        ans[n - 1] = 1;
        int current_or = nums.back();
        for (int j = 0; j < 32; j++) {
            if ((nums.back() & (1 << j)) != 0) {
                most_lefts[j] = n - 1;
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            const auto val = nums[i];
            current_or |= val;
            int cur_min = 0;
            for (int j = 0; j < 32; j++) {
                const auto cur_bit = 1 << j;
                if ((val & cur_bit) != 0) {
                    most_lefts[j] = i;
                }
                if ((current_or & cur_bit) != 0) {
                    cur_min = max(cur_min, most_lefts[j] - i + 1);
                }
            }
            ans[i] = max(1, cur_min);
        }
        return ans;
    }
};
static void test(vector<int>&& nums) {
    output(Solution().smallestSubarrays(nums));
}
int main() {
    test(get_list_int("[0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,32,2,0,0,0,0,0,0,28,16,32,0,0,0,0,0,0,0,1,0,8,0,0,0,0,0,0,0,0,0,32,0,0,0,0,0,0,0,0,16,0,0,0,0,2,0,0,32,0,0,0,4,16,0,4,0,32,0,0,8,0,1,1,0,0,0,0,0]"));
    test(get_list_int("[1,0,2,1,3]"));
    test(get_list_int("[1,2]"));
    return 0;
}