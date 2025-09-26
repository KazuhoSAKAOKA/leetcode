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
    int triangleNumber(vector<int>& nums) {
        sort(begin(nums), end(nums));

        size_t count = 0;

        for (auto it1 = cbegin(nums); it1 != cend(nums); ++it1) {
            const long long num1 = *it1;
            for (auto it2 = next(it1); it2 != cend(nums); ++it2) {
                const long long num2 = *it2;

                auto it_over = lower_bound(next(it2), cend(nums), num1 + num2);
                auto it3 = prev(it_over);
                const auto cur_count = distance(it2, it3);
                count += cur_count;
            }
        }


        return static_cast<int>(count);
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().triangleNumber(nums) << endl;
}

int main() {
    test(get_list_int("[2,2,3,4]"));
    test(get_list_int("[4,2,3,4]"));
    return 0;
}