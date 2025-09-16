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

	template <typename T>
	static T gcd(const T& a, const T& b) {
		if (b == 0) { return a; }
		return gcd(b, a % b);
	}

	template <typename T>
	static T lcm(const T& a, const T& b) {
		return a / gcd(a, b) * b;
	}

    vector<int> replaceNonCoprimes(vector<int>& nums) {
		vector<int> ans;
		ans.reserve(size(nums));
		auto push_ans = [&](int value) {
			int cur(value);
			while (!ans.empty() && gcd(ans.back(), cur) > 1) {
				cur = lcm(ans.back(), cur);
				ans.pop_back();
			}
			ans.push_back(cur);
			};

		for (auto&& num : nums) {
			push_ans(num);
		}
		return ans;
    }
};

static void test(vector<int>&& nums) {
    output(Solution().replaceNonCoprimes(nums));
}
int main() {
	test(get_list_int("[6,4,3,2,7,6,2]"));
	test(get_list_int("[2,2,1,1,3,3,3]"));
	return 0;
}