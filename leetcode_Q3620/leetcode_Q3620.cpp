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

class Solution {
public:

	template<typename T>
	static T djikstra(const std::vector<std::vector<pair<long long, size_t>>>& graph, size_t s, size_t e, long long limit) {
		std::vector<T> costs(graph.size(), std::numeric_limits<T>::max());
		struct point {
			T cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		costs[s] = 0;
		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			if (current == e) {
				return current_cost;
			}
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			for (auto&& [cost, to] : graph[current]) {
				if (cost < limit) { continue; }
				if (costs[to] > cost + current_cost) {
					costs[to] = cost + current_cost;
					p_queue.push(point{ costs[to] , to });
				}
			}
		}
		return costs[e];
	}
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
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        const auto n = size(online);
        vector<vector<pair<long long, size_t>>> graph(n);
		long long min_cost = INT_MAX;
		long long max_cost = 0;
        for (auto&& edge : edges) {
            const auto u = static_cast<size_t>(edge[0]);
            const auto v = static_cast<size_t>(edge[1]);
            if (online[u] && online[v]) {
				const auto cost = static_cast<long long>(edge[2]);
                graph[u].push_back({ cost, v, });
				min_cost = min(min_cost, cost);
				max_cost = max(max_cost, cost);
            }
        }

		long long ok = min_cost;
		long long ng = max_cost + 1;

		auto check = [&](long long v)->bool {
			return djikstra<long long>(graph, 0, n - 1, v) <= k;
			};
		if (!check(ok)) {
			return -1;
		}

		const auto ans = binary_search_meguru<long long>(ok, ng, check);
		return static_cast<int>(ans);
    }
};

static void test(vector<vector<int>>&& edges, vector<bool>&& online, long long k) {
    cout << Solution().findMaxPathScore(edges, online, k) << endl;
}

int main() {
    test(get_matrix_int("[[0,1,5],[1,3,10],[0,2,3],[2,3,4]]"), get_list_bool("[true,true,true,true]"), 10);
	test(get_matrix_int("[[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]]"), get_list_bool("[true,true,true,false,true]"), 12);
	return 0;
}