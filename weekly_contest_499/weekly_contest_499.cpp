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



	template <typename T>
	struct segment_tree_max {
		T inf_;
		vector<T> data_;
		size_t n_;

		segment_tree_max(size_t n)
			: inf_(numeric_limits<T>::min()){
			n_ = 1;
			while (n_ < n) {
				n_ <<= 1;
			}
			data_.assign(2 * n_, inf_);
		}

		void update(size_t index, T value) {
			size_t i = index + n_;
			if (value < data_[i]) { return; }
			data_[i] = value;
			while (i > 1) {
				i >>= 1;
				data_[i] = max(data_[i << 1], data_[(i << 1) | 1]);
			}
		}

		T query(size_t a, size_t b) {
			return query(a, b, 1, 0, n_);
		}

		T query(size_t a, size_t b, size_t index, size_t l, size_t r) {
			if (r <= a || b <= l) {
				return inf_;
			}
			if (a <= l && r <= b) {
				return data_[index];
			}
			size_t mid = (l + r) >> 1;
			T vl = query(a, b, index << 1, l, mid);
			T vr = query(a, b, (index << 1) | 1, mid, r);
			return max(vl, vr);
		}
	};

	long long maxAlternatingSum(vector<int>& nums, int k) {
		const int n = size(nums);
		if (n == 1) { return nums[0]; }
		const auto max_val = *max_element(cbegin(nums), cend(nums));
		// dp[index][is_peak]
		vector<vector<long long>> dp(n, vector<long long>(2));
		using seg_tree = segment_tree_max<long long>;
		seg_tree st_peak(max_val + 1);
		seg_tree st_valley(max_val + 1);

		long long ans = 0;
		for (int i = 0; i < n; i++) {

			if (i - k >= 0) {
				st_peak.update(nums[i - k], dp[i - k][1]);
				st_valley.update(nums[i - k], dp[i - k][0]);
			}
			const auto best_peak = max(0LL, st_peak.query(nums[i] + 1, max_val + 1));
			const auto best_valley = max(0LL, st_valley.query(0, nums[i]));
			dp[i][0] = max(best_peak + static_cast<long long>(nums[i]), static_cast<long long>(nums[i]));
			dp[i][1] = max(best_valley + static_cast<long long>(nums[i]), static_cast<long long>(nums[i]));


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
	test(get_list_int("[5]"), 1);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
