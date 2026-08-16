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
#include "./../utility/TreeNodeUtil.h"
using namespace std;

namespace problem1 {
class Solution {
public:
	int nearestDrone(vector<vector<int>>& drones, vector<int>& target) {
		int min_length = INT_MAX;
		int ans = -1;
		for (int i = 0; i < size(drones); i++) {
			const int dist = abs(drones[i][0] - target[0]) + abs(drones[i][1] - target[1]);
			if (dist <= drones[i][2]) {
				if (dist < min_length) {
					min_length = dist;
					ans = i;
				}
			}
		}
		return ans;
	}
};
static void test(vector<vector<int>>&& drones, vector<int>&& target) {
	cout << Solution().nearestDrone(drones, target) << endl;
}
static void run() {
	test(get_matrix_int("[[0,0,8],[2,2,9]]"), get_list_int("[3,4]"));
	test(get_matrix_int("[[2,1,5],[4,4,5],[6,6,8]]"), get_list_int("[5,5]"));
	test(get_matrix_int("[[4,4,5]]"), get_list_int("[8,6]"));
}
}

namespace problem2 {
class Solution {
public:
	int minPenalty(int period, vector<int>& lights, vector<int>& arrivalTime) {
		int max_penalty = 0;
		const int max_light = *max_element(cbegin(lights), cend(lights));
		auto search_min_penalty = [&](int arrival)-> int {
			const auto r = arrival % period;
			if (r < max_light) {
				return 0;
			}
			return period - r;
			};

		for (auto&& at : arrivalTime) {
			const auto penalty = search_min_penalty(at);
			max_penalty = max(max_penalty, penalty);
		}
		return max_penalty;
	}
};
static void test(int period, vector<int>&& lights, vector<int>&& arrivalTime) {
	cout << Solution().minPenalty(period, lights, arrivalTime) << endl;
}
static void run() {
	test(8, get_list_int("[2,3]"), get_list_int("[2,5,8,11]"));
	test(10, get_list_int("[3,6,8]"), get_list_int("[4,9,15]"));
	test(5, get_list_int("[2]"), get_list_int("[2,3,4,5,6]"));
}
}

namespace problem3 {
class Solution {
public:
	int maximumGap(string skill, string station) {
		const int n = size(skill);
		if (n == 1) { return 0; }
		const int m = size(station);
		vector<long long> dp_ftob(m, -1);
		{
			int i = 0;
			if (skill[0] == station[0]) {
				dp_ftob[0]++;
				i++;
			}
			for (int j = 1; j < m; j++) {
				dp_ftob[j] = dp_ftob[j - 1];
				if (i < n && skill[i] == station[j]) {
					dp_ftob[j]++;
					i++;
				}
			}
		}
		vector<long long> dp_btof(m, n);
		{
			int i = n - 1;
			if (skill[i] == station[m - 1]) {
				dp_btof[m - 1]--;
				i--;
			}
			for (int j = m - 2; j >= 0; j--) {
				dp_btof[j] = dp_btof[j + 1];
				if (i >= 0 && skill[i] == station[j]) {
					dp_btof[j]--;
					i--;
				}
			}

		}

		int max_gap = 0;
		auto it1 = cbegin(dp_ftob);
		auto it2 = cbegin(dp_btof);
		for (int i = 0; i < n - 1; i++) {
			it1 = lower_bound(it1, cend(dp_ftob), i);
			it2 = prev(upper_bound(it2, cend(dp_btof), i + 1));
			const int index1 = distance(cbegin(dp_ftob), it1);
			const int index2 = distance(cbegin(dp_btof), it2);
			max_gap = max(max_gap, index2 - index1);
		}
		return max_gap;
	}
};
static void test(string skill, string station) {
	cout << Solution().maximumGap(skill, station) << endl;
}
static void run() {
	test("ba", "bacc");
	test("ab", "aabb");
	test("aa", "aaaa");
	test("xyz", "xyzz");
	test("cbc", "cbcdbc");
}
}

namespace problem4 {
class Solution {
public:

	static long long rec(int n, const vector<vector<int>>& requests, int completed, int used, long long cur_pos, long long cur_time, map<tuple<int, long long, long long>, long long>& memo) {
		if (completed == size(requests)) {
			return cur_time;
		}

		auto key = make_tuple(used, cur_pos, cur_time);
		auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}

		long long min_time = LLONG_MAX;
		for (int i = 0; i < size(requests); i++) {
			const auto flag = (1 << i);
			if ((used & flag) == 0) {
				const auto pos = requests[i][1];
				const auto time1 = max(cur_time + abs(cur_pos - pos), static_cast<long long>(requests[i][0]));
				long long time = rec(n, requests, completed + 1, used | flag, pos, time1, memo);
				min_time = min(min_time, time);
			}
		}

		memo.insert({ key, min_time });
		return min_time;
	}


	static long long tle(int n, int start, vector<vector<int>>& requests) {
		map<tuple<int, long long, long long>, long long> memo;
		const auto ans = rec(n, requests, 0, 0, start, 0, memo);
		return ans;
	}

	long long elevatorRequests(int n, int start, vector<vector<int>>& requests) {
		const auto m = size(requests);
		const auto max_bits = (1 << m) - 1;
		vector<map<long long, long long>> dp(max_bits + 1);
		dp[0].insert({ static_cast<long long>(start), 0LL });

		for (long long bit = 0; bit <= max_bits; bit++) {
			const auto& mp = dp[bit];
			for (auto&& [cur_pos, cur_time] : mp) {
				for (long long i = 0; i < m; i++) {
					const long long flag = 1LL << i;
					if ((bit & flag) == 0) {
						const long long t = requests[i][0];
						const long long pos = requests[i][1];
						const auto time = max(cur_time + abs(cur_pos - pos), t);
						const auto nbit = bit | flag;
						auto it = dp[nbit].find(pos);
						if (it == cend(dp[nbit])) {
							dp[nbit].insert({ pos, time });
						}
						else {
							it->second = min(it->second, time);
						}
					}
				}
			}
		}

		long long ans = LLONG_MAX;
		for (auto&& [_, time] : dp[max_bits]) {
			ans = min(ans, time);
		}

		return ans;
	}

};
static void test(int n, int start, vector<vector<int>>&& requests) {
	cout << Solution().elevatorRequests(n, start, requests) << endl;
}
static void run() {
	test(9, 0, get_matrix_int("[[0,8],[6,5]]"));
	test(8, 5, get_matrix_int("[[1,7],[7,3]]"));
	test(7, 3, get_matrix_int("[[0,5],[0,1],[6,3]]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
