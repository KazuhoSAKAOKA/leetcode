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
	vector<int> toggleLightBulbs(vector<int>& bulbs) {
		vector<bool> states(100);
		for (auto&& b : bulbs) {
			states[b - 1] = !states[b - 1];
		}
		vector<int> ans;

		for (int i = 0; i < 100; i++) {
			if (states[i]) {
				ans.emplace_back(i + 1);
			}
		}

		return ans;
	}
};
static void test(vector<int>&& bulbs) {
	output(Solution().toggleLightBulbs(bulbs));
}
static void run() {
	test(get_list_int("[10,30,20,10]"));
	test(get_list_int("[100,100]"));
}
}

namespace problem2 {
class Solution {
public:
	int firstUniqueFreq(vector<int>& nums) {
		map<int, int> num_freqs;
		for (auto&& num : nums) {
			num_freqs[num]++;
		}
		map<int, set<int>> freqs;
		for (auto&& [num, freq]: num_freqs) {
			freqs[freq].insert(num);
		}

		set<int> targets;
		for (auto&& [freq, vals] : freqs) {
			if (size(vals) == 1) {
				targets.insert(cbegin(vals), cend(vals));
			}
		}
		if (targets.empty()) {
			return -1;
		}
		for (auto&& num : nums) {
			if (targets.find(num) != cend(targets)) {
				return num;
			}
		}
		return -1;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().firstUniqueFreq(nums) << endl;
}
static void run() {
	test(get_list_int("[20,10,30,30]"));
	test(get_list_int("[20,20,10,30,30,30]"));
	test(get_list_int("[10,10,20,20]"));
}
}

namespace problem3 {
class Solution {
public:

	static vector<int> manacher_odd(const string& original) {
		int n = size(original);
		vector<int> rad(n);
		int c = 0, r = 0;

		while (c < n) {
			while (0 <= c - r && c + r < n && original[c - r] == original[c + r]) { r++; }
			rad[c] = r;
			int k = 1;
			while (0 <= c - k && k + rad[c - k] < r) {
				rad[c + k] = rad[c - k];
				k++;
			}
			c += k;
			r -= k;
		}
		return rad;
	}
	static vector<int> manacher_even(const string& original) {
		const auto n_original = size(original);
		string s(2 * n_original + 1, '#');
		for (int i = 0; i < n_original; i++) { s[2 * i + 1] = original[i]; }
		const auto n = 2 * n_original + 1;
		vector<int> rad(n);
		int c = 0, r = 0;
		while (c < n) {
			while (0 <= c - r && c + r < n && s[c - r] == s[c + r]) r++;
			rad[c] = r;
			int k = 1;
			while (0 <= c - k && k + rad[c - k] < r) {
				rad[c + k] = rad[c - k];
				k++;
			}
			c += k;
			r -= k;
		}
		vector<int> radeven(size(original));

		for (int i = 0; i < n_original; i++) {
			radeven[i] = rad[i * 2] / 2;
		}
		return radeven;
	}
	/*const vector<int> odds = manacher_odd(s);
		const vector<int> evens = manacher_even(s);
		int longest = 0;
		for (auto&& len : odds) {
			longest = max(longest, len);
		}
		for (auto&& len : evens) {
			longest = max(longest, len);
		}*/

	using key_t = tuple<int, int, bool>;
	using memo_t = map<key_t, int>;

	static int get_len(const string& s, int left_index, int right_index, bool deleted, memo_t& memo) {
		if (left_index < 0 || size(s) <= right_index) {
			if (deleted) { return 0; }
			if (left_index >= 0 || size(s) > right_index) {
				return 1;
			}
			return INT_MIN;
		}

		const key_t key{ left_index, right_index, deleted };

		auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}
		int len = 0;
		if (s[left_index] == s[right_index]) {
			len = max(len, get_len(s, left_index - 1, right_index + 1, deleted, memo) + 2);
		}
		if (!deleted) {
			if (0 <= left_index -1 &&  s[left_index - 1] == s[right_index]) {
				len = max(len, get_len(s, left_index - 2, right_index + 1, true, memo) + 3);
			}
			if (right_index + 1 < size(s) && s[left_index] == s[right_index + 1]) {
				len = max(len, get_len(s, left_index - 1, right_index + 2, true, memo) + 3);
			}
		}
		if (!deleted) {
			len = max(len, 1);
		}
		memo[key] = len;
		return len;
	}
	static int tle(const string& s) {
		const int n = size(s);
		int max_len = 2;
		memo_t memo;
		max_len = max(max_len, get_len(s, 0, 1, false, memo));
		for (int i = 1; i < n - 1; i++) {
			const auto odd_len = get_len(s, i - 1, i + 1, false, memo) + 1;
			max_len = max(max_len, odd_len);
			const auto even_len = get_len(s, i, i + 1, false, memo);
			max_len = max(max_len, even_len);
		}
		return max_len;
	}
	int almostPalindromic(string s) {
		int max_len;
		return max_len;
	}
};
static void test(string&& s) {
	cout << Solution().almostPalindromic(s) << endl;
}
static void run() {
	test("abbc");
	test("abca");
	test("abba");
	test("zzabba");
}
}

namespace problem4 {
class Solution {
public:
	int maxXor(vector<int>& nums, int k) {
		int max_xor = 0;
		const int n = size(nums);
		int l = 0;
		multiset<int> freqs;
		for (int r = 0; r < n; r++) {
			freqs.insert(nums[r]);
			while (l < r && *crbegin(freqs) - *cbegin(freqs) > k) {
				auto it = freqs.find(nums[l]);
				freqs.erase(it);
				l++;
			}
			int cur_xor = 0;
			for (int i = r; i >= l; i--) {
				cur_xor ^= nums[i];
				max_xor = max(max_xor, cur_xor);
			}

		}
		return max_xor;
	}
};
static void test(vector<int>&& nums, int k) {
	cout << Solution().maxXor(nums, k) << endl;
}
static void run() {
	test(get_list_int("[5,4,5,6]"), 2);
	test(get_list_int("[5,4,5,6]"), 1);
}
}

int main()
{
	//problem1::run();
	//problem2::run();
	problem3::run();
	problem4::run();
	return 0;
}
