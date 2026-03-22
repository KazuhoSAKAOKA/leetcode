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
	bool uniformArray(vector<int>& nums1) {
		return true;
	}
};
static void test(vector<int>&& nums1) {
	cout << Solution().uniformArray(nums1) << endl;
}
static void run() {
	test(get_list_int("[2,3]"));
	test(get_list_int("[4,6]"));
}
}

namespace problem2 {
class Solution {
public:
	bool uniformArray(vector<int>& nums1) {
		const auto n = size(nums1);
		int even_count = 0;
		int odd_count = 0;
		int min_even = INT_MAX;
		int min_odd = INT_MAX;

		for (int i = 0; i < n; i++) {
			if (nums1[i] % 2 == 0) {
				even_count++;
				min_even = min(min_even, nums1[i]);
			}
			else {
				odd_count++;
				min_odd = min(min_odd, nums1[i]);
			}
		}
		if (even_count == 0 || odd_count == 0) { return true; }
		return min_odd < min_even;
	}
};
static void test(vector<int>&& nums1) {
	cout << Solution().uniformArray(nums1) << endl;
}
static void run() {
	test(get_list_int("[1,4,7]"));
	test(get_list_int("[2,3]"));
	test(get_list_int("[4,6]"));
}
}

namespace problem3 {
class Solution {
public:
	void min_map(map<int, int>& target_map, int key, int value) {
		auto it = target_map.find(key);
		if (it == cend(target_map)) {
			target_map.insert({ key,value });
		}
		else {
			it->second = min(it->second, value);
		}
	}

	int minRemovals(vector<int>& nums, int target) {
		int cur_xor = 0;
		for (auto&& num : nums) {
			cur_xor ^= num;
		}
		if (cur_xor == target) { return 0; }

		const auto n = size(nums);
		vector<map<int, int>> dp(n);
		min_map(dp[0], nums[0], 0);
		min_map(dp[0], 0, 1);
		for (int i = 1; i < n; i++) {
			for (auto&& [value, count] : dp[i - 1]) {
				min_map(dp[i], value ^ nums[i], count);
				min_map(dp[i], value, count + 1);
			}
		}
		auto it = dp.back().find(target);
		if (it == cend(dp.back())) { return -1; }
		return it->second;
	}
};
static void test(vector<int>&& nums, int target) {
	cout << Solution().minRemovals(nums, target) << endl;
}
static void run() {
	test(get_list_int("[0,6]"), 0);
	test(get_list_int("[1,2,3]"), 2);
	test(get_list_int("[2,4]"), 1);
	test(get_list_int("[7]"), 7);
}
}

namespace problem4 {
class Solution {
public:

	static long long wa(vector<int>& nums) {
		const long long n = size(nums);
		long long total = 0;
		map<int, int> freq;
		vector<int> bit_freq(32);
		long long l = 0;
		int cur_bitwise_or = 0;
		for (long long r = 0; r < n; r++) {
			auto it = freq.find(nums[r]);
			if (it == cend(freq)) {
				cur_bitwise_or |= nums[r];
				for (int i = 0; i < 31; i++) {
					if (nums[r] & (1 << i)) {
						bit_freq[i]++;
					}
				}
				freq.insert({ nums[r],1 });
			}
			else {
				it->second++;
			}

			auto try_move_left = [&]() {
				while (l < r) {
					auto it1 = freq.find(cur_bitwise_or);
					if (it1 != cend(freq)) {
						return;
					}
					auto it2 = freq.find(nums[l]);
					if (it2->second == 1) {
						freq.erase(it2);
						for (int i = 0; i < 31; i++) {
							if (nums[l] & (1 << i)) {
								bit_freq[i]--;
								if (bit_freq[i] == 0) {
									cur_bitwise_or &= ~(1 << i);
								}
							}
						}
					}
					else {
						it2->second--;
					}
					l++;
				}
				};
			try_move_left();
			total += r - l + 1;
		}
		return total;
	}


	long long countGoodSubarrays(vector<int>& nums) {
		const long long n = size(nums);
		vector<long long> left_boundaries(n, 0);
		vector<long long> right_boundaries(n, n - 1);
		vector<long long> mono_stack;
		for (long long i = 0; i < n; i++) {
			while (!mono_stack.empty() && (nums[mono_stack.back()] | nums[i]) == nums[i]) {
				mono_stack.pop_back();
			}
			if (mono_stack.empty()) {
				left_boundaries[i] = -1;
			}
			else {
				left_boundaries[i] = mono_stack.back();
			}
			mono_stack.push_back(i);
		}

		mono_stack.clear();
		for (long long i = n - 1; i >= 0; i--) {
			while (!mono_stack.empty() && (nums[mono_stack.back()] | nums[i]) == nums[i]) {
				mono_stack.pop_back();
			}
			if (mono_stack.empty()) {
				right_boundaries[i] = n;
			}
			else {
				right_boundaries[i] = mono_stack.back();
			}
			mono_stack.push_back(i);
		}

		unordered_map<int, long long> prev_values;
		auto get_left = [&](long long index)->long long {
			auto it = prev_values.find(nums[index]);
			if (it == cend(prev_values)) { return left_boundaries[index]; }
			return max(it->second, left_boundaries[index]);
			};
		long long total = 0;
		for (long long i = 0; i < n; i++) {
			const auto lefts = i - get_left(i);
			const auto rights = right_boundaries[i] - i;
			total += lefts * rights;
			prev_values[nums[i]] = i;
		}
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().countGoodSubarrays(nums) << endl;
}
static void run() {
	test(get_list_int("[0,1,1]"));
	test(get_list_int("[6,6]"));
	test(get_list_int("[4,2,3]"));
	test(get_list_int("[1,3,1]"));
	test(get_list_int("[5,2,7]"));
	test(get_list_int("[6,4,2,6]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
