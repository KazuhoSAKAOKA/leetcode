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


    int minRemoval(vector<int>& nums, int k) {
        const int n = size(nums);
        sort(begin(nums), end(nums));
        int min_count = n;
        auto itleft = cbegin(nums);
        while (itleft != cend(nums)) {
            const auto cur_min_value = *itleft;
            const auto itright = upper_bound(cbegin(nums), cend(nums), static_cast<long long>(cur_min_value) * k);

            const auto left_count = distance(cbegin(nums), itleft);
            const auto right_count = distance(itright, cend(nums));
            min_count = min(min_count, static_cast<int>(left_count + right_count));
            itleft = upper_bound(cbegin(nums), cend(nums), cur_min_value);
        }
        return min_count;
    }
};

static void test(vector<int>&& nums, int k) {
    cout << Solution().minRemoval(nums, k) << endl;
}
int main() {
    test(get_list_int("[26155,1776,22815,775,27772,12869,12995,22794,27692,24728,10944,25039,24068,25506,18506,19138,12331,17814,20834,21474,20208,21590,15453,6114,25716,29434,23547,29051,25992,5535,7387]"), 80020);
    test(get_list_int("[16,18]"), 1);
    test(get_list_int("[2,1,5]"), 2);
    test(get_list_int("[1,6,2,9]"), 3);
    test(get_list_int("[4,6]"), 2);
    return 0;
}