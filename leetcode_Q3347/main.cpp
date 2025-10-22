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
        map<long long, long long> freqs;
        for (auto&& num : nums) { freqs[num]++; }
        const auto n = size(freqs);
        map<long long, int> value_index_map{ {0,0} };
        vector<long long> prefix_sums(n + 1);
        int index = 1;
        for (auto&& [num, count] : freqs) {
            prefix_sums[index] += count + prefix_sums[index - 1];
            value_index_map.insert({ num, index });
            index++;
        }

        auto get_range_count = [&](long long value) {
            auto lower_it = value_index_map.lower_bound(value - k);
            int lower_index;
            if (lower_it == cend(value_index_map)) {
                lower_index = n;
            }
            else {
                if (lower_it == cbegin(value_index_map)) {
                    lower_index = 0;
                }
                else {
                    lower_index = lower_it->second - 1;
                }
            }
            auto upper_it = value_index_map.lower_bound(value + k);
            int upper_index;
            if (upper_it == cend(value_index_map)) {
                upper_index = n;
            }
            else {
                if (upper_it->first == value + k) {
                    upper_index = upper_it->second;
                }
                else {
                    upper_index = upper_it->second - 1;
                }
            }
            return prefix_sums[upper_index] - prefix_sums[lower_index];
            };

        int max_freq = 0;
        const vector<long long> offsets{ -k, 0, k };
        for (auto&& [num, _] : freqs) {
            for (auto&& offset : offsets) {
                const auto range_total = get_range_count(num + offset);
                const auto it_eq = freqs.find(num + offset);
                const int eq_count = it_eq == cend(freqs) ? 0 : it_eq->second;
                const int near_count = range_total - eq_count;
                const auto append_value = min(numOperations, near_count);
                max_freq = max(max_freq, eq_count + append_value);
            }
        }
        return max_freq;
    }
};

static void test(vector<int>&& nums, int k, int numOperations) {
    cout << Solution().maxFrequency(nums, k, numOperations) << endl;
}
int main() {
    test(get_list_int("[999999997,999999999,999999999]"), 999999999, 2);
    test(get_list_int("[1,4,5]"), 1, 2);
    test(get_list_int("[5,11,20,20]"), 5, 1);
    return 0;
}