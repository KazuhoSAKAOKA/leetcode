#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        const auto N = size(nums);
        const auto n = N / 3;
        map<int, int, greater<int>> left_map;
        long long left_total = 0;
        for (int i = 0; i < n; i++) {
            left_total += nums[i];
            left_map[nums[i]]++;
        }

        map<int, int, greater<int>> middle_map;
        long long right_total = 0;
        for (int i = n; i < 2 * n; i++) {
            right_total += nums[i];
            middle_map[nums[i]]++;
        }
        long long middle_total = right_total;
        for (int i = 2 * n; i < 3 * n; i++) {
            const auto val = nums[i];
            auto it = begin(middle_map);
            if (val < it->first) {
                middle_total += val;
                middle_total -= it->first;
                if (it->second == 1) {
                    middle_map.erase(it);
                }
                else {
                    it->second--;
                }
                middle_map[val]++;
            }
            right_total += val;
        }
        long long min_diff = left_total - (right_total - middle_total);

        for (int i = n; i < 2 * n; i++) {
            const auto val = nums[i];
            auto it_left = begin(left_map);
            if (val < it_left->first) {
                left_total += val;
                left_total -= it_left->first;
                if (it_left->second == 1) {
                    left_map.erase(it_left);
                }
                else {
                    it_left->second--;
                }
                left_map[val]++;
            }

            auto it_right = begin(middle_map);
            if (val < it_right->first) {
                middle_total -= val;
                auto it2 = middle_map.find(val);
                if (it2->second == 1) {
                    middle_map.erase(it2);
                }
                else {
                    it2->second--;
                }
            }
            else {
                middle_total -= it_right->first;
                if (it_right->second == 1) {
                    middle_map.erase(it_right);
                }
                else {
                    it_right->second--;
                }
            }
            right_total -= val;
            min_diff = min(min_diff, left_total - (right_total - middle_total));
        }

        return min_diff;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minimumDifference(nums) << endl;
}
int main() {
    test(get_list_int("[21,23,6,9,42,43,47,15,42,22,46,43,11,46,20,6,50,45,31,43,16,39,1,47]"));
    test(get_list_int("[3,1,2]"));
    test(get_list_int("[7,9,5,8,1,3]"));
    return 0;
}