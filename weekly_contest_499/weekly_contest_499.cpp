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
	vector<int> findValidElements(vector<int>& nums) {
		const auto n = size(nums);
		vector<bool> valids(n);
		valids[0] = valids[n - 1] = true;
		int max_value = nums[0];
		for (int i = 1; i < n - 1; i++) {
			if (max_value < nums[i]) {
				valids[i] = true;
			}
			max_value = max(max_value, nums[i]);
		}
		max_value = nums[n - 1];
		for (int i = n - 2; i > 0; i--) {
			if (max_value < nums[i]) {
				valids[i] = true;
			}
			max_value = max(max_value, nums[i]);
		}
		vector<int> ans;
		for (int i = 0; i < n; i++) {
			if (valids[i]) {
				ans.push_back(nums[i]);
			}
		}
		return ans;
	}
};
static void test(vector<int>&& nums) {
	output(Solution().findValidElements(nums));
}
static void run() {
	test(get_list_int("[1,2,4,2,3,2]"));
	test(get_list_int("[5,5,5,5]"));
	test(get_list_int("[1]"));
}
}
namespace problem2 {
class Solution {
public:
	string sortVowels(string s) {

		unordered_map<char, int> freq_map;
		unordered_map<char, int> first_occurrences_map;
		string vowels;
		for (auto&& c : s) {
			if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o') {
				freq_map[c]++;
				auto it = first_occurrences_map.find(c);
				if (it == cend(first_occurrences_map)) {
					first_occurrences_map.insert({ c, static_cast<int>(size(first_occurrences_map)) });
				}
				vowels.push_back(c);
			}
		}
		if (vowels.empty()) {
			return s;
		}

		sort(begin(vowels), end(vowels), [&](char a, char b) {
			if (a == b) { return false; }
			auto freqa = freq_map[a];
			auto freqb = freq_map[b];
			if (freqa != freqb) {
				return freqa > freqb;
			}
			auto foa = first_occurrences_map[a];
			auto fob = first_occurrences_map[b];
			return foa < fob;
			});
		string ans(s);
		int vowel_index = 0;
		for (int i = 0; i < size(ans); i++) {
			if (ans[i] == 'a' || ans[i] == 'i' || ans[i] == 'u' || ans[i] == 'e' || ans[i] == 'o') {
				ans[i] = vowels[vowel_index++];
			}
		}

		return ans;
	}
};
static void test(string&& s) {
	cout << Solution().sortVowels(s) << endl;
}
static void run() {
	test("leetcode");
	test("aeiaaioooa");
	test("baeiou");
}
}
namespace problem3 {
class Solution {
public:
	long long minOperations(vector<int>& nums) {
		const long long n = size(nums);
		long long total_opvalues = 0LL;

		vector<long long> st;

		auto get_diff = [&](long long index)-> long long {
			if (size(st) == 1) {
				return 0LL;
			}

			long long level = static_cast<long long>(nums[index]);
			if (size(st) > 1) {
				level = min(level, static_cast<long long>(nums[st[size(st) - 2]]));
			}
			return level - nums[st.back()];
			};

		for (long long i = 0; i < n; i++) {
			while (!st.empty() && nums[st.back()] <= nums[i]) {
				total_opvalues += get_diff(i);
				st.pop_back();
			}
			st.push_back(i);
		}
		while (size(st) > 1) {
			const long long v1 = nums[st[size(st) - 2]];
			const long long v2 = nums[st[size(st) - 1]];

			total_opvalues += v1 - v2;
			st.pop_back();
		}
		return total_opvalues;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().minOperations(nums) << endl;
}
static void run() {
	test(get_list_int("[12,1,14]"));
	test(get_list_int("[3,3,2,1]"));
	test(get_list_int("[5,1,2,3]"));
}
}
namespace problem4 {
class Solution {
public:

	template<typename T>
	class binary_indexed_tree {
		int n;
		std::vector<T> data;

	public:
		binary_indexed_tree(int size) : n(size), data(size + 1, 0) {}

		void update(int i, T x) {
			++i;
			while (i <= n) {
				data[i] = max(data[i], x);
				i += i & -i;
			}
		}

		T query(int i) const {
			T res = 0;
			while (i > 0) {
				res = max(data[i], res);
				i -= i & -i;
			}
			return res;
		}
	};

	using fenwick_tree = binary_indexed_tree<long long>;

	long long maxAlternatingSum(vector<int>& nums, int k) {
		const int n = size(nums);
		if (n == 1) { return nums[0]; }
		const auto max_val = *max_element(cbegin(nums), cend(nums));
		vector<vector<long long>> dp(n, vector<long long>(2));
		fenwick_tree st0(max_val + 1);
		fenwick_tree st1(max_val + 1);
		long long ans = 0;
		for (int i = 0; i < n; i++) {
			if (i - k >= 0) {
				const auto target = i - k;
				const long long base_val = static_cast<long long>(nums[target]);
				st0.update(nums[target], max(dp[target][0], base_val));
				st1.update(max_val + 1 - nums[i], max(dp[target][1], base_val));
			}

			
			const auto best_low = st0.query(nums[i] - 1);
			const auto best_high = st1.query(max_val + 1 - nums[i]);
			dp[i][0] = max(best_high + static_cast<long long>(nums[i]), static_cast<long long>(nums[i]));
			dp[i][1] = max(best_low + static_cast<long long>(nums[i]), static_cast<long long>(nums[i]));


			ans = max(ans, max(dp[i][0], dp[i][1]));
		}

		return ans;
	}
};
static void test(vector<int>&& nums, int k) {
	cout << Solution().maxAlternatingSum(nums, k) << endl;
}
static void run() {
	test(get_list_int("[5,4,2]"), 2);
	test(get_list_int("[3,5,4,2,4]"), 1);
	//test(get_list_int("[5]"), 1);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
