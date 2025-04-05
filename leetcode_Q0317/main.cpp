#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
constexpr int INF = std::numeric_limits<int>::max();
class Solution {
public:
	static vector<int> djikstra(const std::vector<std::vector<int>>& graph, int s) {
		std::vector<int> costs(graph.size(), INF);
		struct point {
			int cost;
			int pos;
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
			constexpr int cost = 1;
			for (auto&& to : graph[current]) {
				if (costs[to] > cost + current_cost) {
					costs[to] = cost + current_cost;
					p_queue.push(point{ costs[to] , to });
				}
			}
		}
		return costs;
	}


    int shortestDistance(vector<vector<int>>& grid) {
		const auto n = size(grid);
		const auto m = size(grid.front());
		const vector<pair<int, int>> dirs{ {-1,0},{1,0},{0,-1},{0,1}, };
		vector<vector<int>> graph(n * m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				const int source = i * m + j;
				auto& node = graph[source];
				if (grid[i][j] == 0 || grid[i][j] == 1) {
					for (auto&& dir : dirs) {
						const auto y = i + dir.first;
						const auto x = j + dir.second;
						if (0 <= y && y < n && 0 <= x && x < m && grid[y][x] == 0) {
							node.emplace_back(y * m + x);
						}
					}
				}
			}
		}
		vector<int> total_costs(n * m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == 1) {
					const vector<int> costs = djikstra(graph, i * m + j);
					for (int k = 0; k < n * m; k++) {
						if (costs[k] < INF && total_costs[k] >=0) {
							total_costs[k] += costs[k];
						}
						else {
							total_costs[k] = -1;
						}
					}
				}
			}
		}

		int min_value = INT_MAX;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				const auto index = i * m + j;
				if (grid[i][j] == 0) {
					if (total_costs[index] >= 0) {
						min_value = min(min_value, total_costs[index]);
					}
				}
			}
		}
		if (min_value == INT_MAX) { return -1; }
		return min_value;
    }
};

void test(vector < vector<int>>&& grid) {
    cout << Solution().shortestDistance(grid) << endl;
}
int main() {
	test(get_matrix_int("[[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]"));
	test(get_matrix_int("[[1,0]]"));
	test(get_matrix_int("[[1]]"));
	return 0;
}