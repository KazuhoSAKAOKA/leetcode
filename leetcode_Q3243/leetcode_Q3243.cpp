// leetcode_Q3243.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

constexpr int INF = std::numeric_limits<int>::max();

class Solution {
public:

	static void bellman_ford(const vector<vector<int>>& edges, vector<int>& costs) {
		bool updated = true;
		while (updated) {
			updated = false;
			for (auto&& edge : edges) {
				const auto from = edge.front();
				const auto to = edge.back();
				if (costs[from] != INF && costs[to] > costs[from] + 1) {
					costs[to] = costs[from] + 1;
					updated = true;
				}
			}
		}
	}

    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
		vector<int> costs(n, INF);
		costs[0] = 0;
		vector<int> ans;

		vector<vector<int>> edges;
		edges.reserve(n + size(queries));
		for (int i = 0; i < n - 1; i++) {
			edges.emplace_back(vector<int>{i, i + 1});
		}

		ans.reserve(size(queries));
		for (auto&& query : queries) {
			edges.emplace_back(vector<int>{query.front(), query.back()});
			bellman_ford(edges, costs);
			ans.emplace_back(costs[n - 1]);
		}
		return ans;
    }
};

void test(int n, vector<vector<int>>&& queries) {

    output(Solution().shortestDistanceAfterQueries(n, queries));
}
int main()
{
    test(5, get_matrix_int("[[2,4],[0,2],[0,4]]"));
    test(4, get_matrix_int("[[0,3],[0,2]]"));
    return 0;
}