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
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        const auto n = size(startTime);
        int max_free_time = 0;
        auto get_left = [&](int index)-> int {
            if (index < 0) { return 0; }
            if (n <= index) { return eventTime; }
            return startTime[index];
            };
        auto get_right = [&](int index)-> int {
            if (index < 0) { return 0; }
            if (n <= index) { return eventTime; }
            return endTime[index];
            };

        int max_left_space = 0;
        for (int i = 0; i < n; i++) {
            const auto cur_len = endTime[i] - startTime[i];
            const auto left_space = get_left(i) - get_right(i - 1);
            const auto right_space = get_left(i + 1) - get_right(i);
            if (cur_len <= max_left_space) {
                max_free_time = max(max_free_time, left_space + right_space + cur_len);
            }
            else {
                max_free_time = max(max_free_time, left_space + right_space);
            }
            max_left_space = max(max_left_space, left_space);
        }

        int max_right_space = 0;
        for (int i = n - 1; i >= 0; i--) {
            const auto cur_len = endTime[i] - startTime[i];
            const auto left_space = get_left(i) - get_right(i - 1);
            const auto right_space = get_left(i + 1) - get_right(i);
            if (cur_len <= max_right_space) {
                max_free_time = max(max_free_time, left_space + right_space + cur_len);
            }
            else {
                max_free_time = max(max_free_time, left_space + right_space);
            }
            max_right_space = max(max_right_space, right_space);
        }
        return max_free_time;
    }
};

static void test(int eventTime, vector<int>&& startTime, vector<int>&& endTime) {
    cout << Solution().maxFreeTime(eventTime, startTime, endTime) << endl;
}

int main() {
    test(5, get_list_int("[1,3]"), get_list_int("[2,5]"));
    test(10, get_list_int("[0,7,9]"), get_list_int("[1,8,10]"));
    test(10, get_list_int("[0,3,7,9]"), get_list_int("[1,4,8,10]"));
    test(5, get_list_int("[0,1,2,3,4]"), get_list_int("[1,2,3,4,5]"));
    return 0;
}