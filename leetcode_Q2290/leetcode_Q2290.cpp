// leetcode_Q2290.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

	static vector<size_t> get_connects(const std::vector<std::vector<int>>& grid, size_t p) {
		const size_t H = size(grid);
		const size_t W = size(grid.front());
		vector<size_t> nexts;
		int x = p % W;
		int y = p / W;
		if (x > 0) {
			nexts.emplace_back(p - 1);
		}
		if (x < W - 1) {
			nexts.emplace_back(p + 1);
		}
		if (y > 0) {
			nexts.emplace_back(p - W);
		}
		if (y < H - 1) {
			nexts.emplace_back(p + W);
		}
		return nexts;
	}

	static int djikstra(const std::vector<std::vector<int>>& grid) {
		const size_t H = size(grid);
		const size_t W = size(grid.front());
		std::vector<int> costs(H * W, std::numeric_limits<int>::max());

		struct point {
			int cost;
			size_t pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, 0 });
		costs[0] = 0;
		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			const auto nexts = get_connects(grid, current);
			for (auto&& to : nexts) {
				const auto cost = grid[to / W][to % W] == 0 ? 0 : 1;
				if (costs[to] > cost + current_cost) {
					costs[to] = cost + current_cost;
					p_queue.push(point{ costs[to] , to });
				}
			}
		}
		return costs[W * H - 1];
	}
    int minimumObstacles(vector<vector<int>>& grid) {
		return djikstra(grid);
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().minimumObstacles(grid) << endl;
}

int main()
{
	test(get_matrix_int("[[0,1,1],[1,1,0],[1,1,0]]"));
	test(get_matrix_int("[[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]"));
	return 0;
}
