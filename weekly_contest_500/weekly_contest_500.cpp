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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
	vector<int> countOppositeParity(vector<int>& nums) {
		const auto n = size(nums);
		vector<int> ans;

		for (int i = 0; i < n; i++) {
			int count = 0;
			for (int j = i + 1; j < n; j++) {
				if (nums[i] % 2 != nums[j] % 2) {
					count++;
				}
			}

			ans.emplace_back(count);
		}
		return ans;
	}
};
static void test(vector<int>&& nums) {
	output(Solution().countOppositeParity(nums));
}
static void run() {
	test(get_list_int("[1,2,3,4]"));
	test(get_list_int("[1]"));
}
}
namespace problem2 {
class Solution {
public:
	static int reverse_num(int n) {
		if (n == 0) {
			return 0;
		}
		vector<int> digits;
		int cur(n);
		while (cur > 0) {
			digits.emplace_back(cur % 10);
			cur /= 10;
		}

		int value = 0;
		int base = 1;
		for (auto it = crbegin(digits); it != crend(digits); ++it) {
			value += *it * base;
			base *= 10;
		}

		return value;
	}

	static std::vector<bool> eratosthenes(int n) {
		std::vector<bool> candidates(n + 1, true);
		candidates[0] = false;
		candidates[1] = false;
		const auto limit = sqrt(n);
		int current = 2;
		while (current <= limit) {
			if (candidates[current]) {
				for (int i = 2; i * current <= n; i++) {
					candidates[i * current] = false;
				}
			}
			current++;
		}
		return candidates;
	}

	int sumOfPrimesInRange(int n) {
		const auto rev = reverse_num(n);
		const auto low = min(rev, n);
		const auto high = max(rev, n);
		const auto primes = eratosthenes(high);
		int ans = 0;
		for (int i = low; i <= high; i++) {
			if (primes[i]) {
				ans += i;
			}
		}
		return ans;
	}
};
static void test(int n) {
	cout << Solution().sumOfPrimesInRange(n) << endl;
}
static void run() {
	test(13);
	test(10);
	test(8);
}
}
namespace problem3 {
class Solution {
public:
	vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
		const auto n = size(nums);
		vector<long long> closests(n);
		closests[0] = 1;
		closests[n - 1] = n - 2;
		for (int i = 1; i < n - 1; i++) {
			if (nums[i] - nums[i - 1] <= nums[i + 1] - nums[i]) {
				closests[i] = i - 1;
			}
			else {
				closests[i] = i + 1;
			}
		}
		vector<long long> prefix_sums_up(n + 1);
		vector<long long> prefix_sums_down(n + 1);
		for (int i = 0; i < n - 1; i++) {
			long long diff;
			if (closests[i] == i + 1) {
				diff = 1LL;
			}
			else {
				diff = nums[i + 1] - nums[i];
			}
			prefix_sums_up[i + 1] = prefix_sums_up[i] + diff;
		}

		for (int i = n - 1; i > 0; i--) {
			long long diff;
			if (closests[i] == i - 1) {
				diff = 1LL;
			}
			else {
				diff = nums[i] - nums[i - 1];
			}
			prefix_sums_down[i - 1] = prefix_sums_down[i] + diff;
		}
		const auto q = size(queries);
		vector<int> ans;
		ans.reserve(q);

		for (auto&& query : queries) {
			const auto l = query[0];
			const auto r = query[1];
			if (l == r) {
				ans.push_back(0);
			}
			else if(l < r) {
				ans.push_back(prefix_sums_up[r] - prefix_sums_up[l]);
			}
			else {
				ans.push_back(prefix_sums_down[r] - prefix_sums_down[l]);
			}
		}
		return ans;
	}
};
static void test(vector<int>&& nums, vector<vector<int>>&& queries) {
	output(Solution().minCost(nums, queries));
}
static void run() {
	test(get_list_int("[-5,-2,3]"), get_matrix_int("[[0,2],[2,0],[1,2]]"));
	test(get_list_int("[0,2,3,9]"), get_matrix_int("[[3,0],[1,2],[2,0]]"));
}
}
namespace problem4 {
class Solution {
public:


	int maxFixedPoints(vector<int>& nums) {
		const auto n = size(nums);
		vector<pair<int, int>> diff_nums;
		diff_nums.reserve(n);
		for (int i = 0; i < n; i++) {
			if (nums[i] <= i) {
				diff_nums.push_back(make_pair(i - nums[i], nums[i]));
			}
		}

		sort(begin(diff_nums), end(diff_nums));

		const auto n2 = size(diff_nums);
		vector<int> dp;
		dp.reserve(n2);

		for (auto&& p : diff_nums) {
			auto it = lower_bound(begin(dp), end(dp), p.second);
			if (it == cend(dp)) {
				dp.push_back(p.second);
			}
			else {
				*it = p.second;
			}
		}
		return static_cast<int>(size(dp));
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().maxFixedPoints(nums) << endl;
}
static void run() {
	//test(get_list_int("[4,4,0,3]"));
	test(get_list_int("[2,0,0]"));
	test(get_list_int("[0,3,2]"));
	test(get_list_int("[0,2,1]"));
	test(get_list_int("[3,1,2]"));
	test(get_list_int("[1,0,1,2]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}

//vector<int> dp(n);
//if (nums[0] == 0) {
//	dp[0] = 1;
//}
//int ans = dp[0];
//for (int i = 1; i < n; i++) {
//	if (nums[i] == 0) {
//		dp[0] = max(dp[0], 1);
//		ans = max(ans, dp[nums[i]]);
//	}
//	else if (nums[i] <= i) {
//		dp[nums[i]] = dp[nums[i] - 1] + 1;
//		ans = max(ans, dp[nums[i]]);
//	}
//}
