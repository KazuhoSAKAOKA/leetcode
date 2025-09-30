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
    int triangularSum(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> before(nums);
        vector<int> current(n);
        for (int i = n - 1; i >= 1; i--) {
            for (int j = 0; j < i; j++) {
                current[j] = (before[j] + before[j + 1]) % 10;
            }
            swap(current, before);
        }
        return before[0];
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().triangularSum(nums) << endl;
}
int main() {
	return 0;
}