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
    int maximumUniqueSubarray(vector<int>& nums) {
        long long max_total = 0;
        unordered_map<int, int> exists;
        int l = 0;
        long long cur_total = 0;
        for (int r = 0; r < size(nums); r++) {
            cur_total += nums[r];
            exists[nums[r]]++;

            while (l < r && size(exists) < (r - l + 1)) {
                cur_total -= nums[l];
                exists[nums[l]]--;
                if (exists[nums[l]] == 0) {
                    exists.erase(nums[l]);
                }
                l++;
            }
            if (size(exists) == (r - l + 1)) {
                max_total = max(max_total, cur_total);
            }
        }

        return static_cast<int>(max_total);
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maximumUniqueSubarray(nums) << endl;
}
int main() {
    test(get_list_int("[4,2,4,5,6]"));
    test(get_list_int("[5,2,1,2,5,2,1,2,5]"));
    return 0;
}