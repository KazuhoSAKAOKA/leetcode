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
class Solution {
public:
	static vector<int> djikstra(const std::vector<int>& coins, int max_jump) {
		const int n = size(coins);
		std::vector<int> costs(n, numeric_limits<int>::max());
		struct point {
			int cost;
			int pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ coins[0], 0 });
		costs[0] = coins[0];

		while (!p_queue.empty()) {
			const auto [current_cost, current] = p_queue.top();
			p_queue.pop();
			if (costs[current] < current_cost) { continue; }
			for (int i = 1; i <= min(max_jump, n - current - 1); i++) {
				const int index = i + current;
				if (coins[index] >= 0) {
					if (costs[index] > coins[index] + current_cost) {
						costs[index] = coins[index] + current_cost;
						p_queue.push(point{ costs[index] , index });
					}
				}
			}
		}
		return costs;
	}

	static void dfs(const std::vector<int>& coins, const vector<int>& costs, int max_jump, int index, vector<int>& cur_route, vector<vector<int>>& anss) {
		if (index == 0) {
			anss.push_back(vector<int>(crbegin(cur_route), crend(cur_route)));
			return;
		}

		const auto cur_cost = costs[index] - coins[index];
		for (int i = index - 1; i >= max(0, index - max_jump); i--) {
			if (costs[i] == cur_cost) {
				cur_route.push_back(i + 1);
				dfs(coins, costs, max_jump, i, cur_route, anss);
				cur_route.pop_back();
			}
		}
	}

    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
		const int n = size(coins);
		const auto costs = djikstra(coins, maxJump);
		if (costs.back() == numeric_limits<int>::max()) { return{}; }
		vector<vector<int>> anss;
		vector<int> cur_route{ n };
		dfs(coins, costs, maxJump, n - 1, cur_route, anss);
		return *min_element(cbegin(anss), cend(anss));
    }
};

static void test(vector<int>&& coins, int maxJump) {
    output(Solution().cheapestJump(coins, maxJump));
}
int main() {
	test(get_list_int("[33,90,57,39,42,45,29,90,81,87,88,37,58,97,80,2,77,64,82,41,2,33,34,95,85,77,92,3,8,15,71,84,58,65,46,48,3,74,4,83,23,12,15,77,33,65,17,86,21,62,71,55,80,63,75,55,11,34,-1,64,81,18,77,82,8,12,14,6,46,39,71,14,6,46,89,37,88,70,88,33,89,92,60,0,78,10,88,99,20]"), 74);
	test(get_list_int("[0,0,0,0,0,0]"), 3);

	test(get_list_int("[1,2,4,-1,2]"), 2);
	test(get_list_int("[1,2,4,-1,2]"), 1);
	return 0;
}