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
    long long countSubarrays(vector<int>& nums, long long k) {
        long long count = 0;

        long long current = 0;
        long long l = 0;
        for (long long r = 0; r < size(nums); r++) {
            current += static_cast<long long>(nums[r]);

            while (l < r && current * (r - l + 1) >= k) {
                current -= static_cast<long long>(nums[l]);
                l++;
            }

            if (current * (r - l + 1) < k) {
                count += (r - l) + 1;
            }
        }
        return count;
    }
};

void test(vector<int>&& nums, long long k) {
    cout << Solution().countSubarrays(nums, k) << endl;
}

int main() {
    test(get_list_int("[2,1,4,3,5]"), 10);
    test(get_list_int("[1,1,1]"), 5);
    return 0;
}