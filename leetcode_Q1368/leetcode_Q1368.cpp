// leetcode_Q1368.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
	struct outbound_edge {
		int cost;
		size_t to;
	};

	static int djikstra(const std::vector<std::vector<outbound_edge>>& graph, size_t s, size_t e) {
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
					p_queue.push(point{ costs[to] , to });
				}
			}
		}
		return costs[e];
	}
    int minCost(vector<vector<int>>& grid) {
		const size_t H = size(grid);
		const size_t W = size(grid.front());
		const size_t N = H * W;
		vector<vector<outbound_edge>> graph(N);
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				const auto n = y * W + x;
				auto& nodes = graph[n];
				if (x < W - 1) {
					nodes.emplace_back(outbound_edge{ grid[y][x] == 1 ? 0 : 1, y * W + (x + 1) });
				}
				if (x > 0) {
					nodes.emplace_back(outbound_edge{ grid[y][x] == 2 ? 0 : 1, y * W + (x - 1) });
				}
				if (y < H - 1) {
					nodes.emplace_back(outbound_edge{ grid[y][x] == 3 ? 0 : 1, (y + 1) * W + x });
				}
				if (y > 0) {
					nodes.emplace_back(outbound_edge{ grid[y][x] == 4 ? 0 : 1, (y - 1) * W + x });
				}
			}
		}

		const auto ans = djikstra(graph, 0, N - 1);
		return ans;
    }
};

void test(vector<vector<int>>&& grid) {
	cout << Solution().minCost(grid) << endl;
}
int main()
{
	test(get_matrix_int("[[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]"));
	test(get_matrix_int("[[1,1,3],[3,2,2],[1,1,4]]"));
	test(get_matrix_int("[[1,2],[4,3]]"));

	return 0;
}