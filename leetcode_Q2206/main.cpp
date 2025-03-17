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
    bool wa(vector<int>& nums) {
        int cur = 0;
        for (auto&& num : nums) {
            cur ^= num;
        }
        return cur == 0;
    }

    bool divideArray(vector<int>& nums) {
        vector<bool> exists(500);
        for (auto&& num : nums) {
            exists[num - 1] = !exists[num - 1];
        }
        return !any_of(cbegin(exists), cend(exists), [](bool b) {return b; });
    }
};
void test(vector<int>&& nums) {
    cout << Solution().divideArray(nums) << endl;
}
int main() {
    test(get_list_int("[1,2,3,4]"));

    test(get_list_int("[9,9,19,10,9,12,2,12,3,3,11,5,8,4,13,6,2,11,9,19,11,15,9,17,15,12,5,14,12,16,18,16,10,3,8,9,16,20,2,4,16,12,11,14,20,16,2,18,17,20,3,13,16,17,1,1,11,20,20,4]"));
	return 0;
}