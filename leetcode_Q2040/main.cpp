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

    static long long tle(const vector<int>& nums1, const vector<int>& nums2, long long k) {
        const auto n = size(nums1);
        const auto m = size(nums2);
        vector<long long> vals;
        vals.reserve(n * m);
        for (auto&& a : nums1) {
            for (auto&& b : nums2) {
                vals.emplace_back(static_cast<long long>(a) * static_cast<long long>(b));
            }
        }
        sort(begin(vals), end(vals));
        return vals[k - 1];
    }


    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        const auto it_zero_lower1 = lower_bound(cbegin(nums1), cend(nums1), 0);
        const auto it_zero_upper1 = upper_bound(cbegin(nums1), cend(nums1), 0);
        const auto it_zero_lower2 = lower_bound(cbegin(nums2), cend(nums2), 0);
        const auto it_zero_upper2 = upper_bound(cbegin(nums2), cend(nums2), 0);
        const long long num1_plus_count = distance(it_zero_upper1, cend(nums1));
        const long long num1_zero_count = distance(it_zero_lower1, it_zero_upper1);
        const long long num1_minus_count = distance(cbegin(nums1), it_zero_lower1);
        const long long num2_plus_count = distance(it_zero_upper2, cend(nums2));
        const long long num2_zero_count = distance(it_zero_lower2, it_zero_upper2);
        const long long num2_minus_count = distance(cbegin(nums2), it_zero_lower2);

        const auto minus_count = num2_plus_count * num1_minus_count + num1_plus_count * num2_minus_count;
        const auto zero_count = num1_zero_count * size(nums2) + num2_zero_count * (size(nums1) - num1_zero_count);
        if (k <= minus_count) {
            return -1;
        }
        else if (k <= (minus_count + zero_count)) {
            return 0;
        }
        else {
            return 1;
        }
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2, long long k) {
    cout << Solution().kthSmallestProduct(nums1, nums2, k) << endl;
}

int main() {
    test(get_list_int("[2,5]"), get_list_int("[3,4]"), 2);
    test(get_list_int("[-4,-2,0,3]"), get_list_int("[2,4]"), 6);
    test(get_list_int("[-2,-1,0,1,2]"), get_list_int("[-3,-1,2,4,5]"), 3);
    return 0;
}