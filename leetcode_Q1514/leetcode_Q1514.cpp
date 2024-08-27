// leetcode_Q1514.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
	
	static double bellman_ford(size_t n, const vector<vector<int>>& edges, const vector<double>& prob, int s, int e) {
		constexpr double INF = 0.0;
		vector<double> costs(n, INF);
		costs[s] = 1.0;
		bool updated = true;
		auto check = [&](int from, int to, double prob) ->bool {
			if (costs[from] != INF && costs[to] < costs[from] * prob) {
				costs[to] = costs[from] * prob;
				return true;
			}
			return false;
			};

		while (updated) {
			updated = false;
			for (size_t i = 0; i < size(edges); i++) {
				const auto& edge = edges[i];
				updated |= check(edge[0], edge[1], prob[i]);
				updated |= check(edge[1], edge[0], prob[i]);
			}
		}
		return costs[e];
	}

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
		return bellman_ford(n, edges, succProb, start_node, end_node);
    }
};

void test(int n, vector<vector<int>>&& edges, vector<double>&& succProb, int start_node, int end_node) {
    cout << Solution().maxProbability(n, edges, succProb, start_node, end_node) << endl;
}

int main()
{
    test(3, get_matrix_int("[[0,1],[1,2],[0,2]]"), get_list_double("[0.5,0.5,0.2]"), 0, 2);
    test(3, get_matrix_int("[[0,1],[1,2],[0,2]]"), get_list_double("[0.5,0.5,0.3]"), 0, 2);
    test(3, get_matrix_int("[[0,1]]"), get_list_double("[0.5]"), 0, 2);

    return 0;
}