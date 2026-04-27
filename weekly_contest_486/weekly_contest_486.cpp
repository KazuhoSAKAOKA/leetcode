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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
	int minimumPrefixLength(vector<int>& nums) {
		const int n = size(nums);
		int index = n - 2;
		while (0 <= index && nums[index] < nums[index + 1]) {
			index--;
		}
		return index + 1;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().minimumPrefixLength(nums) << endl;
}
static void run() {
	test(get_list_int("[1,-1,2,3,3,4,5]"));
	test(get_list_int("[4,3,-2,-5]"));
	test(get_list_int("[1,2,3,4]"));
}
}

namespace problem2 {
class Solution {
public:
	vector<int> rotateElements(vector<int>& nums, int k) {
		if (k == 0) { return nums; }
		const auto n = size(nums);
		vector<int> nn_elements;
		nn_elements.reserve(n);
		for (int i = 0; i < n; i++) {
			if (nums[i] >= 0) {
				nn_elements.emplace_back(i);
			}
		}
		const int n1 = size(nn_elements);
		if (n1 < 2) { return nums; }
		vector<int> ans(nums);
		
		for (int i = 0; i < n1; i++) {
			int target_index = i - k;
			if (target_index < 0) {
				target_index = (n1 - (abs(target_index) % n1)) % n1;
			}
			ans[nn_elements[target_index]] = nums[nn_elements[i]];
		}
		return ans;
	}
};
static void test(vector<int>&& nums, int k) {
	output(Solution().rotateElements(nums, k));
}
static void run() {
	test(get_list_int("[1,-2,3,-4]"), 3);
	test(get_list_int("[-3,-2,7]"), 1);
	test(get_list_int("[5,4,-9,6]"), 2);
}
}

namespace problem3 {
class Solution {
public:
	static void dfs(const vector<vector<int>>& graph, int current, int from, long long current_distance, vector<long long>& distances) {
		distances[current] = current_distance;
		for (auto&& next : graph[current]) {
			if (next != from) {
				dfs(graph, next, current, current_distance + 1, distances);
			}
		}
	}

	static bool is_pythagorean_triplet(long long a, long long b, long long c) {
		vector<long long> temp{ a,b,c };
		sort(begin(temp), end(temp));
		return temp[0] * temp[0] + temp[1] * temp[1] == temp[2] * temp[2];
	}

	static int dfs2(const vector<vector<int>>& graph, int current, int from, long long current_distance, vector<long long>& distances, const vector<long long>& distances1, const vector<long long>& distances2) {
		distances[current] = current_distance;
		int count = 0;
		if (is_pythagorean_triplet(current_distance, distances1[current], distances2[current])) {
			count++;
		}

		for (auto&& next : graph[current]) {
			if (next != from) {
				count += dfs2(graph, next, current, current_distance + 1, distances, distances1, distances2);
			}
		}
		return count;
	}


	int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
		vector<vector<int>> graph(n);
		for (auto&& edge : edges) {
			graph[edge[0]].emplace_back(edge[1]);
			graph[edge[1]].emplace_back(edge[0]);
		}
		vector<long long> distances_x(n);
		vector<long long> distances_y(n);
		vector<long long> distances_z(n);
		dfs(graph, x, -1, 0, distances_x);
		dfs(graph, y, -1, 0, distances_y);
		return dfs2(graph, z, -1, 0, distances_z, distances_x, distances_y);
	}
};
static void test(int n, vector<vector<int>>&& edges, int x, int y, int z) {
	cout << Solution().specialNodes(n, edges, x, y, z) << endl;
}
static void run() {
	test(4, get_matrix_int("[[0,1],[0,2],[0,3]]"), 1, 2, 3);
	test(4, get_matrix_int("[[0,1],[1,2],[2,3]]"), 0, 3, 2);
	test(4, get_matrix_int("[[0,1],[1,2],[1,3]]"), 1, 3, 0);
}
}

namespace problem4 {
class Solution {
public:

	static long long func(long long m, unordered_map<long long, long long>& memo) {
		if (m == 0) { return 1LL; }
		auto it = memo.find(m);
		if (it != cend(memo)) { return it->second; }
		const long long v = func(m - 1, memo) * m;
		memo[m] = v;
		return v;
	}

	static long long make_nth(long long ones, long long zeros, long long n, long long bit, long long& target_value) {
		if (ones == 0 || zeros == 0) {

			return 1;
		}
	}


	long long nthSmallest(long long n, int k) {
		if (n == 1) {
			return (1LL << k) - 1;
		}

		unordered_map<long long, long long> memo;

		const auto constant_val = func(k - 1, memo);
		long long zero_count = 1;
		long long remain = n - 1;

		auto get_count = [&](long long zeros)-> long long {
			return func((k - 1LL) + zeros, memo) / (constant_val * func(zeros, memo));
			};

		for (;;) {
			const long long next_count = get_count(zero_count);
			if (remain < next_count) {

			}
			else {
				remain -= next_count;
				zero_count++;
			}
		}

	}
};
static void test(long long n, int k) {
	cout << Solution().nthSmallest(n, k) << endl;
}
static void run() {
	test(4, 2);
	test(3, 1);
}
}

int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}