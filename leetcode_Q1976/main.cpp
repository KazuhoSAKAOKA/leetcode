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
constexpr size_t MODULO = 1e9 + 7;

class Solution {
public:

	static vector<size_t> bellman_ford(int n, const std::vector<vector<size_t>>& edges, int s) {
		constexpr size_t INF = std::numeric_limits<size_t>::max();
		vector<size_t> costs(n, INF);
		costs[s] = 0;
		bool updated = true;
		while (updated) {
			updated = false;
			for (auto&& edge : edges) {
				const auto from = edge[0];
				const auto to = edge[1];
				const auto cost = edge[2];
				const auto cur_cost = costs[from] + cost;
				if (costs[from] != INF && costs[to] > cur_cost) {
					costs[to] = cur_cost;
					updated = true;
				}
			}
		}

		return costs;
	}

	static void bfs(const vector<vector<pair<int, int>>>& graph, const vector<size_t>& costs, int goal, vector<size_t>& ways) {

		auto compare = [&](int a, int b)->bool {return costs[a] < costs[b]; };
		priority_queue<int, vector<int>, decltype(compare)> pq(compare);
		ways[goal] = 1;
		pq.push(goal);
		vector<bool> visited(size(graph));

		while (!pq.empty()) {
			const auto current = pq.top();
			pq.pop();
			if (!visited[current]) {
				visited[current] = true;
				for (auto&& [to, cost] : graph[current]) {
					if (costs[current] - costs[to] == cost) {
						ways[to] += ways[current];
						ways[to] %= MODULO;
						pq.push(to);
					}
				}
			}
		}
	}

    int countPaths(int n, vector<vector<int>>& roads) {

		vector<vector<size_t>> roads2;
		roads2.reserve((size(roads) * 2));
		for (auto&& road : roads) {
			size_t u = static_cast<size_t>(road[0]);
			size_t v = static_cast<size_t>(road[1]);
			size_t cost = static_cast<size_t>(road[2]);
			roads2.emplace_back(vector<size_t>{u,v,cost});
			roads2.emplace_back(vector<size_t>{v,u,cost});
		}
		const vector<size_t> costs = bellman_ford(n, roads2, 0);
		vector<vector<pair<int,int>>> graph(n);
		for (auto&& edge : roads) {
			const auto u = edge[0];
			const auto v = edge[1];
			const auto cost = edge[2];
			graph[u].emplace_back(make_pair(v, cost));
			graph[v].emplace_back(make_pair(u, cost));
		}
		vector<size_t> ways(n, 0);
		ways.back() = 1;
		bfs(graph, costs, n - 1, ways);
		return static_cast<int>(ways[0]);
    }
};
void test(int n, vector<vector<int>>&& roads) {
    cout << Solution().countPaths(n, roads) << endl;
}
int main() {
	test(2, get_matrix_int("[[1,0,10]]"));
	test(7, get_matrix_int("[[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]"));
    return 0;
}