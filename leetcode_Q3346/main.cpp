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
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> freqs;
        int max_value = 0;
        int min_value = INT_MAX;
        for (auto&& num : nums) {
            freqs[num]++;
            max_value = max(max_value, num);
            min_value = min(min_value, num);
        }
        vector<long long> prefix_sums(max_value + 1);
        for (int i = 1; i <= max_value; i++) {
            auto it = freqs.find(i);
            if (it != cend(freqs)) {
                prefix_sums[i] = it->second;
            }
            prefix_sums[i] += prefix_sums[i - 1];
        }
        int max_freq = 0;

        for (int i = min_value; i <= max_value; i++) {
            const auto range_total = prefix_sums[min(max_value, i + k)] - prefix_sums[max(0, i - k - 1)];
            const int range_eq = prefix_sums[i] - prefix_sums[i - 1];
            const int near_count = range_total - range_eq;
            const auto append_value = min(numOperations, near_count);
            max_freq = max(max_freq, range_eq + append_value);
        }
        return max_freq;
    }
};

static void test(vector<int>&& nums, int k, int numOperations) {
    cout << Solution().maxFrequency(nums, k, numOperations) << endl;
}
int main() {
    test(get_list_int("[88,53]"), 27, 2);
    test(get_list_int("[1,4,5]"), 1, 2);
    test(get_list_int("[5,11,20,20]"), 5, 1);
    return 0;
}