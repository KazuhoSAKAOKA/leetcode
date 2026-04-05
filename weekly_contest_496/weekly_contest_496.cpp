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
	static char get_rev(char c) {
		if ('a' <= c && c <= 'z') {
			auto index = c - 'a';
			return 'a' + 26 - index - 1;
		}
		else {
			auto index = c - '0';
			return '0' + 10 - index - 1;
		}
	}

	int mirrorFrequency(string s) {
		unordered_map<char, size_t> freq_map;
		for (auto&& c : s) { freq_map[c]++; }

		int ans = 0;

		for (int i = 0; i < 5; i++) {
			const int v1 = freq_map[i + '0'];
			const int v2 = freq_map[get_rev(i + '0')];
			ans += abs(v1 - v2);
		}
		for (char c = 'a'; c < 'a' + 13; c++) {
			const int v1 = freq_map[c];
			const int v2 = freq_map[get_rev(c)];
			ans += abs(v1 - v2);
		}
		return ans;
	}
};
static void test(string&& s) {
	cout << Solution().mirrorFrequency(s) << endl;
}
static void run() {
	test("ab1z9");
	test("4m7n");
	test("byby");
}
}

namespace problem2 {
class Solution {
public:
	vector<int> findGoodIntegers(int n) {
		map<long long, size_t> values;

		long long i = 1;

		for (;;) {
			const auto v1 = i * i * i;
			if (n < v1) {
				break;
			}
			for (long long j = i; ; j++) {
				const auto v2 = j * j * j;
				if (n < v1 + v2) { break; }
				values[v1 + v2]++;
			}
			i++;
		}
		vector<int> ans;
		for (auto&& [v, count] : values) {
			if (1 < count) {
				ans.push_back(v);
			}
		}

		return ans;
	}
}; 
static void test(int n) {
	output(Solution().findGoodIntegers(n));
}
static void run() {
	test(1e9);
	test(4104);
	test(578);
}
}

namespace problem3 {
class Solution {
public:
	long long minIncrease(vector<int>& nums) {
		const auto n = size(nums);
		if (n % 2 != 0 || n <= 3) {
			long long cur_count = 0;
			for (int i = 1; i < n - 1; i += 2) {
				cur_count += max(0, max(nums[i - 1], nums[i + 1]) + 1 - nums[i]);
			}
			return cur_count;
		}
		else {
			const auto m = (n - 2) / 2;
			vector<vector<long long>> dp(m, vector<long long>(2));

			dp[0][0] = max(0, max(nums[1 - 1], nums[1 + 1]) + 1 - nums[1]);
			dp[0][1] = max(0, max(nums[2 - 1], nums[2 + 1]) + 1 - nums[2]);

			for (int i = 1; i < m; i++) {
				const auto index0 = (i + 1) * 2 - 1;
				const auto index1 = (i + 1) * 2;
				dp[i][0] = dp[i - 1][0] + max(0, max(nums[index0 - 1], nums[index0 + 1]) + 1 - nums[index0]);
				dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + max(0, max(nums[index1 - 1], nums[index1 + 1]) + 1 - nums[index1]);
			}
			return min(dp.back()[0], dp.back()[1]);
		}
	}
};

static void test(vector<int>&& nums) {
	cout << Solution().minIncrease(nums) << endl;
}
static void run() {
	test(get_list_int("[17,22,35,33,27,10]"));
	test(get_list_int("[2,1,1,3]"));
	test(get_list_int("[12,23,13,17,21,3]"));
	test(get_list_int("[17,3,10,4,19]"));
	test(get_list_int("[1,2,2]"));
	test(get_list_int("[5,2,1,4,3]"));
}
}

namespace problem4 {
class Solution {
public:
	int minOperations(vector<int>& nums, int k) {
		constexpr long long INF = LLONG_MAX / 2;
		const auto n = size(nums);
		if (k == 0) { return 0; }
		if (n / 2 < k) { return -1; }
		if (n == 2) {
			return nums[0] == nums[1] ? 1 : 0;
		}
		long long ans = INF;
		{
			vector<vector<long long>> dp(n, vector<long long>(k + 1, INF));
			for (int i = 0; i < n; i++) { dp[i][0] = 0LL; }

			dp[0][1] = max(0, max(nums[n - 1], nums[1]) + 1 - nums[0]);
			dp[1][1] = min(dp[0][1], max(0LL, static_cast<long long>(max(nums[0], nums[2]) + 1 - nums[1])));

			for (int i = 2; i < n - 1; i++) {
				const long long cur_cost = max(0, max(nums[i - 1], nums[(i + 1) % n]) + 1 - nums[i]);
				for (int j = 1; j <= k; j++) {
					const auto cost1 = dp[i - 2][j - 1] + cur_cost;
					const auto cost2 = dp[i - 1][j];
					dp[i][j] = min(dp[i][j], min(cost1, cost2));
				}
			}
			ans = min(ans, dp[n - 2][k]);
		}
		{
			vector<vector<long long>> dp(n, vector<long long>(k + 1, INF));
			for (int i = 0; i < n; i++) { dp[i][0] = 0LL; }

			dp[0][1] = INF;
			dp[1][1] = min(dp[0][1], max(0LL, static_cast<long long>(max(nums[0], nums[2]) + 1 - nums[1])));

			for (int i = 2; i < n; i++) {
				const long long cur_cost = max(0, max(nums[i - 1], nums[(i + 1) % n]) + 1 - nums[i]);
				for (int j = 1; j <= k; j++) {
					const auto cost1 = dp[i - 2][j - 1] + cur_cost;
					const auto cost2 = dp[i - 1][j];
					dp[i][j] = min(dp[i][j], min(cost1, cost2));
				}
			}
			ans = min(ans, dp.back()[k]);
		}

		return ans == INF ? -1 : ans;
	}
};
static void test(vector<int>&& nums, int k) {
	cout << Solution().minOperations(nums, k) << endl;
}
static void run() {
	test(get_list_int("[23,10,-14,-23,1]"), 2);
	test(get_list_int("[6,-7,11,13]"), 2);
	test(get_list_int("[-21,12,1,-5]"), 2);
	test(get_list_int("[11,6,-4]"), 1);
	test(get_list_int("[11,-3,3]"), 1);
	test(get_list_int("[5,9]"), 1);
	test(get_list_int("[2,1,2]"), 1);
	test(get_list_int("[4,5,3,6]"), 2);
	test(get_list_int("[3,7,3]"), 2);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
