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
	string trimTrailingVowels(string s) {
		set<char> vowels{ 'a','i','u','e','o', };
		string temp;
		bool rev = false;
		for (auto it = crbegin(s); it != crend(s); ++it) {
			if (rev) {
				temp += *it;
			}
			else {
				if (vowels.find(*it) == cend(vowels)) {
					temp += *it;
					rev = true;
				}
			}
		}
		return string(crbegin(temp), crend(temp));
	}
};
static void test(string&& s) {
	cout << Solution().trimTrailingVowels(s) << endl;
}
static void run() {
	test("idea");
	test("day");
	test("aeiou");
}
}
namespace problem2 {
class Solution {
public:
	static int rec(int n, map<int, int>& memo) {
		if (n == 1) {
			return 0;
		}
		auto it = memo.find(n);
		if (it != cend(memo)) {
			return it->second;
		}

		int min_cost = INT_MAX;
		const int limit = n % 2 == 0 ? (n / 2) : (n / 2) + 1;
		for (int i = 1; i <= limit; i++) {
			int cost = (i * (n - i)) + rec(i, memo) + rec(n - i, memo);
			min_cost = min(min_cost, cost);
		}
		memo[n] = min_cost;
		return min_cost;
	}

	int minCost(int n) {
		map<int, int> memo;
		return rec(n, memo);
	}
};
static void test(int n) {
	cout << Solution().minCost(n) << endl;
}
static void run() {
	test(3);
	test(4);
}

}
namespace problem3 {
class Solution {
public:

	static int tle(const vector<vector<int>>& grid) {
		const auto n = size(grid);
		const auto m = size(grid.front());
		vector<set<int>> dp(n);
		for (auto&& num : grid[0]) {
			dp[0].insert(num);
		}
		for (int i = 1; i < n; i++) {
			for (auto&& value : dp[i - 1]) {
				for (auto&& num : grid[i]) {
					dp[i].insert(value | num);
				}
			}
		}
		return *cbegin(dp.back());
	}


	static void rec(size_t n, size_t m, const vector<vector<int>>& grid, int bit, vector<set<int>>& candidates, int& value) {
		if (bit < 0) {
			return;
		}

		const int bit_val = 1 << bit;
		bool must_on = false;
		vector<set<int>> bit_on_indexes(n);
		for (int i = 0; i < n; i++) {
			for (auto it = cbegin(candidates[i]); it != cend(candidates[i]); ++it) {
				if (grid[i][*it] & bit_val) {
					bit_on_indexes[i].insert(*it);
				}
			}
			if (size(candidates[i]) == size(bit_on_indexes[i])) {
				must_on = true;
			}
		}
		if (must_on) {
			value |= bit_val;
		}
		else {
			for (int i = 0; i < n; i++) {
				for (auto it = cbegin(bit_on_indexes[i]); it != cend(bit_on_indexes[i]); ++it) {
					candidates[i].erase(*it);
				}
			}
		}
		rec(n, m, grid, bit - 1, candidates, value);
	}

	int minimumOR(vector<vector<int>>& grid) {
		const auto n = size(grid);
		const auto m = size(grid.front());

		vector<set<int>> candidates(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				candidates[i].insert(j);
			}
		}
		int value = 0;
		rec(n, m, grid, 17, candidates, value);

		return value;
	}
};
static void test(vector<vector<int>>&& grid) {
	cout << Solution().minimumOR(grid) << endl;
}
static void run() {
	test(get_matrix_int("[[19]]"));
	test(get_matrix_int("[[1,5],[2,4]]"));
	test(get_matrix_int("[[3,5],[6,4]]"));
	test(get_matrix_int("[[7,9,8]]"));
}
}
namespace problem4 {
class Solution {
public:
	long long countSubarrays(vector<int>& nums, int k, int m) {
		const auto n = size(nums);
		map<int, size_t> freqs;
		map<int, size_t> freqs2;

		long long ans = 0;
		long long l = 0;
		long long l2 = 0;
		auto check = [&]()->bool {
			return size(freqs) > k;
			};

		long long ok_distincts = 0;

		auto check2 = [&](long long left1, long long left2)->bool {
			if (left1 > left2) { return true; }
			if (ok_distincts < k) { return false; }
			auto next_val = nums[left2];
			auto it = freqs2.find(next_val);
			if (it->second == m) {
				return false;
			}
			return true;
			};
		for (long long r = 0; r < n; r++) {
			freqs[nums[r]]++;
			freqs2[nums[r]]++;
			if (freqs2[nums[r]] == m) {
				ok_distincts++;
			}

			while (l < r && check()) {
				auto it = freqs.find(nums[l]);
				if (it->second == 1) {
					freqs.erase(it);
				}
				else {
					it->second--;
				}
				l++;
			}
			while (l2 < r && check2(l, l2)) {
				auto it = freqs2.find(nums[l2]);
				if (it->second == 1) {
					freqs2.erase(it);
					if (m == 1) {
						ok_distincts--;
					}
				}
				else {
					if (it->second == m) {
						ok_distincts--;
					}
					it->second--;
				}
				l2++;
			}
			if (ok_distincts == k) {
				ans += l2 - l + 1;
			}
		}
		return ans;
	}
};
static void test(vector<int>&& nums, int k, int m) {
	cout << Solution().countSubarrays(nums, k, m) << endl;
}
static void run() {
	test(get_list_int("[1,2,1,2,2]"), 2, 2);
	test(get_list_int("[3,1,2,4]"), 2, 1);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	problem3::run();
	//problem4::run();
	return 0;
}
