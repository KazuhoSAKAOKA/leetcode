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
    static inline int flip(int v) {
        return v == 0 ? 1 : 0;
    }
    int minOperations(vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < size(nums) - 2; i++) {
            if (nums[i] == 0) {
                nums[i] = 1;
                nums[i + 1] = flip(nums[i + 1]);
                nums[i + 2] = flip(nums[i + 2]);
                count++;
            }
        }
        return nums[size(nums) - 2] == 1 && nums[size(nums) - 1] == 1 ? count : -1;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minOperations(nums) << endl;
}
int main() {
    test(get_list_int("[0,1,1,1,0,0]"));
    test(get_list_int("[0,1,1,1]"));
    return 0;
}