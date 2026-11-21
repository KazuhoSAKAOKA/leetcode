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
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

namespace problem1 {
class Solution {
public:

	static void dfs1(const vector<vector<size_t>>& graph, const string& s, size_t node, size_t parent, vector<size_t>& parent_alphabets, vector<size_t>& new_parents) {

		if (parent_alphabets[s[node] - 'a'] != -1) {
			new_parents[node] = parent_alphabets[s[node] - 'a'];
		}
		else {
			new_parents[node] = parent;
		}

		const size_t old_val = parent_alphabets[s[node] - 'a'];
		parent_alphabets[s[node] - 'a'] = node;
		for (auto&& child : graph[node]) {
			dfs1(graph, s, child, node, parent_alphabets, new_parents);
		}
		parent_alphabets[s[node] - 'a'] = old_val;

	}
	static void dfs2(const vector<vector<size_t>>& graph, size_t node, vector<int>& ans) {

		int count = 1;
		for (auto&& child : graph[node]) {
			dfs2(graph, child, ans);
			count += ans[child];
		}
		ans[node] = count;
	}



	vector<int> findSubtreeSizes(vector<int>& parent, string s) {
		const auto n = size(parent);
		vector<vector<size_t>> graph(n);
		for (size_t i = 1; i < n; i++) {
			graph[parent[i]].push_back(i);
		}
		vector<size_t> parent_alphabets(26, -1);
		vector<size_t> new_parents(n);
		dfs1(graph, s, 0, -1, parent_alphabets, new_parents);

		vector<vector<size_t>> graph2(n);
		for (size_t i = 1; i < n; i++) {
			graph2[new_parents[i]].push_back(i);
		}

		vector<int> ans(n);
		dfs2(graph2, 0, ans);
		return ans;
	}
};
static void test(vector<int>&& parent, string&& s) {
	output(Solution().findSubtreeSizes(parent, s));
}
static void run() {
	test(get_list_int("[-1,10,0,12,10,18,11,12,2,3,2,2,2,0,4,11,4,2,0]"), "babadabbdabcbaceeda");
	test(get_list_int("[-1,0,0,1,1,1]"), "abaabc");
	test(get_list_int("[-1,0,4,0,1]"), "abbba");
	//test(get_list_int(""), "");
}
}


int main() {
	problem1::run();
	return 0;
}
