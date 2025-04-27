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
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        const auto n = size(nums);
        long long count = 0;
        long long mink_count = 0;
        long long maxk_count = 0;
        long long right_most_out = -1;
        long long l = 0;

        for (long long r = 0; r < n; r++) {
            if (nums[r] < minK || maxK < nums[r]) {
                right_most_out = r;
            }
            else {
                if (nums[r] == minK) {
                    mink_count++;
                }
                if (nums[r] == maxK) {
                    maxk_count++;
                }
            }

            while (l < r && (mink_count >= 1 && maxk_count >=1)) {
                if (mink_count == 1 && nums[l] == minK) {
                    break;
                }
                if (maxk_count == 1 && nums[l] == maxK) {
                    break;
                }
                if (nums[l] == minK) {
                    mink_count--;
                }
                if (nums[l] == maxK) {
                    maxk_count--;
                }
                l++;
            }


            if (right_most_out < l && (mink_count >= 1 && maxk_count >= 1)) {
                count += l - right_most_out;
            }
        }
        return count;
    }
};
void test(vector<int>&& nums, int minK, int maxK) {
    cout << Solution().countSubarrays(nums, minK, maxK) << endl;
}
int main() {
    test(get_list_int("[4,3]"), 3, 3);
    test(get_list_int("[1,3,5,2,7,5]"), 1, 5);
    test(get_list_int("[1,1,1,1]"), 1, 1);
	return 0;
}