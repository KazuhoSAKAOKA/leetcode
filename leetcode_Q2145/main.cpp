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
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        const auto n = size(differences);
        long long min_value = 0;
        long long max_value = 0;

        long long cur_value = 0;
        for (auto&& difference : differences) {
            cur_value += difference;
            min_value = min(min_value, cur_value);
            max_value = max(max_value, cur_value);
        }
        const auto diff = upper - lower;
        const auto diff1 = max_value - min_value;
        if (diff < diff1) {
            return 0;
        }
        return diff - diff1 + 1;
    }
};

void test(vector<int>&& differences, int lower, int upper) {
    cout << Solution().numberOfArrays(differences, lower, upper) << endl;
}
int main() {
    test(get_list_int("[1,-3,4]"), 1, 6);
    test(get_list_int("[3,-4,5,1,-2]"), -4, 5);
    test(get_list_int("[4,-7,2]"), 3, 6);
	return 0;
}