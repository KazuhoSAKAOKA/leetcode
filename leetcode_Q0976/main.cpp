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
    int largestPerimeter(vector<int>& nums) {
        sort(begin(nums), end(nums), greater<int>());
        for (int i = 0; i < size(nums) - 2; i++) {
            auto len1 = nums[i];
            auto len2 = nums[i + 1];
            auto len3 = nums[i + 2];
            if (len1 < len2 + len3) {
                return len1 + len2 + len3;
            }
        }
        return 0;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().largestPerimeter(nums) << endl;
}
int main() {
    test(get_list_int("[1,2,1,10]"));
    test(get_list_int("[2,1,2]"));
    return 0;
}