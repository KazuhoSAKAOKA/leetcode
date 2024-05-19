// weekly_contest_398.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <string>
#include <stack>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


namespace problem1 {
	class Solution {
	public:
		bool isArraySpecial(vector<int>& nums) {

			for (int i = 0; i < nums.size() - 1; i++) {
				if (nums[i] % 2 == nums[i + 1] % 2) {
					return false;
				}
			}
			return true;
		}
	};

	void test(vector<int>&& nums) {
		cout << Solution().isArraySpecial(nums) << endl;
	}

	void run() {
		test(get_list_int("[1]"));
		test(get_list_int("[2,1,4]"));
		test(get_list_int("[4,3,1,6]"));
	}
}

namespace problem2 {
class Solution {
public:
	vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {

		vector<int> cumulative_sums(nums.size() + 1, 0);
		cumulative_sums[0] = 0;

		auto check_invalid_counter = [&](int index) {return nums[index] % 2 == nums[index + 1] % 2 ? 1 : 0; };
		for (int i = 0; i < nums.size() - 1; i++) {
			cumulative_sums[i + 1] = cumulative_sums[i] + check_invalid_counter(i);
		}

		vector<bool> ans(queries.size(), false);

		for (int i = 0; i < queries.size(); i++) {
			const auto& query = queries[i];
			const auto v = cumulative_sums[query.back()] - cumulative_sums[query.front()];
			ans[i] = v == 0;
		}
		return ans;
	}
};

void test(vector<int>&& nums, vector<vector<int>>&& queries) {
	const auto ans = Solution().isArraySpecial(nums, queries);
	for (auto&& value : ans) {
		cout << value << ",";
	}
	cout << endl;
}

void run() {
//	test(get_list_int("[1,2,2,3]"), get_matrix_int("[[0,1],[0,2],[1,3]]"));
	test(get_list_int("[3,4,1,2,6]"),get_matrix_int("[[0,4],[0,3]]"));
	test(get_list_int("[4,3,1,6]"), get_matrix_int("[[0,2],[2,3]]"));
}
}
namespace problem3 {
class Solution {
public:
	long long sumDigitDifferences(vector<int>& nums) {
		unordered_map<int, unordered_map<char, long long>> digits_map;
		for (auto&& num : nums) {
			auto s = to_string(num);
			for (int i = 0; i < s.size(); i++) {
				digits_map[i][s[i]]++;
			}
		}

		long long ans = 0;

		for (auto&& [_, inner] : digits_map) {

			vector<pair<char, long long>> work;
			work.reserve(inner.size());
			for (auto& [c, v] : inner) {
				work.emplace_back(make_pair(c, v));
			}
			for (int i = 0; i < work.size(); i++) {
				for (int j = i + 1; j < work.size(); j++) {
					const long long comb_count = work[i].second * work[j].second;
					ans += comb_count;
				}
			}
		}
		return ans;
	}
};
void test(vector<int>&& nums) {
	cout << Solution().sumDigitDifferences(nums) << endl;
}
void run() {
	test(get_list_int("[50,28,48]"));
	test(get_list_int("[13,23,12]"));
	test(get_list_int("[10,10,10,10]"));
}
}
namespace problem4 {
class Solution {
public:

	static int pow2(int jump) {
		if (jump == 0) { return 1; }
		if (jump % 2 == 1) {
			return pow2(jump / 2) * pow2(jump / 2) * 2;
		}
		return pow2(jump / 2) * pow2(jump / 2);
	}

	using memo_key_t = tuple<int, int, bool>;
	using memo_t = map<memo_key_t, int>;

	static int rec(int k, int current, int jump, bool last_backstep, memo_t& memo) {
		if (k + 1 < current) {
			return 0;
		}
		if (last_backstep && k < current) {
			return 0;
		}

		const auto key = memo_key_t(current, jump, last_backstep);
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}

		int value = 0;
		if (current == k) {
			value = 1;
		}

		if (0 < current && !last_backstep) {
			value += rec(k, current - 1, jump, true, memo);
		}
		const auto dist = pow2(jump);
		value += rec(k, current + dist, jump + 1, false, memo);
		memo[key] = value;
		return value;
	}

	int waysToReachStair(int k) {
		memo_t memo;
		return rec(k, 1, 0, false, memo);
	}

	static int wa(int k) {
		vector<map<int, map<int, int>>> dp(k + 3);

		dp[1][0][0] = 1;

		queue<tuple<int, int, bool>> q;
		q.emplace(make_tuple(1, 0, false));

		while (!q.empty()) {
			const auto [step, jump, use_op1] = q.front();
			q.pop();

			if (0 < step && !use_op1) {
				dp[step - 1][jump][1] += dp[step][jump][0];
				q.push(make_tuple(step - 1, jump, true));
			}
			const auto next_step = step + pow2(jump);
			if (k + 2 < next_step) { continue; }

			dp[next_step][jump + 1][0] += dp[step][jump][0] + dp[step][jump][1];
			q.push(make_tuple(next_step, jump + 1, false));
		}

		int ans = 0;
		for (auto&& [_, inner] : dp[k]) {
			for (auto&& [_, v] : inner) {
				ans += v;

			}
		}
		return ans;
	}

};

void test(int k) {
	cout << Solution().waysToReachStair(k) << endl;
}

void run() {
	test(0);
	test(2);
	test(1);
}
}



int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}