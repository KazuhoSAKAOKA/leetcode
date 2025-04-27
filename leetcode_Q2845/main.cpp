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
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        const auto n = size(nums);
        vector<int> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + (((nums[i] % modulo) == k) ? 1 : 0);
        }
        unordered_map<int, long long> mp;
        long long count = 0;
        for (int i = 0; i <= n; i++) {
            count += mp[(prefix_sums[i] + modulo - k) % modulo];
            mp[prefix_sums[i] % modulo]++;
        }
        return count;
    }
};

void test(vector<int>&& nums, int modulo, int k) {
    cout << Solution().countInterestingSubarrays(nums, modulo, k) << endl;
}

int main() {
    test(get_list_int("[3,2,4]"),2 ,1 );
    test(get_list_int("[3,1,9,6]"), 3, 0);
    return 0;
}