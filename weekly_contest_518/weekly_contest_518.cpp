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
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"
using namespace std;

namespace problem1 {
class Solution {
public:
	int countRotations(string s, int k) {
		const int n = size(s);
		int ans = 0;

		for (int i = 0; i < n; i++) {
			int score = 0;
			for (int j = 0; j < n - 1; j++) {
				if (s[(j + i) % n] == s[(j + i + 1) % n]) {
					score++;
				}
			}
			if (score == k) {
				ans++;
			}
		}
		return ans;
	}
};
static void test(string&& s, int k) {
	cout << Solution().countRotations(s, k) << endl;
}
static void run() {
	test("aab", 1);
	test("abca", 0);
}
}

namespace problem2 {
class Solution {
public:
	int countGoodRotations(vector<int>& nums) {
		const int n = size(nums);
		const int half = n / 2;
		vector<long long> prefix_sums(n + 1);
		for (int i = 0; i < n; i++) { prefix_sums[i + 1] = prefix_sums[i] + static_cast<long long>(nums[i]); }
		const long long total = prefix_sums.back();
		int ans = 0;

		for (int i = 0; i <= half; i++) {
			const auto first = prefix_sums[i + half] - prefix_sums[i];
			const auto remain = total - first;
			if (first > remain) {
				ans++;
			}
		}
		for (int i = half + 1; i < n; i++) {
			const auto first = prefix_sums[n] - prefix_sums[i] + prefix_sums[((i + half) % n)] - prefix_sums[0];
			const auto remain = total - first;
			if (first > remain) {
				ans++;
			}
		}


		return ans;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().countGoodRotations(nums) << endl;
}
static void run() {
	test(get_list_int("[1,2,3,4,5,6]"));
	test(get_list_int("[1,2,1,2]"));
}
}

namespace problem3 {
class Solution {
public:
	int countGroups(vector<int>& position, vector<int>& speed, int distance) {
		const int n = size(position);
		int ans = 1;
		int right_speed = speed[n - 1];
		for (int i = n - 2; i >= 0; i--) {
			if (position[i + 1] <= position[i] + distance) {
			}
			else {
				if (right_speed < speed[i]) {

				}
				else {
					ans++;
					right_speed = speed[i];
				}
			}
		}
		return ans;
	}
};
static void test(vector<int>&& position, vector<int>&& speed, int distance) {
	cout << Solution().countGroups(position, speed, distance) << endl;
}
static void run() {
	test(get_list_int("[657,686]"), get_list_int("[139,284]"), 77);
	test(get_list_int("[1,5,6,20]"), get_list_int("[4,3,2,3]"), 1);
	test(get_list_int("[1,5,9]"), get_list_int("[3,2,2]"), 2);
	test(get_list_int("[9]"), get_list_int("[8]"), 5);

}
}

namespace problem4 {
class Solution {
public:


	//auto djikstra = [&]() {
	//	std::vector<T> costs(graph.size(), std::numeric_limits<T>::max());
	//	struct point {
	//		T cost;
	//		size_t pos;
	//		bool operator > (const point& other) const {
	//			return cost > other.cost;
	//		}
	//	};
	//	std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
	//	p_queue.push(point{ 0, s });
	//	costs[s] = 0;
	//	while (!p_queue.empty()) {
	//		const auto [current_cost, current] = p_queue.top();
	//		p_queue.pop();
	//		if (costs[current] < current_cost) { continue; }
	//		for (auto&& [cost, to] : graph[current]) {
	//			if (costs[to] > cost + current_cost) {
	//				costs[to] = cost + current_cost;
	//				p_queue.push(point{ costs[to] , to });
	//			}
	//		}
	//	}
	//	return costs[e];
	//	};

	int minCost(vector<vector<int>>& grid, int k) {
		const auto n = size(grid);
		const auto m = size(grid[0]);
		if (n == 1 && m == 1) { return grid[0][0]; }
		set<tuple<int, int, long long>> prev;
		prev.insert({ 0,0, grid[0][0] });
		constexpr long long INF = LLONG_MAX / 2;
		vector<vector<long long>> costs(n, vector<long long>(m, INF));
		costs[0][0] = grid[0][0];
		const vector<pair<int, int>> directions{
			{-1,0},{1,0}, {0,-1},{0,1},
		};
		long long detected = INF;

		for (int i = 0; i <= k; i++) {
			set<tuple<int, int, long long>> current;
			for (auto&& [y, x, cost] : prev) {
				for (auto&& [dy, dx] : directions) {
					int ny = y + dy;
					int nx = x + dx;
					long long cur_cost = cost;
					while (0 <= ny && ny < n && 0 <= nx && nx < m) {
						cur_cost += grid[ny][nx];
						if (cur_cost < costs[ny][nx]) {
							if (ny == n - 1 && nx == m - 1) {
								detected = min(detected, cur_cost);
							}
							else {
								current.insert({ ny,nx, cur_cost });
							}
							costs[ny][nx] = cur_cost;
						}
						ny += dy;
						nx += dx;
					}
				}
			}
			swap(current, prev);
		}
		if (detected < INF) {
			return static_cast<int>(detected);
		}
		return -1;
	}
};
static void test(vector<vector<int>>&& grid, int k) {
	cout << Solution().minCost(grid, k) << endl;
}
static void run() {
	test(get_matrix_int("[[10]]"), 0);
	test(get_matrix_int("[[2,7,3],[1,4,5]]"), 1);
	test(get_matrix_int("[[4,1,9],[3,2,5],[4,8,6]]"), 2);
	test(get_matrix_int("[[1,9],[3,4]]"), 0);
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
