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
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        const auto n = size(startTime);
        auto get_left_space = [&](int index)-> int {
            if (index <= 0) {
                return startTime[0];
            }
            return startTime[index] - endTime[index - 1];
            };
        auto get_right_space = [&](int index)-> int {
            if (index >= n - 1) {
                return eventTime - endTime[index];
            }
            return startTime[index + 1] - endTime[index];
            };

        int inner_space = 0;
        for (int i = 0; i < k - 1; i++) {
            inner_space += get_right_space(i);
        }
        int max_free_len = 0;
        for (int i = 0; i + k - 1 < n; i++) {
            const auto left_space = get_left_space(i);
            const auto right_space = get_right_space(i + k - 1);
            max_free_len = max(max_free_len, left_space + inner_space + right_space);
            inner_space -= get_right_space(i);
            inner_space += right_space;
        }
        return max_free_len;
    }
};

static void test(int eventTime, int k, vector<int>&& startTime, vector<int>&& endTime) {
    cout << Solution().maxFreeTime(eventTime, k, startTime, endTime) << endl;
}
int main() {
    test(5, 1, get_list_int("[1,3]"), get_list_int("[2,5]"));
    test(10, 1, get_list_int("[0,2,9]"), get_list_int("[1,4,10]"));
    test(5, 2, get_list_int("[0,1,2,3,4]"), get_list_int("[1,2,3,4,5]"));
    return 0;
}