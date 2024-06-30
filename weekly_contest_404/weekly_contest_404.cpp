// weekly_contest_404.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


namespace problem1 {
class Solution {
public:

	static int get_max_height(int first, int second, int depth) {
		if (first < depth) {
			return depth - 1;
		}
		return get_max_height(second, first - depth, depth + 1);
	}

	int maxHeightOfTriangle(int red, int blue) {
		return max(get_max_height(red, blue, 0), get_max_height(blue,red, 0));
	}
};

void test(int red, int blue) {
	cout << Solution().maxHeightOfTriangle(red, blue) << endl;
}
void run() {
	test(2, 4);
	test(2, 1);
	test(1, 1);
	test(10, 1);
}
}
namespace problem2 {

class Solution {
public:
	static bool is_even(int n) {
		return n % 2 == 0;
	}
	int maximumLength(vector<int>& nums) {
		int even_count = 0;
		int odd_count = 0;
		vector<int> before(2);
		if (is_even(nums[0])) {
			even_count++;
			before[0] = 1;
		}
		else {
			odd_count++;
			before[1] = 1;
		}

		for (int i = 1; i < nums.size(); i++) {
			vector<int> current(2, 0);
			if (is_even(nums[i])) {
				even_count++;
				current[0] = max(before[1] + 1, before[0]);
				current[1] = before[1];
			}
			else {
				odd_count++;
				current[0] = before[0];
				current[1] = max(before[0] + 1, before[1]);
			}
			before = current;
		}

		return max(max(even_count, odd_count), max(before[0], before[1]));
	}
};
void test(vector<int>&& nums) {
	cout << Solution().maximumLength(nums) << endl;
}
void run() {
	test(get_list_int("[1,2,3,4]"));
	test(get_list_int("[1,2,1,1,2,1,2]"));
	test(get_list_int("[1,3]"));
}
}
namespace problem3 {

class Solution {
public:

	int maximumLength(vector<int>& nums, int k) {
		if (nums.size() < 2) {
			return 0;
		}
		vector<vector<int>> dp(k, vector<int>(k, 0));
		for (int i = 0; i < k; i++) {
			const int m = nums[0] % k;
			dp[m][i] = 1;
		}

		for (int i = 1; i < nums.size(); i++) {
			const int m = nums[i] % k;
			for (int j = 0; j < k; j++) {
				dp[m][j] = max(dp[j][m] + 1, dp[m][j]);
			}
		}

		int max_value = 2;//lower limit
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				max_value = max(max_value, dp[i][j]);
			}
		}

		return max_value;
	}
};
void test(vector<int>&& nums, int k) {
	cout << Solution().maximumLength(nums, k) << endl;
}
void run() {
	test(get_list_int("[1,2,3,4,5]"), 2);
	test(get_list_int("[8,2,8]"), 5);
	test(get_list_int("[2,10]"), 7);
	test(get_list_int("[1,1]"), 7);
	test(get_list_int("[1,1,1]"), 7);
	test(get_list_int("[1,4,2,3,1,4]"), 3);
}
}
namespace problem4 {

class Solution {
public:



	static int get_longest(const unordered_map<int, vector<int>>& graph, int start, int from) {
		int distance = 0;
		const auto it = graph.find(start);
		if (it != cend(graph)) {
			for (auto&& next : it->second) {
				if (next == from) { continue; }
				distance = max(distance, get_longest(graph, next, start) + 1);
			}
		}
		return distance;
	}

	static pair<int, int> get_radius_diameter(const vector<vector<int>>& edges) {
		unordered_map<int, vector<int>> graph;
		int max_vertex = 0;
		for (auto&& edge : edges) {
			graph[edge[0]].push_back(edge[1]);
			graph[edge[1]].push_back(edge[0]);
			max_vertex = max(max_vertex, edge[0]);
			max_vertex = max(max_vertex, edge[1]);
		}
		int radius = INT_MAX;
		int diameter = 0;
		for (int i = 0; i <= max_vertex; i++) {
			const int d = get_longest(graph, i, -1);
			radius = min(radius, d);
			diameter = max(diameter, d);
		}
		return {radius, diameter};
	}
	static int tle(const vector<vector<int>>& edges1,const vector<vector<int>>& edges2) {

		const auto [radius1, diameter1] = get_radius_diameter(edges1);
		const auto [radius2, diameter2] = get_radius_diameter(edges2);
		int ans = max(diameter1, diameter2);
		ans = max(ans, radius1 + radius2 + 1);
		return ans;
	}

	static pair<int, int> get_far(const unordered_map<int, vector<int>>& graph, int start, int from) {
		pair<int, int> currentmax{ 0, start };
		const auto it = graph.find(start);
		if (it != cend(graph)) {
			for (auto&& next : it->second) {
				if (next == from) { continue; }
				const auto r1 = get_far(graph, next, start);
				if (currentmax.first < r1.first + 1) {
					currentmax = { r1.first + 1 , r1.second };
				}
			}
		}
		return currentmax;
	}

	static int tree_diamiter(const vector<vector<int>>& edges) {
		unordered_map<int, vector<int>> graph;
		for (auto&& edge : edges) {
			graph[edge[0]].push_back(edge[1]);
			graph[edge[1]].push_back(edge[0]);
		}
		const auto p1 = get_far(graph, 0, -1);
		const auto p2 = get_far(graph, p1.second, -1);
		return p2.first;
	}

	int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
		const auto diameter1 = tree_diamiter(edges1);
		const auto diameter2 = tree_diamiter(edges2);
		const auto radius1 = (diameter1 + 1) / 2;
		const auto radius2 = (diameter2 + 1)/ 2;
		int ans = max(diameter1, diameter2);
		ans = max(ans, radius1 + radius2 + 1);
		return ans;
	}


};

void test(vector<vector<int>>&& edges1, vector<vector<int>>&& edges2) {
	cout << Solution().minimumDiameterAfterMerge(edges1, edges2) << endl;
}

void run() {
	test(get_matrix_int("[[0,1],[2,0],[3,2],[3,6],[8,7],[4,8],[5,4],[3,5],[3,9]]"), get_matrix_int("[[0,1],[0,2],[0,3]]"));
	test(get_matrix_int("[[0,1],[0,2],[0,3]]"), get_matrix_int("[[0,1]]"));
	test(get_matrix_int("[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]"), get_matrix_int("[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]"));
}
}



int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
}