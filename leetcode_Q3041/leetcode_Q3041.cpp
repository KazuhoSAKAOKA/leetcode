#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

namespace problem1 {
class Solution {
public:
	int maxSelectedElements(vector<int>& nums) {
		map<int, int> freq_map;
		for (auto&& num : nums) { freq_map[num]++; }
		int ans = 0;
		int prev_val = INT_MIN;
		int normal_streak = 0;
		int inc_streak = 0;

		for (auto&& [v, count] : freq_map) {
			if (prev_val < v - 2) {
				if (count == 1) {
					normal_streak = 1;
					inc_streak = 1;
				}
				else {
					normal_streak = 1;
					inc_streak = 2;
				}
			}
			else if (prev_val == v - 2) {
				if (count == 1) {
					normal_streak = inc_streak + 1;
					inc_streak = 1;
				}
				else {
					normal_streak = inc_streak + 1;
					inc_streak = inc_streak + 2;
				}
			}
			else if (prev_val == v - 1) {
				if (count == 1) {
					normal_streak = normal_streak + 1;
					inc_streak = inc_streak + 1;
				}
				else {
					const auto temp = normal_streak;
					normal_streak = temp + 1;
					inc_streak = max(temp + 2, inc_streak + 1);
				}
			}
			prev_val = v;
			ans = max(ans, max(normal_streak, inc_streak));
		}

		return ans;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().maxSelectedElements(nums) << endl;
}
static void run() {
	test(get_list_int("[12,11,8,7,2,10,18,12]"));
	test(get_list_int("[2,1,5,1,1]"));
	test(get_list_int("[1,4,7,10]"));
	//test(get_list_int("[12,11,8,7,2,10,18,12]"));
}
}

int main() {
	problem1::run();
	return 0;
}
