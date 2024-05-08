// leetcode_Q2473.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


class Solution {
public:
	using cost_and_dest = pair<int, int>;

	static unordered_map<int, long long> djikstra(const std::vector<std::vector<cost_and_dest>>& graph, int s) {
		
		unordered_map<int, long long> costs;

		struct point {
			long long cost;
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
			for (auto&& [cost, dest] : graph[current]) {
				const auto it = costs.find(dest);
				if (it == cend(costs) || it->second > cost + current_cost) {
					costs[dest] = cost + current_cost;
					p_queue.push(point{ costs[dest] , dest });
				}
			}
		}
		return costs;
	}

    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
		vector<long long> ans(n, 0);

		vector<vector<cost_and_dest>> graph(n, vector<cost_and_dest>());

		for (auto&& road : roads) {
			graph[road[0] - 1].emplace_back(cost_and_dest{ road[2], road[1] - 1 });
			graph[road[1] - 1].emplace_back(cost_and_dest{ road[2], road[0] - 1 });
		}

		for(int i = 0; i < n; i++){
			const auto costs = djikstra(graph, i);
			long long min_value = LLONG_MAX;
			for (auto&& [dest, cost] : costs) {
				min_value = min(min_value, cost * (1 + k) + static_cast<long long>(appleCost[dest]));
			}
			ans[i] = static_cast<long long>(min_value);
		}
		return ans;
    }
};

void test(int n, vector<vector<int>>&& roads, vector<int>&& appleCost, int k) {
    const auto ans = Solution().minCost(n, roads, appleCost, k);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
	test(8, { { 8,3,193 }, { 4,1,890 }, { 8,2,714 }, { 7,2,654 }, { 6,1,147 } }, { 87310,86029,37141,89780,2747,39709,38302,21966, }, 63);

    test(4, { {1,2,4,},{2,3,2,},{2,4,5,},{3,4,1,},{1,3,4,}, }, { 56,42,102,301, }, 2);
    test(3, { {1,2,5,},{2,3,1,},{3,1,2,},}, { 2,3,1, }, 3);
}