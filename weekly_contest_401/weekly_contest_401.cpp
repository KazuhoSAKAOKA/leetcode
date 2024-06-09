// weekly_contest_401.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stack>
#include <queue>
#include <chrono>
#include <bitset>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


namespace problem1 {

class Solution {
public:
	int numberOfChild(int n, int k) {
		int index = 0;
		int direction = 1;
		for (int i = 0; i < k; i++) {
			index += direction;
			if (direction > 0) {
				if (index == n - 1) {
					direction = -1;
				}
			}
			else {
				if (index == 0) {
					direction = 1;
				}
			}
		}
		return index;
	}
};
void test(int n, int k) {
	cout << Solution().numberOfChild(n, k) << endl;
}
void run() {
	test(3, 5);
	test(5, 6);
	test(4, 2);
}
}

namespace problem2 {

class Solution {
public:

	static int rec(int n, int k, map<pair<int, int>, int>& memo) {
		constexpr long long MODULO = 1000000007;
		if (k == 0) {
			return 1;
		}
		if (n == 1) {
			return 1;
		}
		const auto key = make_pair(n, k);
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}

		long long value = 0;

		for (int i = 1; i <= n; i++) {
			value += rec(i, k - 1, memo);
			value %= MODULO;
		}

		int v = static_cast<int>(value % MODULO);
		memo[key] = v;
		return v;
	}

	int valueAfterKSeconds(int n, int k) {
		constexpr long long MODULO = 1000000007;
		vector<vector<long long>> dp(k + 1, vector<long long>(n, 0));
		for (int i = 0; i < n; i++) {
			dp[0][i] = 1;
		}
		for (int i = 0; i <= k; i++) {
			dp[i][0] = 1;
		}
		for (int i = 1; i <= k; i++) {
			long long total = 1;
			for (int j = 1; j < n; j++) {
				total += dp[i - 1][j];
				total %= MODULO;
				dp[i][j] = total;
			}
		}
		return dp[k][n - 1];
	}
};
void test(int n, int k) {
	cout << Solution().valueAfterKSeconds(n, k) << endl;
}
void run() {
	test(1, 1000);
	auto s = chrono::system_clock::now();
	test(1000, 1000);
	auto e = chrono::system_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>((e - s)).count() << endl;
	//test(4, 1000);
	test(4, 5);
	test(5, 3);
}
}

namespace problem3 {
class Solution {
public:
int maxTotalReward(vector<int>& rewardValues) {
	sort(begin(rewardValues), end(rewardValues));
	unordered_set<int> before;
	before.insert(0);
	int max_value = 0;
	unordered_set<int> current(before);
	for (int i = 0; i < rewardValues.size(); i++) {
		for (auto&& v : before) {
			if (v < rewardValues[i]) {
				const auto value = v + rewardValues[i];
				max_value = max(value, max_value);
				current.insert(value);
			}
		}
		before = current;
	}
	return *max_element(cbegin(before), cend(before));
}
};

void test(vector<int>&& rewardValues) {
	cout << Solution().maxTotalReward(rewardValues) << endl;
}

void run() {
	test(get_list_int("[1,1,3,3]"));
	test(get_list_int("[1,6,4,3,2]"));
}
}

namespace problem4 {
class Solution {
public:
	int maxTotalReward(vector<int>& rewardValues) {
		constexpr int MAX_VALUE = 5 * 1e5 * 2;
		sort(begin(rewardValues), end(rewardValues));
		bitset<MAX_VALUE> bs1;
		bs1.set(0, true);
		bitset<MAX_VALUE> bs2;
		int now = 0;
		for (auto&& reward: rewardValues) {
			while (now < reward) {
				bs2.set(now);
				now++;
			}
			auto temp = (bs1 & bs2);
			auto temp2 = temp << reward;
			bs1 |= temp2;
		}
		for (int i = MAX_VALUE - 1; i >= 0; i--) {
			if (bs1.test(i)) {
				return i;
			}
		}
		return -1;
	}
};
void test(vector<int>&& rewardValues) {
	cout << Solution().maxTotalReward(rewardValues) << endl;
}
void run() {
	test(get_list_int("[1,1,3,3]"));
	test(get_list_int("[1,6,4,3,2]"));
}
}


int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
}