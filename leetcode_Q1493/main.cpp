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
    int longestSubarray(vector<int>& nums) {
        const auto n = size(nums);
        int longest = 0;
        int current_zero = 0;
        int l = 0;
        for (int r = 0; r < n; r++) {
            if (nums[r] == 0) {
                current_zero++;
            }
            while (l < r && current_zero > 1) {
                if (nums[l] == 0) {
                    current_zero--;
                }
                l++;
            }

            longest = max(longest, r - l + 1 - current_zero);
        }
        if (longest == n) {
            return n - 1;
        }
        return longest;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().longestSubarray(nums) << endl;
}
int main() {
    test(get_list_int("[1,1,0,1]"));
    test(get_list_int("[0,1,1,1,0,1,1,0,1]"));
    test(get_list_int("[1,1,1]"));
    return 0;
}