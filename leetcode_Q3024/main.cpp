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
    string triangleType(vector<int>& nums) {
        sort(begin(nums), end(nums));
        if (nums[0] + nums[1] <= nums[2]) {
            return "none";
        }
        if (nums[0] == nums[1] && nums[1] == nums[2]) {
            return "equilateral";
        }
        else if(nums[0] == nums[1] || nums[1] == nums[2]){
            return "isosceles";
        }
        return "scalene";
    }
};

void test(vector<int>&& nums) {
    cout << Solution().triangleType(nums) << endl;
}

int main() {
	return 0;
}