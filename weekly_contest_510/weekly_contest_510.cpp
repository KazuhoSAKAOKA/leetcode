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
	int get_sec(const string& s) {
		return
			stoi(s.substr(0, 2)) * 60 * 60 +
			stoi(s.substr(3, 2)) * 60 +
			stoi(s.substr(6, 2));
	}
	int secondsBetweenTimes(string startTime, string endTime) {
		const auto s = get_sec(startTime);
		const auto e = get_sec(endTime);
		return e - s;
	}
};
static void test(string&& startTime, string&& endTime) {
	cout << Solution().secondsBetweenTimes(startTime, endTime) << endl;
}
static void run() {
	test("01:00:00", "01:00:25");
	test("12:34:56", "13:00:00");
}

}

namespace problem2 {
class Solution {
public:
	int minimumCost(vector<int>& nums, int k) {
		constexpr long long MODULO = 1e9 + 7;
		long long current = k;
		long long cost = 0;
		long long base_cost = 1;
		for (auto&& num : nums) {
			if (current < num) {
				const auto val = num - current;
				auto sum_count = (val + k - 1) / k;
				current += k * sum_count - num;
				if (current < 0) {
					sum_count++;
					current += k;
				}
				auto a = (base_cost * 2 + (sum_count - 1));
				auto b = sum_count;
				a %= MODULO;
				b %= MODULO;
				if (a % 2 == 0) {
					a /= 2;
				}
				else {
					b /= 2;
				}
				auto append_cost = a * b;
				append_cost %= MODULO;
				cost += append_cost;
				cost %= MODULO;
				base_cost += sum_count;
			}
			else {
				current -= num;
			}
		}

		return static_cast<int>(cost);
	}
};
static void test(vector<int>&& nums, int k){
	cout << Solution().minimumCost(nums, k) << endl;
}
static void run() {
	test(get_list_int("[1,2,3,4]"), 4);
	test(get_list_int("[1,1,7,14]"), 4);
	test(get_list_int("[1,2,3,4]"), 10);
}
}

namespace problem3 {
class Solution {
public:
	vector<string> createGrid(int m, int n, int k) {
		vector<string> ans;
		ans.reserve(m);
		if (k == 1) {
			ans.push_back(string(n, '.'));
			string row(n - 1, '#');
			row += '.';
			for (int i = 0; i < m - 1; i++) {
				ans.push_back(row);
			}
		}
		else {
			if (m == 1 || n == 1) { return {}; }
			if (k == 2) {
				ans.push_back(string(n, '.'));
				ans.push_back(string(n - 2, '#') + string(2, '.'));
				for (int i = 0; i < m - 2; i++) {
					ans.push_back(string(n - 1, '#') + string(1, '.'));
				}
			}
			else if (k == 3) {
				if (2 < n) {
					ans.push_back(string(n, '.'));
					ans.push_back(string(n - 3, '#') + string(3, '.'));
					for (int i = 0; i < m - 2; i++) {
						ans.push_back(string(n - 1, '#') + string(1, '.'));
					}
				}
				else if (2 < m) {
					for (int i = 0; i < m - 3; i++) {
						ans.push_back(string(1, '.') + string(n - 1, '#'));
					}
					for (int i = 0; i < 2; i++) {
						ans.push_back(string(2, '.') + string(n - 2, '#'));
					}
					ans.push_back(string(n, '.'));
				}
				else {
					return {};
				}
			}
			else if (k == 4) {
				if (n >= 4) {
					ans.push_back(string(n, '.'));
					ans.push_back(string(n - 4, '#') + string(4, '.'));
					for (int i = 0; i < m - 2; i++) {
						ans.push_back(string(n - 1, '#') + string(1, '.'));
					}
				}
				else if (m >= 4) {
					for (int i = 0; i < m - 4; i++) {
						ans.push_back(string(1, '.') + string(n - 1, '#'));
					}
					for (int i = 0; i < 3; i++) {
						ans.push_back(string(2, '.') + string(n - 2, '#'));
					}
					ans.push_back(string(n, '.'));
				}
				else if (n == 3 && m == 3) {
					ans.push_back("..#");
					ans.push_back("...");
					ans.push_back("#..");
				}
				else {
					return {};
				}
			}
			else {
				throw runtime_error("not suppored.");
			}
		}
		


		return ans;
	}
};
static void test(int m, int n, int k) {
	output(Solution().createGrid(m, n, k));
}
static void run() {
	//test(2, 2, 2);

	test(6, 3, 4);

	//test(2, 3, 2);
	//test(3, 3, 4);
	//test(1, 4, 2);
}
}

namespace problem4 {
class Solution {
public:
	int maxConsistentColumns(vector<vector<int>>& grid, int limit) {
		const auto rows = size(grid);
		const auto cols = size(grid[0]);
		vector<int> indexes(rows);
		for (int i = 0; i < rows; i++) { indexes[i] = i; }
		vector<map<int,int>> dp(cols);
		dp[0][0] = 1;
		int max_cols = 1;
		for (int i = 1; i < cols; i++) {
			dp[i][i] = 1;
			for (auto&& [last_col, count] : dp[i - 1]) {
				if (all_of(cbegin(indexes), cend(indexes), [&](int row)->bool { return abs(grid[row][i] - grid[row][last_col]) <= limit; })) {
					dp[i][i] = max(dp[i][i], count + 1);
					max_cols = max(max_cols, dp[i][i]);
				}
				dp[i][last_col] = count;
			}
		}
		return max_cols;
	}
};
static void test(vector<vector<int>>&& grid, int limit) {
	cout << Solution().maxConsistentColumns(grid, limit) << endl;
}
static void run() {
	test(get_matrix_int("[[-2,0,3]]"), 2);
	test(get_matrix_int("[[1,-1,1],[2,2,2]]"), 1);
	test(get_matrix_int("[[-5,5]]"), 9);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
