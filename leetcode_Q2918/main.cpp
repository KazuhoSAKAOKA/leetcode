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

    static pair<long long, long long> sum_and_count_zero(const vector<int>& nums) {
        long long total = 0;
        int count = 0;
        
        for (auto&& num : nums) {
            total += static_cast<long long>(num);
            if (num == 0) {
                count++;
            }
        }
        if (count > 0) {
            return { total + count, LLONG_MAX };
        }
        return { total, total };
    }

    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        const auto [lowbound1, upperbound1] = sum_and_count_zero(nums1);
        const auto [lowbound2, upperbound2] = sum_and_count_zero(nums2);
        if (lowbound1 < lowbound2) {
            if (upperbound1 < lowbound2) {
                return -1;
            }
            return lowbound2;
        }
        else {
            if (upperbound2 < lowbound1) {
                return -1;
            }
            return lowbound1;
        }
    }
};


int main() {
	return 0;
}