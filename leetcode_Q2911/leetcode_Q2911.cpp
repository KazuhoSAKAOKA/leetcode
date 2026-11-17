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
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

namespace problem1 {
class Solution {
public:

	template<typename T>
	static vector<T> divisor(T n) {
		vector<T> ret;
		for (T i = 1; i * i <= n; i++) {
			if (n % i == 0) {
				ret.push_back(i);
				if (i * i != n) { ret.push_back(n / i); }
			}
		}
		return ret;
	}


	int minimumChanges(string s, int k) {
		map<string, int> cost_memo;
		map<int, vector<int>> divisor_map;
		map<pair<int, int>, optional<int>> memo;
		const int n = size(s);
		auto get_divisors = [&](int len)->const vector<int>&{
			auto it = divisor_map.find(len);
			if (it != cend(divisor_map)) {
				return it->second;
			}
			auto temp = divisor(len);
			auto [it2, _] = divisor_map.insert({ len, temp });
			return it2->second;
			};

		auto get_cost = [&](const string& ss)->int {
			auto it = cost_memo.find(ss);
			if (it != cend(cost_memo)) {
				return it->second;
			}
			int min_cost = INT_MAX;
			const int len = size(ss);
			const auto& divisors = get_divisors(len);
			for (auto&& d : divisors) {
				if (d == len) { continue; }
				int cost = 0;
				for (int i = 0; i < len / (d * 2); i++) {
					for (int j = 0; j < d; j++) {
						if (ss[i * d + j] != ss[len - ((i + 1) * d) + j]) {
							cost++;
						}
					}
				}
				min_cost = min(min_cost, cost);
			}
			cost_memo.insert({ss, min_cost});
			return min_cost;
			};

		auto fnc = [&](auto f, int index, int remain)->optional<int> {
			if (index == n && remain == 0) {
				return 0;
			}
			if (index > n || remain == 0) {
				return nullopt;
			}
			const auto key = make_pair(index, remain);
			auto it = memo.find(key);
			if (it != cend(memo)) {
				return it->second;
			}

			int min_cost = INT_MAX;
			for (int len = 2; index + len <= n; len++) {
				auto after_ans = f(f, index + len, remain - 1);
				if (!after_ans.has_value()) {
					continue;
				}
				int cost = 0;
				auto ss = s.substr(index, len);
				cost += get_cost(ss);
				cost += after_ans.value();
				min_cost = min(min_cost, cost);
			}

			if (min_cost == INT_MAX) {
				memo.insert({ key,nullopt });
				return nullopt;
			}
			memo.insert({ key,min_cost });
			return min_cost;
			};

		const auto ans = fnc(fnc, 0, k);
		return ans.value();
	}
};
static void test(string&& s, int k) {
	cout << Solution().minimumChanges(s, k) << endl;
}
static void run() {
	test("abcac", 2);
	test("abcdef", 2);
	test("aabbaa", 3);
}
}


int main() {
	problem1::run();
	return 0;
}
