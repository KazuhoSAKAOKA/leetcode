// leetcode_Q2093.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

	static int djikstra(const vector<vector<pair<int,int>>>& graph, int s, int e, int discounts) {
		vector<vector<int>> costs(graph.size(), vector<int>(discounts + 1, INT_MAX));
		struct point {
			int cost;
			int discounts;
			int pos;
			bool operator > (const point& other) const {
				return cost > other.cost;
			}
		};
		priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
		p_queue.push(point{ 0, discounts, s });
		costs[s][discounts] = 0;
		while (!p_queue.empty()) {
			const point current_point = p_queue.top();
			p_queue.pop();
			if (costs[current_point.pos][current_point.discounts] < current_point.cost) { continue; }
			for (auto&& [to, cost] : graph[current_point.pos]) {
				if (costs[to][current_point.discounts] > cost + current_point.cost) {
					costs[to][current_point.discounts] = cost + current_point.cost;
					p_queue.push(point{ costs[to][current_point.discounts] ,current_point.discounts, to });
				}
				if (current_point.discounts > 0 && costs[to][current_point.discounts - 1] > cost / 2 + current_point.cost) {
					costs[to][current_point.discounts - 1] = cost / 2 + current_point.cost;
					p_queue.push(point{ costs[to][current_point.discounts - 1] ,current_point.discounts - 1, to });
				}
			}
		}

		int min_cost = INT_MAX;
		for (auto&& cost : costs[e]) {
			min_cost = min(min_cost, cost);
		}

		return min_cost;
	}

    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
        for (auto&& highway : highways) {
            graph[highway[0]].push_back({ highway[1], highway[2] });
            graph[highway[1]].push_back({ highway[0], highway[2] });
        }
		auto ans = djikstra(graph, 0, n - 1, discounts);
		if (ans == INT_MAX) {
			return -1;
		}
		else {
			return ans;
		}
    }
};

void test(int n, vector<vector<int>>&& highways, int disconts) {
    cout << Solution().minimumCost(n, highways, disconts) << endl;
}


int main()
{
    test(5, get_matrix_int("[[0,1,4],[2,1,3],[1,4,11],[3,2,3],[3,4,2]]"), 1);
    test(4, get_matrix_int("[[1,3,17],[1,2,7],[3,2,5],[0,1,6],[3,0,20]]"), 20);
    test(4, get_matrix_int("[[0,1,3],[2,3,2]]"), 0);
    return 0;
}