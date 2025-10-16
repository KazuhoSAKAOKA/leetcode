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
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> mod_freqs(value);
        for (auto&& num : nums) {
            if (num >= 0) {
                mod_freqs[num % value]++;
            }
            else {
                const auto m = -num / value + 1;
                mod_freqs[(num + m * value) % value]++;
            }
        }

        int min_count = INT_MAX;
        int cur_ans = 0;
        
        for (int i = 0; i < value; i++) {
            if (mod_freqs[i] < min_count) {
                min_count = mod_freqs[i];
                cur_ans = min_count * value + i;
            }
        }

        return cur_ans;
    }
};

static void test(vector<int>&& nums, int value) {
    cout << Solution().findSmallestInteger(nums, value) << endl;
}
int main() {
    test(get_list_int("[1,-10,7,13,6,8]"), 5);
    test(get_list_int("[1,-10,7,13,6,8]"), 7);
    return 0;
}