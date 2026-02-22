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
	int scoreDifference(vector<int>& nums) {
		long long score1 = 0LL;
		long long score2 = 0LL;
		bool active_first = true;

		for (int i = 0; i < size(nums); i++) {
			if ((nums[i] % 2 != 0)) {
				active_first = !active_first;
			}
			if (((i + 1) % 6 == 0)) {
				active_first = !active_first;
			}
			if (active_first) {
				score1 += nums[i];
			}
			else {
				score2 += nums[i];
			}
		}
		return static_cast<int>(score1 - score2);
	}
};
static void test(vector<int>&& nums){
	cout << boolalpha << Solution().scoreDifference(nums) << endl;
}
static void run() {
	test(get_list_int("[2,4,2,1,2,1]"));
	test(get_list_int("[1,2,3]"));
	test(get_list_int("[1]"));
}
}

namespace problem2 {
class Solution {
public:

	static vector<int> get_digits(int n) {
		if (n == 0) { return{ 0 }; }
		vector<int> digits;
		int cur(n);
		while (cur > 0) {
			digits.emplace_back(cur % 10);
			cur /= 10;
		}
		return digits;
	}

	bool isDigitorialPermutation(int n) {
		vector<int> digits = get_digits(n);
		vector<long long> factorials(10);
		factorials[0] = 1;
		factorials[1] = 1;
		for (long long i = 2; i < 10; i++) {
			factorials[i] = factorials[i - 1] * i;
		}
		long long sum = accumulate(cbegin(digits), cend(digits), 0LL, [&](long long t, int d) { return t + factorials[d]; });
		vector<int> sum_digits = get_digits(sum);
		sort(begin(digits), end(digits));
		sort(begin(sum_digits), end(sum_digits));
		return digits == sum_digits;
	}
};
static void test(int n) {
	cout << Solution().isDigitorialPermutation(n) << endl;
}
static void run() {
	test(145);
	test(10);
}
}

namespace problem3 {
class Solution {
public:

	static char get_xor_char(char c1, char c2) {
		return c1 == c2 ? '0' : '1';
	}

	string maximumXor(string s, string t) {
		const long long n = size(s);
		const long long ones = count_if(cbegin(t), cend(t), [](char c) { return c == '1'; });
		int remain_ones = ones;
		string ans;
		ans.reserve(n);
		for (long long i = 0; i < n; i++) {
			const auto remain_len = n - i;
			if (remain_ones == 0) {
				ans += get_xor_char(s[i], '0');
			}
			else if (remain_len <= remain_ones) {
				ans += get_xor_char(s[i], '1');
				remain_ones--;
			}
			else {
				if (s[i] == '1') {
					ans += '1';
				}
				else {
					ans += '1';
					remain_ones--;
				}
			}
		}

		return ans;
	}
};
static void test(string&& s, string&& t) {
	cout << Solution().maximumXor(s, t) << endl;
}
static void run() {
	test("101", "011");
	test("0110", "1110");
	test("0101", "1001");
}
}

namespace problem4 {

template <typename T>
static T gcd(const T& a, const T& b) {
	if (b == 0) { return a; }
	return gcd(b, a % b);
}

struct fraction {
	long long numerator;
	long long denominator;
	fraction() : numerator(0), denominator(1) {}
	fraction(long long n, long long d = 1LL) : numerator(n), denominator(d) {
		if (d == 0) { throw exception(); }
		simplification();
	}
	fraction& simplification() {
		const auto gcdv = gcd(numerator, denominator);
		if (gcdv != 1) {
			numerator /= gcdv;
			denominator /= gcdv;
		}
		return *this;
	}
};
static fraction operator * (const fraction& a, const fraction& b) {
	if (a.numerator == 0 || b.numerator == 0) {
		return fraction(0);
	}
	fraction m(a.numerator * b.numerator, a.denominator * b.denominator);
	m.simplification();
	return m;
}
static optional<fraction> operator / (const fraction& a, const fraction& b) {
	if (b.numerator == 0) {
		return nullopt;
	}
	fraction d(a.numerator * b.denominator, a.denominator * b.numerator);
	d.simplification();
	return d;
}

static bool operator == (const fraction& a, const long long& b) {
	if (a.denominator != 1) { return false; }
	return a.numerator == b;
}
static bool operator == (long long& b, const fraction& a) {
	if (a.denominator != 1) { return false; }
	return a.numerator == b;
}
static bool operator < (const fraction& a, const fraction& b) {
	if (a.denominator == b.denominator) { return a.numerator < b.numerator; }
	return a.numerator * b.denominator < b.numerator * a.denominator;
}

class Solution {
public:

	int countSequences(vector<int>& nums, long long k) {
		const auto n = size(nums);
		vector<map<fraction, int>> dp(n + 1);
		dp[0][fraction(1)] = 1;
		for (int i = 0; i < n; i++) {
			const fraction cur_num(nums[i]);
			const auto& before_map = dp[i];
			auto& mp = dp[i + 1];
			for (auto&& [f, count] : before_map) {
				mp[f] += count;
				const fraction mval = f * cur_num;
				mp[mval] += count;
				const optional<fraction> dval_opt = f / cur_num;
				mp[dval_opt.value()] += count;
			}
		}

		int ans = 0;
		for (auto&& [f, count] : dp.back()) {
			if (f == k) {
				ans += count;
			}
		}
		return ans;
	}
};
static void test(vector<int>&& nums, long long k) {
	cout << Solution().countSequences(nums, k) << endl;
}
static void run() {
	test(get_list_int("[2,3,2]"), 6);
	test(get_list_int("[4,6,3]"), 2);
	test(get_list_int("[1,5]"), 1);
}
}

int main(){
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
