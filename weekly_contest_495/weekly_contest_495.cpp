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
	int firstMatchingIndex(string s) {
		for (int i = 0; i < size(s); i++) {
			if (s[i] == s[size(s) - i - 1]) {
				return i;
			}
		}
		return -1;
	}
};
static void test(string&& s) {
	cout << Solution().firstMatchingIndex(s) << endl;
}
static void run() {
	test("abcacbd");
	test("abc");
	test("abcdab");
}
}

namespace problem2 {
class EventManager {
	map<int, set<int>, greater<int>> priority_map;
	map<int, int> event_to_priority;
public:
	EventManager(vector<vector<int>>& events) {
		for (auto&& ev : events) {
			const auto evid = ev.front();
			const auto priority = ev.back();
			priority_map[priority].insert(evid);
			event_to_priority.insert({ evid,priority });
		}
	}

	void updatePriority(int eventId, int newPriority) {
		auto it = event_to_priority.find(eventId);
		if (it == cend(event_to_priority)) { return; }
		auto pit = priority_map.find(it->second);
		pit->second.erase(eventId);
		if (pit->second.empty()) {
			priority_map.erase(pit);
		}
		priority_map[newPriority].insert(eventId);
		it->second = newPriority;
	}

	int pollHighest() {
		if (priority_map.empty()) { return -1; }
		auto it = begin(priority_map);
		auto priority = it->first;
		auto& events = it->second;
		auto it1 = begin(events);
		auto eventid = *it1;
		events.erase(it1);
		if (events.empty()) {
			priority_map.erase(it);
		}
		event_to_priority.erase(eventid);
		return eventid;
	}
};
	
static void run() {
}
}

namespace problem3 {
class Solution {
public:

	static pair<bool, pair<int, int>> rotate_sotable(const vector<int>& nums, int start, int len) {
		int rev_count = 0;
		int min_value = nums[start];
		int max_value = nums[start];
		for (int i = 1; i < len; i++) {
			min_value = min(min_value, nums[i + start]);
			max_value = max(max_value, nums[i + start]);
			if (nums[start + i - 1] <= nums[start + i]) {

			}
			else {
				if (rev_count > 0) {
					return { false, {min_value,max_value} };
				}
				rev_count++;
			}
		}
		if (rev_count == 0) { return { true, {min_value,max_value} }; }
		return { nums[start + len - 1] <= nums[start], {min_value,max_value} };
	}

	static bool check(const vector<int>& nums, int len) {
		const auto count = size(nums) / len;

		int prev_max = INT_MIN;
		for (int i = 0; i < count; i++) {
			const auto [res, min_max] = rotate_sotable(nums, i * len, len);
			if (!res) {
				return false;
			}
			const auto [cur_min, cur_max] = min_max;
			if (cur_min < prev_max) { return false; }
			prev_max = cur_max;
		}
		return true;
	}


	int sortableIntegers(vector<int>& nums) {
		const auto n = static_cast<int>(size(nums));
		if (n == 1) { return 1; }
		const auto limit = static_cast<int>(sqrt(n));
		int ans = 0;

		for (int i = 1; i <= limit; i++) {
			if (n % i == 0) {
				if (check(nums, i)) { ans += i; }
				const auto v = n / i;
				if (v != i) {
					if (check(nums, v)) { ans += v; }
				}
			}
		}

		return ans;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().sortableIntegers(nums) << endl;
}
static void run() {
	test(get_list_int("[2,3,4,1]"));
	test(get_list_int("[3,4,1,2]"));
	test(get_list_int("[1,2,3,4]"));
	test(get_list_int("[3,1,2]"));
	test(get_list_int("[7,6,5]"));
	test(get_list_int("[5,8]"));
}
}

namespace problem4 {
class Solution {
public:


	struct union_find {

		std::vector<size_t> parents_;
		std::vector<size_t> sizes_;

		union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
			for (size_t i = 0; i < n; i++) {
				parents_[i] = i;
			}
		}

		size_t root(size_t x) {
			if (x == parents_[x]) { return x; }
			parents_[x] = root(parents_[x]);
			return parents_[x];
		}

		bool same(size_t x, size_t y) {
			return root(x) == root(y);
		}

		void unite(size_t x, size_t y) {
			const auto rootx = root(x);
			const auto rooty = root(y);
			if (rootx == rooty) { return; }
			if (sizes_[rootx] < sizes_[rooty]) {
				parents_[rootx] = rooty;
				sizes_[rooty] += sizes_[rootx];
			}
			else {
				parents_[rooty] = rootx;
				sizes_[rootx] += sizes_[rooty];
			}
		}

		size_t size(size_t x) {
			return sizes_[root(x)];
		}

		bool is_root(size_t x) {
			return root(x) == x;
		}
	};


	static void dfs_set(const vector<vector<pair<int, int>>>& graph, int current, int prev, int parity, vector<int>& parities, vector<bool>& visited) {
		parities[current] = parity;
		for (auto&& [dest, cost] : graph[current]) {
			if (dest != prev && !visited[dest]) {
				visited[dest] = true;
				dfs_set(graph, dest, current, (parity + cost) % 2, parities, visited);
			}
		}
	}

	int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
		int ans = 0;

		union_find uf(n);
		vector<vector<pair<int, int>>> graph(n);
		vector<int> parities(n, -1);
		for (auto&& edge : edges) {
			const auto u = edge[0];
			const auto v = edge[1];
			const auto w = edge[2];
			if (uf.same(u, v)) {
				if (
					(w == 0 && parities[u] == parities[v]) ||
					(w == 1 && parities[u] != parities[v])
					) {
					ans++;
					graph[u].emplace_back(make_pair(v, w));
					graph[v].emplace_back(make_pair(u, w));
				}
			}
			else {
				if (parities[u] < 0 && parities[v] < 0) {
					if (w == 0) {
						parities[u] = parities[v] = 0;
					}
					else {
						parities[u] = 0;
						parities[v] = 1;
					}
				}
				else {

					int start_node = parities[u] >= 0 ? v : u;
					int start_parity = (parities[start_node] + w) % 2;
					if (parities[start_node] != start_parity) {
						vector<bool> visited(n);
						visited[u] = true;
						dfs_set(graph, start_node, -1, start_parity, parities, visited);
					}
				}

				ans++;
				uf.unite(u, v);
				graph[u].emplace_back(make_pair(v, w));
				graph[v].emplace_back(make_pair(u, w));
			}
		}


		return ans;
	}
};
static void test(int n, vector<vector<int>>&& edges) {
	cout << Solution().numberOfEdgesAdded(n, edges) << endl;
}
static void run() {
	test(3, get_matrix_int("["));
	test(3, get_matrix_int("[[0,1,1],[1,2,1],[0,2,1]]"));
	test(3, get_matrix_int("[[0,1,1],[1,2,1],[0,2,0]]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
