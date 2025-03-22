#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

	static int djikstra(const std::vector<std::vector<pair<int,int>>>& graph, size_t s, const vector<int>& marked) {
		std::vector<int> costs(graph.size(), std::numeric_limits<int>::max());
		struct point {
			int cost;
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
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			for (auto&& [cost, to] : graph[current]) {
				if (costs[to] > cost + current_cost) {
					costs[to] = cost + current_cost;
					p_queue.push(point{ costs[to] , static_cast<size_t>(to) });
				}
			}
		}

		int min_distance = std::numeric_limits<int>::max();
		for (auto&& mark : marked) {
			min_distance = min(min_distance, costs[mark]);
		}

		return min_distance;
	}


    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
		vector<vector<pair<int, int>>> graph(n);
		for (auto&& edge : edges) {
			graph[edge[0]].emplace_back(edge[2], edge[1]);
		}
		const auto ans = djikstra(graph, s, marked);
		if (ans == std::numeric_limits<int>::max()) {
			return -1;
		}
		return ans;
	}
};
void test(int n, vector<vector<int>>&& edges, int s, vector<int>&& marked) {
    cout << Solution().minimumDistance(n, edges, s, marked) << endl;
}

int main() {
    test(4, get_matrix_int("[[0,1,1],[1,2,3],[2,3,2],[0,3,4]]"), 0, get_list_int("[2,3]"));
    test(5, get_matrix_int("[[0,1,2],[0,2,4],[1,3,1],[2,3,3],[3,4,2]]"), 1, get_list_int("[0,4]"));
    test(4, get_matrix_int("[[0,1,1],[1,2,3],[2,3,2]]"), 3, get_list_int("[0,1]"));

	return 0;
}