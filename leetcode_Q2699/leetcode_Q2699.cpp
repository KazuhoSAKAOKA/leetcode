// leetcode_Q2699.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cassert>
#include "./../utility/leetcode_testcase_helper.h"


using namespace std;
class Solution {
public:
	struct path {
		size_t destination;
		long long cost;
	};
	static pair<long long, vector<size_t>> djikstra(const std::vector<std::vector<path>>& graph, size_t s, size_t e) {
		std::vector<pair<long long, size_t>> costs(graph.size(), { std::numeric_limits<long long>::max(), static_cast<size_t>(-1) });
		struct point {
			long long cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, s });
		costs[s] = { 0, s };
		while (!p_queue.empty()) {
			const point current = p_queue.top();
			p_queue.pop();
			if (costs[current.pos].first < current.cost) { continue; }
			for (auto&& p : graph[current.pos]) {
				if (costs[p.destination].first > p.cost + current.cost) {
					costs[p.destination] = { p.cost + current.cost , current.pos };
					p_queue.push(point{ costs[p.destination].first , p.destination });
				}
			}
		}
		if (costs[e].first == std::numeric_limits<long long>::max()) {
			return { std::numeric_limits<long long>::max(), vector<size_t>() };
		}
		vector<size_t> rev_route;
		size_t route_pos = e;
		rev_route.emplace_back(e);
		while (route_pos != s) {
			rev_route.emplace_back(costs[route_pos].second);
			route_pos = costs[route_pos].second;
		}

		return { costs[e].first, vector<size_t>(crbegin(rev_route), crend(rev_route)) };
	}

	vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
		vector<vector<path>> graph(n);
		vector<size_t> minus_edges;
		map<pair<size_t, size_t>, size_t> minus_edge_path_map;
		for (size_t i = 0; i < size(edges); i++) {
			const size_t u = static_cast<size_t>(min(edges[i][0], edges[i][1]));
			const size_t v = static_cast<size_t>(max(edges[i][0], edges[i][1]));
			if (edges[i][2] < 0) {
				minus_edges.emplace_back(i);
				minus_edge_path_map[{ u, v }] = i;
			}
			else {
				graph[u].emplace_back(path{ v ,edges[i][2] });
				graph[v].emplace_back(path{ u ,edges[i][2] });
			}
		}

		const auto minus_ignore_cost = djikstra(graph, source, destination);
		if (minus_ignore_cost.first < target) {
			return vector<vector<int>>();
		}

		vector<vector<int>> answer_edges(edges);
		if (minus_ignore_cost.first == target) {
			for (auto&& index : minus_edges) {
				answer_edges[index][2] = target + 1;
			}
			return answer_edges;
		}

		vector<vector<path>> work_graph(graph);
		for (auto&& index : minus_edges) {
			work_graph[edges[index][0]].emplace_back(path{ static_cast<size_t>(edges[index][1]) ,1 });
			work_graph[edges[index][1]].emplace_back(path{ static_cast<size_t>(edges[index][0]) ,1 });
		}
		const auto one_temp_cost_graph = djikstra(work_graph, source, destination);
		if (target < one_temp_cost_graph.first) {
			return vector<vector<int>>();
		}
		if (target == one_temp_cost_graph.first) {
			for (auto&& index : minus_edges) {
				answer_edges[index][2] = 1;
			}
			return answer_edges;
		}


		vector<vector<path>> work_graph2(graph);
		constexpr size_t MODCOSTTAG = numeric_limits<int>::max();
		for (auto&& index : minus_edges) {
			work_graph2[edges[index][0]].emplace_back(path{ static_cast<size_t>(edges[index][1]) ,MODCOSTTAG });
			work_graph2[edges[index][1]].emplace_back(path{ static_cast<size_t>(edges[index][0]) ,MODCOSTTAG });
		}

		for (auto&& index : minus_edges) {
			answer_edges[index][2] = target + 1;
		}
		const auto working_cost_route = djikstra(work_graph2, source, destination);
		const auto count_of_minus_routes = working_cost_route.first / MODCOSTTAG;
		if (count_of_minus_routes == 0) {
			const auto& current_route = one_temp_cost_graph.second;
			size_t before = static_cast<size_t>(source);
			map<size_t, size_t> mod_index_map;
			for (size_t i = 1; i < size(current_route); i++) {
				const pair<size_t, size_t> path_tag = { min(before, current_route[i]), max(before, current_route[i]) };
				const auto it = minus_edge_path_map.find(path_tag);
				if (it != cend(minus_edge_path_map)) {
					mod_index_map[before] = it->second;
				}
				before = current_route[i];
			}

			const auto count_of_minus_routes2 = size(mod_index_map);
			size_t current_count = 0;
			size_t current_cost = one_temp_cost_graph.first;
			for (auto&& [route_index, edge_index] : mod_index_map) {
				current_count++;
				if (current_count == count_of_minus_routes2) {
					answer_edges[edge_index][2] = static_cast<int>(target - current_cost);
				}
				else {
					auto& target_edge = answer_edges[edge_index];
					const size_t u = current_route[route_index];
					const size_t v = current_route[route_index + 1];
					const auto cost2 = djikstra(graph, source, v).first;
					if (cost2 == numeric_limits<long long>::max()) {
						answer_edges[edge_index][2] = 1;
					}
					else {
						const auto cost1 = djikstra(work_graph, source, u).first;
						answer_edges[edge_index][2] = cost2 - cost1;
					}
					graph[edges[edge_index][0]].emplace_back(path{ static_cast<size_t>(edges[edge_index][1]) ,answer_edges[edge_index][2] });
					graph[edges[edge_index][1]].emplace_back(path{ static_cast<size_t>(edges[edge_index][0]) ,answer_edges[edge_index][2] });
				}
			}
		}
		else {
			size_t current_minus_route = 0;
			const auto& current_route = working_cost_route.second;
			size_t current_cost = working_cost_route.first;
			size_t before = static_cast<size_t>(source);
			for (size_t i = 1; i < size(current_route); i++) {
				const pair<size_t, size_t> path_tag = { min(before, current_route[i]), max(before, current_route[i]) };
				const auto it = minus_edge_path_map.find(path_tag);
				if (it != cend(minus_edge_path_map)) {
					current_minus_route++;
					const auto target_index = it->second;
					if (current_minus_route == count_of_minus_routes) {
						current_cost -= MODCOSTTAG;
						answer_edges[target_index][2] = static_cast<int>(target - current_cost);
						break;
					}
					else {
						current_cost -= MODCOSTTAG;
						current_cost++;
						answer_edges[target_index][2] = 1;
					}
				}
				before = current_route[i];
			}
		}
		return answer_edges;
	}
};

void test(int n, vector<vector<int>>&& edges, int source, int destination, int target) {
    const auto ans = Solution().modifiedGraphEdges(n, edges, source, destination, target);
    cout << "------" << endl;
    for (auto&& values : ans) {
        for (auto&& value : values) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
	test(5, get_matrix_int("[[0,2,-1],[1,3,10],[0,1,7],[0,4,10],[3,2,-1],[4,2,5]]"), 0, 3, 6);
	test(5, get_matrix_int("[[1,3,10],[4,2,-1],[0,3,7],[4,0,7],[3,2,-1],[1,4,5],[2,0,8],[1,0,3],[1,2,5]]"), 3, 4, 11);
	test(5, get_matrix_int("[[1,4,1],[2,4,-1],[3,0,2],[0,4,-1],[1,3,10],[1,0,10]]"), 0, 2, 15);
	test(5, get_matrix_int("[[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]]"), 0, 1, 5);
    test(3, get_matrix_int("[[0,1,-1],[0,2,5]]"), 0, 2, 6);
    test(4, get_matrix_int("[[1,0,4],[1,2,3],[2,3,5],[0,3,-1]]"), 0, 2, 6);
    return 0;
}