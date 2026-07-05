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
	static int get_digit_range(int value) {
		if (value == 0) { return 0; }
		int max_digit = 0;
		int min_digit = 9;

		while (value > 0) {
			const auto d = value % 10;
			max_digit = max(max_digit, d);
			min_digit = min(min_digit, d);
			value /= 10;
		}
		return max_digit - min_digit;
	}

	int maxDigitRange(vector<int>& nums) {
		map<int, int> val_map;
		for (auto&& num : nums) {
			val_map[get_digit_range(num)] += num;
		}
		return crbegin(val_map)->second;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().maxDigitRange(nums) << endl;
}
static void run() {
	test(get_list_int("[5724,111,350]"));
	test(get_list_int("[90,900]"));
}
}

namespace problem2 {
class Solution {
public:
	bool canMakeSubsequence(string s, string t) {
		const auto n = size(s);
		const auto m = size(t);
		if (m < n) { return false; }
		vector<vector<long long>> prefix_sums(26, vector<long long>(m + 1));
		for (long long i = 0; i < m; i++) {
			for (long long c = 0; c < 26; c++) {
				prefix_sums[c][i + 1] = prefix_sums[c][i] + (t[i] == static_cast<char>('a' + c) ? 1LL : 0LL);
			}
		}

		auto myfind = [&](char c, size_t offset)->size_t {
			const auto index = static_cast<long long>(c - 'a');
			auto& target = prefix_sums[index];
			const auto v = target[offset];
			auto it = upper_bound(next(cbegin(target), offset), cend(target), v);
			return distance(cbegin(target), it);
			};

		vector<vector<size_t>> dp(n, vector<size_t>(2, m + 1));
		dp[0][0] = myfind(s[0], 0);
		dp[0][1] = 1;

		for (size_t i = 1; i < n; i++) {
			if (dp[i - 1][1] < m + 1) {
				dp[i][1] = myfind(s[i], dp[i - 1][1]);
			}

			if (dp[i - 1][0] < m + 1) {
				dp[i][0] = myfind(s[i], dp[i - 1][0]);
				dp[i][1] = min(dp[i][1], dp[i - 1][0] + 1);
			}
		}
		
		return dp.back()[0] < m + 1 || dp.back()[1] < m + 1;
	}
};
static void test(string&& s, string&& t) {
	cout << Solution().canMakeSubsequence(s, t) << endl;
}
static void run() {
	test("cat", "chat");
	test("plane", "apple");
}
}

namespace problem3 {
class Solution {
public:

	template<typename T>
	static vector<T> divisor(T n) {
		vector<T> ret;
		for (T i = 1; i * i <= n; i++) {
			if (n % i == 0) {
				ret.push_back(i);
				if (i * i != n) { ret.push_back(n / i); }
			}
		}
		return ret;
	}

	int divisibleGame(vector<int>& nums) {
		const long long n = size(nums);
		constexpr long long MODULO = 1e9 + 7;

		set<int> candidates;
		unordered_set<int> exists;
		for (auto&& num : nums) {
			if (exists.count(num) == 0) {
				const auto cand = divisor(num);
				candidates.insert(cbegin(cand), cend(cand));
				exists.insert(num);
			}
		}
		candidates.erase(1);
		if (candidates.empty()) {
			candidates.insert(2);
		}
		auto get_val = [](long long num, long long k)->long long {
			return num % k == 0 ? num : -num;
			};

		long long max_score = LLONG_MIN;
		long long selected_k = 0;
		for (auto&& k : candidates) {

			long long prefix = get_val(nums[0], k);
			long long max_sum = prefix;
			long long min_prefix = min(0LL, prefix);
			for (long long i = 1; i < n; i++) {
				prefix += get_val(nums[i], k);
				max_sum = max(max_sum, prefix - min_prefix);
				min_prefix = min(min_prefix, prefix);
			}
			if (max_score < max_sum) {
				max_score = max_sum;
				selected_k = k;
			}
		}

		max_score += MODULO;
		const auto v1 = (max_score % MODULO) * selected_k;
		return static_cast<int>(v1 % MODULO);
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().divisibleGame(nums) << endl;
}
static void run() {
	//test(get_list_int("[1,4,6,8]"));
	//test(get_list_int("[2,1,2]"));
	test(get_list_int("[1]"));
}
}

namespace problem4 {
class Solution {
public:

	static vector<int> manacher(const vector<int>& nums) {
		const auto n = size(nums);
		vector<int> radius(n);
		int i = 0, j = 0;
		while (i < n) {
			while (i - j >= 0 && i + j < n && nums[i - j] == nums[i + j]) {
				++j;
			}
			radius[i] = j;
			int k = 1;
			while (i - k >= 0 && i + k < n && k + radius[i - k] < j) {
				radius[i + k] = radius[i - k];
				++k;
			}
			i += k;
			j -= k;
		}
		return radius;
	}

	static long long get_sum(const vector<int>& nums) {
		const auto n = size(nums);
		vector<long long> prefix_sums(n + 1);
		for (long long i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + nums[i]; }
		const auto r = manacher(nums);
		long long max_sum = 0;

		for (long long i = 0; i < n; i++) {
			const auto cur_sum = prefix_sums[i + r[i]] - prefix_sums[i - r[i] + 1];
			max_sum = max(max_sum, cur_sum);
  		}
		return max_sum;
	}


	long long getSum(vector<int>& nums) {
		const auto n = size(nums);
		const auto v1 = get_sum(nums);
		vector<int> nums2(n * 2);
		for (int i = 0; i < n; i++) {
			nums2[i * 2] = nums[i];
		}
		const auto v2 = get_sum(nums2);
		return max(v1, v2);
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().getSum(nums) << endl;
}
static void run() {
	test(get_list_int("[10,10]"));
	test(get_list_int("[1,2,3,2,1,5,6]"));
	test(get_list_int("[7,1,2,1,7,3,4,3,4]"));
	test(get_list_int("[1,2,3,4,5]"));
	test(get_list_int("[1000]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	problem3::run();
	//problem4::run();
	return 0;
}
