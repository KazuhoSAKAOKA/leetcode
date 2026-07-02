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
	static T djikstra(const vector<vector<int>>& grid) {

		const long long h = size(grid);
		const long long w = size(grid[0]);
		const vector<pair<long long, long long>> nexts{
			{-1,0},{1,0},{0,-1}, {0,1},
		};
		std::vector<T> costs(h * w, std::numeric_limits<T>::max());
		struct point {
			T cost;
			long long pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		costs[0] = grid[0][0];
		p_queue.push(point{ costs[0], 0 });
		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			const long long y = current / w;
			const long long x = current % w;
			for (auto&& [dy,dx] : nexts) {
				const long long ny = y + dy;
				const long long nx = x + dx;
				if (0 <= ny && ny < h && 0 <= nx && nx < w) {
					const auto cost = grid[ny][nx];
					const auto to = ny * w + nx;
					if (costs[to] > cost + current_cost) {
						costs[to] = cost + current_cost;
						p_queue.push(point{ costs[to] , to });
					}
				}
			}
		}
		return costs[h * w - 1];
	}

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
		const auto cost = djikstra<long long>(grid);
		return cost < static_cast<long long>(health);
    }
};

static void test(vector<vector<int>>&& grid, int health) {
    cout << Solution().findSafeWalk(grid, health) << endl;
}
int main() {
    test(get_matrix_int("[[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]"), 1);
    test(get_matrix_int("[[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]]"), 3);
    test(get_matrix_int("[[1,1,1],[1,0,1],[1,1,1]]"), 5);
    return 0;
}
