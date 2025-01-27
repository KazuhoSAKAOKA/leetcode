// leetcode_Q1462.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

constexpr auto INF = std::numeric_limits<int>::max();

static void bellman_ford(const std::vector<vector<int>>& edges, size_t s, vector<int>& costs) {
	costs[s] = 0;
	size_t loop_counter = 0;
	bool updated = true;
	while (updated) {
		updated = false;
		for (auto&& edge : edges) {
			const auto from = edge.front();
			const auto to = edge.back();
			if (costs[from] != INF && costs[to] > costs[from]) {
				costs[to] = costs[from];
				updated = true;
			}
		}
		loop_counter++;
	}

}
class Solution {
public:
	vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
		vector<vector<int>> costs_list(numCourses, vector<int>(numCourses, INF));
		
		for (int i = 0; i < numCourses; i++) {
			bellman_ford(prerequisites, i, costs_list[i]);
		}

		vector<bool> ans(size(queries));
		for (int i = 0; i < size(queries); i++) {
			const auto u = queries[i].front();
			const auto v = queries[i].back();
			ans[i] = costs_list[u][v] != INF;
		}
		return ans;
	}
};

void test(int numCourses, vector<vector<int>>&& prerequisites, vector<vector<int>>&& queries) {
	output(Solution().checkIfPrerequisite(numCourses, prerequisites, queries));
}
int main()
{
	test(2, get_matrix_int("[[1,0]]"), get_matrix_int("[[0,1],[1,0]]"));
	test(2, get_matrix_int("[]"), get_matrix_int("[[0,1],[1,0]]"));
	test(3, get_matrix_int("[[1,2],[1,0],[2,0]]"), get_matrix_int("[[1,0],[1,2]]"));
	return 0;
}