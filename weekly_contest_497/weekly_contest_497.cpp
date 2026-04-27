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
	vector<int> findDegrees(vector<vector<int>>& matrix) {
		const auto n = size(matrix);
		vector<int> counts(n);
		for (size_t i = 0; i < n; i++) {
			for (size_t j = i + 1; j < n; j++) {
				if (i != j && matrix[i][j] != 0) {
					counts[i]++;
					counts[j]++;
				}
			}
		}

		return counts;
	}
};
static void test(vector<vector<int>>&& matrix) {
	output(Solution().findDegrees(matrix));
}
static void run() {
	test(get_matrix_int("[[0,1,1],[1,0,1],[1,1,0]]"));
	test(get_matrix_int("[[0,1,0],[1,0,0],[0,0,0]]"));
	test(get_matrix_int("[[0]]"));
}
}

namespace problem2 {
class Solution {
public:
	vector<double> internalAngles(vector<int>& sides) {
		sort(begin(sides), end(sides));
		if (sides[0] + sides[1] <= sides[2]) {
			return {};
		}
		const auto a = sides[0];
		const auto b = sides[1];
		const auto c = sides[2];
		const double cosa = static_cast<double>((b * b) + (c * c) - (a * a)) / (2 * b * c);
		const double cosb = static_cast<double>((c * c) + (a * a) - (b * b)) / (2 * c * a);
		const double cosc = static_cast<double>((a * a) + (b * b) - (c * c)) / (2 * a * b);

		vector<double> ans{
			std::acos(cosa) * 180 / numbers::pi,
			std::acos(cosb) * 180 / numbers::pi,
			std::acos(cosc) * 180 / numbers::pi,
		};

		sort(begin(ans), end(ans));
		return ans;
	}
};
static void test(vector<int>&& sides) {
	output(Solution().internalAngles(sides));
}
static void run() {
	test(get_list_int("[3,4,5]"));
	test(get_list_int("[2,4,2]"));
}
}

namespace problem3 {
class Solution {
public:
	int longestBalanced(string s) {
		const int n = size(s);
		vector<long long> prefix_sums_0(n + 1);
		vector<long long> prefix_sums_1(n + 1);
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				prefix_sums_0[i + 1] = prefix_sums_0[i] + 1;
				prefix_sums_1[i + 1] = prefix_sums_1[i];
			}
			else {
				prefix_sums_0[i + 1] = prefix_sums_0[i];
				prefix_sums_1[i + 1] = prefix_sums_1[i] + 1;
			}
		}
		const long long zeros = prefix_sums_0.back();
		const long long ones = prefix_sums_1.back();
		const int upper_lim = min(zeros, ones);
		if (upper_lim == 0) { return 0; }
		int max_len = 0;

		map<int, int> diff_ps_map;
		diff_ps_map[0] = 0;
		for (int i = 0; i < n; i++) {
			const auto ps0 = prefix_sums_0[i + 1];
			const auto ps1 = prefix_sums_1[i + 1];
			const auto diff = ps0 - ps1;
			const auto it0 = diff_ps_map.find(diff);
			int cur_len = 0;
			if (it0 != cend(diff_ps_map)) {
				const auto st = it0->second;
				cur_len = i + 1 - st;
				int append_len = 0;
				if (2 <= st) {
					auto check = [&]() {
						const auto cur_0 = prefix_sums_0[i + 1] - prefix_sums_0[st];
						const auto cur_1 = prefix_sums_1[i + 1] - prefix_sums_1[st];
						if (upper_lim <= cur_0) {
							return false;
						}
						if (s[st - 1] == s[st - 2]) {
							return true;
						}
						return false;
						};
					if (check()) {
						append_len = 2;
					}
				}
				if (i + 2 < n) {
					auto check = [&]() {
						const auto cur_0 = prefix_sums_0[i + 1] - prefix_sums_0[st];
						const auto cur_1 = prefix_sums_1[i + 1] - prefix_sums_1[st];
						if (upper_lim <= cur_0) {
							return false;
						}
						if (s[i + 1] == s[i + 2]) {
							return true;
						}
						return false;
						};
					if (check()) {
						append_len = 2;
					}
				}
				max_len = max(max_len, cur_len + append_len);
			}
			else {
				diff_ps_map.insert({ diff, i + 1 });
			}
		}


		return max_len;
	}
};

static void test(string&& s) {
	cout << Solution().longestBalanced(s) << endl;
}
static void run() {
	test("00001000001100000100");

	test("0011110");


	test("100001");


	test("000011");


	test("01000011");

	test("0010100");


	test("111");
}
}

namespace problem4 {
static void test() {
}
static void run() {
}
}

int main() {
	//problem1::run();
	//problem2::run();
	problem3::run();
	problem4::run();
	return 0;
}
