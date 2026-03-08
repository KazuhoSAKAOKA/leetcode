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
	int minimumIndex(vector<int>& capacity, int itemSize) {
		const auto n = size(capacity);
		vector<int> indexes(n);
		for (int i = 0; i < n; i++) { indexes[i] = i; }
		stable_sort(begin(indexes), end(indexes), [&](int a, int b) { return capacity[a] < capacity[b]; });
		for (int i = 0; i < n; i++) {
			if (itemSize <= capacity[indexes[i]]) {
				return indexes[i];
			}
		}
		return -1;
	}
};
static void test(vector<int>&& capacity, int itemSize) {
	cout << Solution().minimumIndex(capacity, itemSize) << endl;
}
static void run() {
	test(get_list_int("[49,68,4,22,45,76,19,76,31,40,13,58,77,64,47,99,63,96]"), 72);
	test(get_list_int("[1,5,3,7]"), 3);
	test(get_list_int("[3,5,4,3]"), 2);
	test(get_list_int("[4]"), 5);
}
}

namespace problem2 {
class Solution {
public:

	int smallestBalancedIndex(vector<int>& nums) {
		const auto n = size(nums);
		vector<unsigned long long> prefix_sums(n + 1);
		for (size_t i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + nums[i]; }

		int last_ok = -1;
		unsigned long long cur_prod = 1LL;
		for (int i = n - 1; i >= 0; i--) {
			if (prefix_sums[i] == cur_prod) {
				last_ok = i;
			}
			if(prefix_sums.back() < cur_prod) {
				return last_ok;
			}
			cur_prod *= nums[i];
		}
		return last_ok;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().smallestBalancedIndex(nums) << endl;
}
static void run() {
	test(get_list_int("[999,818,984,995,841,822,984,978,960,997,896,926,759,961,1000,562,1,1,1,87,4,1,40]"));
	test(get_list_int("[2,1,2]"));
	test(get_list_int("[2,8,2,2,5]"));
	test(get_list_int("[1]"));
}
}

namespace problem3 {
class Solution {
public:
	int minOperations(string s) {
		const auto n = size(s);
		if (n == 1) { return 0; }
		if (n == 2) {
			if (s[0] > s[1]) { return -1; }
			return 0;
		}
		bool sorted = true;
		for (int i = 0; i < n - 1; i++) {
			if (s[i] > s[i + 1]) {
				sorted = false;
				break;
			}
		}
		if (sorted) { return 0; }
		if (
			all_of(next(cbegin(s)), cend(s), [&](char c) { return s[0] <= c; }) ||
			all_of(cbegin(s), prev(cend(s)), [&](char c) { return s[n - 1] >= c; })
			) {
			return 1;
		}

		char min_el = 'z' + 1;
		int min_el_count = 0;
		char max_el = 'a' - 1;
		int max_el_count = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] < min_el) {
				min_el = s[i]; 
				min_el_count = 1;
			}
			else if (s[i] == min_el) {
				min_el_count++;
			}

			if (s[i] > max_el) {
				max_el = s[i];
				max_el_count = 1;
			}
			else if (s[i] == max_el) {
				max_el_count++;
			}
		}
		if ((s[0] == max_el && max_el_count == 1) && (s[n - 1] == min_el && min_el_count == 1)) {
			bool sorted_1 = true;
			for (int i = 1; i < n - 1; i++) {
				if (s[i] > s[i + 1]) {
					sorted_1 = false;
					break;
				}
			}
			bool sorted_2 = true;
			for (int i = 0; i < n - 2; i++) {
				if (s[i] > s[i + 1]) {
					sorted_2 = false;
					break;
				}
			}
			int opcount = 3;
			if (sorted_1) {
				opcount--;
			}
			else if (sorted_2) {
				opcount--;
			}


			return opcount;
		}
		return 2;
	}
};
static void test(string&& s) {
	cout << Solution().minOperations(s) << endl;
}
static void run() {
	test("jgg");

	test("edc");
	test("onon");
	test("dog");
	test("card");
	test("gf");
}
}

namespace problem4 {
class Solution {
public:

	long long min_cost_rec(const string& s, const vector<long long>& prefix_sums, long long begin_index, long long len, long long encCost, long long flatCost) {
		const auto ones = prefix_sums[begin_index + len] - prefix_sums[begin_index];
		long long cur_cost = ones == 0 ? flatCost : (len * ones * encCost);
		if (len % 2 != 0) {
			return cur_cost;
		}
		long long cost1 = min_cost_rec(s, prefix_sums, begin_index, len / 2, encCost, flatCost) +
			min_cost_rec(s, prefix_sums, begin_index + (len / 2), len / 2, encCost, flatCost);
		return min(cur_cost, cost1);
	}

	long long minCost(string s, int encCost, int flatCost) {
		const long long n = size(s);
		vector<long long> prefix_sums(n + 1);
		for (long long i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + (s[i] == '1' ? 1LL : 0LL); }

		return min_cost_rec(s, prefix_sums, 0, n, encCost, flatCost);
	}
};
static void test(string&& s, int encCost, int flatCost) {
	cout << Solution().minCost(s, encCost, flatCost) << endl;
}
static void run() {
	test("1010", 2, 1);
	test("1010", 3, 10);
	test("00", 1, 2);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
