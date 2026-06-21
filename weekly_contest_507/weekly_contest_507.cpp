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
	int maxDistance(string moves) {
		const unordered_map<char, pair<int, int>> dirs{
			{ 'U', {-1,0}},
			{ 'D', {1,0}},
			{ 'L', {0,-1}},
			{ 'R', {0,1}},
		};

		int free_count = 0;
		int x = 0;
		int y = 0;
		for (auto&& c : moves) {
			auto it = dirs.find(c);
			if (it == cend(dirs)) {
				free_count++;
			}
			else {
				auto [dy, dx] = it->second;
				x += dx;
				y += dy;
			}
		}

		return abs(x) + abs(y) + free_count;
	}
};
static void test(string&& moves) {
	cout << Solution().maxDistance(moves) << endl;
}
static void run() {
	test("L_D_");
	test("U_R");
}
}

namespace problem2 {
class Solution {
public:

	static bool check(long long num, int x) {
		if (num == 0) {
			return x == 0;
		}
		if (num % 10 != x) { return false; }
		int last_digit = 0;
		while (num > 0) {
			last_digit = num % 10;
			num /= 10;
		}
		return last_digit == x;
	}

	int countValidSubarrays(vector<int>& nums, int x) {
		const auto n = size(nums);
		vector<long long> prefix_sums(n + 1);
		for (size_t i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + nums[i]; }

		long long ans = 0;

		for (size_t i = 0; i < n; i++) {
			for (size_t j = i + 1; j <= n; j++) {
				const auto s = prefix_sums[j] - prefix_sums[i];
				if (check(s, x)) {
					ans++;
				}
			}
		}
		return static_cast<int>(ans);
	}
};
static void test(vector<int>&& nums, int x) {
	cout << Solution().countValidSubarrays(nums, x) << endl;
}
static void run() {
	test(get_list_int("[1,100,1]"), 1);
	test(get_list_int("[1]"), 2);
}
}

namespace problem3 {
class Solution {
public:
	int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
		if (n == 1) { return 0; }
		vector<vector<pair<int, long long>>> graph(n);
		for (auto&& edge : edges) {
			const auto u = edge[0];
			const auto v = edge[1];
			const long long w = edge[2];
			graph[u].push_back({ v,w });
		}
		priority_queue<tuple<long long, int, char, int>, vector<tuple<long long, int, char, int>>, greater<tuple<long long, int, char, int>>> q;
		vector<map<int, long long>> costs(n);
		q.push({ 0,0LL,labels[0], 1 });
		while (!q.empty()) {
			const auto [cost, p, last_char, streak] = q.top();
			if (p == n - 1) {
				return static_cast<int>(cost);
			}
			q.pop();
			for (auto&& [np,w] : graph[p]) {
				if (last_char == labels[np] && streak == k) {
					continue;
				}
				const auto new_cost = cost + w;
				int new_streak;
				if (last_char == labels[np]) {
					new_streak = streak + 1;
				}
				else {
					new_streak = 1;
				}
				auto it = costs[np].find(new_streak);

				if (it==cend(costs[np]) ||  new_cost < it->second) {
					costs[np][new_streak] = new_cost;
					q.push({ new_cost, np, labels[np], new_streak });
				}
			}
		}

		return -1;
	}
};
static void test(int n, vector<vector<int>>&& edges, string labels, int k) {
	cout << Solution().shortestPath(n, edges, labels, k) << endl;
}
static void run() {
	test(3, get_matrix_int("[[0,1,1],[1,2,1],[0,2,3]]"), "aab", 1);
	test(3, get_matrix_int("[[0,1,1],[1,2,1],[0,2,3]]"), "aab", 2);
	test(3, get_matrix_int(" [[0,1,1],[1,2,1]]"), "aaa", 2);
}
}

namespace problem4 {
class Solution {
public:

	template <typename T = long long>
	T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
		while (abs(ng - ok) > 1) {
			const auto mid = (ok + ng) / 2;
			if (check(mid)) {
				ok = mid;
			}
			else {
				ng = mid;
			}
		}
		return ok;
	}

	int maxTotalValue(vector<int>& value, vector<int>& decay, int m) {
		const auto n = size(value);
		constexpr long long MODULO = 1e9 + 7;
		int ok = 0;
		int ng = *max_element(cbegin(value), cend(value)) + 1;
		auto check = [&](int low_val)->bool {
			long long count = 0;
			for (size_t i = 0; i < n; i++) {
				if (value[i] >= low_val) {
					count += (value[i] - low_val) / decay[i] + 1;
				}
			}
			return count > m;
			};
		const auto low_val = binary_search_meguru<int>(ok, ng, check);

		long long total_sum = 0;
		long long total_count = 0;
		for (size_t i = 0; i < n; i++) {
			if (value[i] >= low_val) {
				const long long count = (value[i] - low_val) / decay[i] + 1;
				total_sum += count * value[i] - (count - 1) * count / 2 * decay[i];
				total_count += count;
				total_sum %= MODULO;
			}
		}
		if (m < total_count) {
			const long long over = total_count - m;
			const long long v = (over * low_val) % MODULO;
			total_sum += MODULO - v;
			total_sum %= MODULO;
		}

		return static_cast<int>(total_sum);
	}


	static int tle(vector<int>& value, vector<int>& decay, int m) {
		const auto n = size(value);
		struct info {
			size_t index;
		};
		vector<long long> selecteds(n);
		auto compare = [&](const info& a, const info& b)->bool {
			return value[a.index] - decay[a.index] * selecteds[a.index] < value[b.index] - decay[b.index] * selecteds[b.index];
			};
		priority_queue<info, vector<info>, decltype(compare)> pq(compare);

		for (size_t i = 0; i < n; i++) {
			pq.push(info{ i });
		}

		int total_selected = 0;
		long long current_total_value = 0;
		constexpr long long MODULO = 1e9 + 7;

		auto calc = [](int cur_val, int decay_val, int next_val) {
			const auto diff = cur_val - next_val;
			if (diff == 0) { return 1; }
			const auto count = (diff + decay_val - 1) / decay_val;
			return count;
			};

		auto get_val = [](long long cur_val, long long decay_val, long long count)-> long long {
			return cur_val * count - decay_val * ((count - 1) * count / 2);
			};
		while (!pq.empty() && total_selected < m) {
			const auto select = pq.top();
			pq.pop();
			const auto cur_value = value[select.index] - decay[select.index] * selecteds[select.index];
			int next_val;
			if (pq.empty()) {
				next_val = 0;
			}
			else {
				const auto i = pq.top().index;
				next_val = value[i] - decay[i] * selecteds[i];
			}
			const auto cur_count = calc(cur_value, decay[select.index], next_val);
			const auto proc_count = min(m - total_selected, cur_count);
			current_total_value += get_val(cur_value, decay[select.index], proc_count);
			current_total_value %= MODULO;
			selecteds[select.index] += proc_count;
			total_selected += proc_count;
			if (value[select.index] - decay[select.index] * selecteds[select.index] > 0) {
				pq.push(select);
			}
		}


		return static_cast<int>(current_total_value);
	}
};
static void test(vector<int>&& value, vector<int>&& decay, int m) {
	cout << Solution().maxTotalValue(value, decay, m) << endl;
}
static void run() {
	test(get_list_int("[6,5,4]"), get_list_int("[2,1,1]"), 4);
	test(get_list_int("[7,2,2]"), get_list_int(" [3,2,1]"), 2);
	test(get_list_int("[4,3]"), get_list_int("[5,4]"), 5);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
