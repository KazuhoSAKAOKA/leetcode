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

namespace problem1 {
class Solution {
public:
	int countCommas(int n) {
		if (n < 1000) {
			return 0;
		}
		return n - 1000 + 1;
	}
};
static void test(int n) {
	cout << Solution().countCommas(n) << endl;
}
static void run() {
	test(1002);
	test(998);
}
}

namespace problem2 {
class Solution {
public:
	long long countCommas(long long n) {
		if (n < 1000) { return 0LL; }
		long long ans = 0LL;
		ans += n - 1000 + 1;
		if (n >= 1000'000) {
			ans += n - 1000'000 + 1;
			if (n >= 1000'000'000) {
				ans += n - 1000'000'000 + 1;
				if (n >= 1000'000'000'000) {
					ans += n - 1000'000'000'000 + 1;
					if (n >= 1000'000'000'000'000) {
						ans += n - 1000'000'000'000'000 + 1;
					}
				}
			}
		}
		return ans;
	}
};
static void test(int n) {
	cout << Solution().countCommas(n) << endl;
}
static void run() {
	test(1002);
	test(998);
}
}

namespace problem3 {
class Solution {
public:

	int longestArithmetic(vector<int>& nums) {
		constexpr int INF = INT_MAX / 2;
		const auto n = size(nums);
		vector<pair<int, int>> diff_streak_begin(n);
		vector<pair<int, int>> diff_streak_end(n);
		int streak = 2;
		int prev_diff = nums[0 + 1] - nums[0];
		int max_streak = 2;
		diff_streak_end[0] = { INF, 1 };
		for (int i = 1; i < n - 1; i++) {
			const auto cur_diff = nums[i + 1] - nums[i];
			if (prev_diff != cur_diff) {
				diff_streak_begin[i - (streak - 1)] = { prev_diff,streak };
				diff_streak_end[i] = { prev_diff,streak };
				streak = 2;
				prev_diff = cur_diff;
			}
			else {
				streak++;
				max_streak = max(max_streak, streak);
			}
		}
		diff_streak_begin[n - 1 - (streak - 1)] = { prev_diff,streak };
		diff_streak_end[n - 1] = { prev_diff,streak };
		diff_streak_begin[n - 1] = { INF,1 };


		if (diff_streak_begin[1].second > 0) {
			max_streak = max(max_streak, diff_streak_begin[1].second + 1);
		}
		for (int i = 1; i < n - 1; i++) {
			if (nums[i + 1] - nums[i - 1] == diff_streak_end[i - 1].first * 2) {
				if (diff_streak_begin[i + 1].first == diff_streak_end[i - 1].first) {
					const auto connected = diff_streak_begin[i + 1].second + diff_streak_end[i - 1].second + 1;
					max_streak = max(max_streak, connected);
				}
				else {
					max_streak = max(max_streak, diff_streak_end[i - 1].second + 2);
				}
			}
			else if (nums[i + 1] - nums[i - 1] == diff_streak_begin[i + 1].first * 2) {
				max_streak = max(max_streak, diff_streak_begin[i + 1].second + 2);
			}
			else {
				max_streak = max(max_streak, diff_streak_end[i - 1].second + 1);
				max_streak = max(max_streak, diff_streak_begin[i + 1].second + 1);
			}
		}
		if (diff_streak_end[n - 2].second > 0) {
			max_streak = max(max_streak, diff_streak_end[n - 2].second + 1);
		}
		return max_streak;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().longestArithmetic(nums) << endl;
}
static void run() {
	test(get_list_int("[19334,19334,24488,58213,19334,19334,19334,19334,19334,19334]"));
	test(get_list_int("[9,7,5,10,1]"));
	test(get_list_int("[1,2,1,1]"));
	test(get_list_int("[1,1,3,4]"));
	test(get_list_int("[1,1,2,3]"));
	test(get_list_int("[1,1,2,1]"));
	test(get_list_int("[1,1,1,2]"));
	test(get_list_int("[1,2,3,10,5,6,7]"));
	test(get_list_int("[1,2,6,7]"));
}
}

namespace problem4 {
class Solution {
public:

	struct union_find {

		std::vector<size_t> parents_;
		std::vector<size_t> sizes_;

		union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
			for (size_t i = 0; i < n; i++) {
				parents_[i] = i;
			}
		}

		size_t root(size_t x) {
			if (x == parents_[x]) { return x; }
			parents_[x] = root(parents_[x]);
			return parents_[x];
		}

		bool same(size_t x, size_t y) {
			return root(x) == root(y);
		}

		void unite(size_t x, size_t y) {
			const auto rootx = root(x);
			const auto rooty = root(y);
			if (rootx == rooty) { return; }
			if (sizes_[rootx] < sizes_[rooty]) {
				parents_[rootx] = rooty;
				sizes_[rooty] += sizes_[rootx];
			}
			else {
				parents_[rooty] = rootx;
				sizes_[rootx] += sizes_[rooty];
			}
		}

		size_t size(size_t x) {
			return sizes_[root(x)];
		}

		bool is_root(size_t x) {
			return root(x) == x;
		}
	};

	int maxActivated(vector<vector<int>>& points) {
		const auto n = size(points);
		union_find uf(n);
		map<int, set<int>> x_map;
		map<int, set<int>> y_map;
		for (size_t i = 0; i < n; i++) {
			const auto& point = points[i];
			const auto x = point.front();
			const auto y = point.back();
			auto itx = cbegin(x_map[x]);
			if (itx != cend(x_map[x])) {
				uf.unite(i, *itx);
			}
			auto ity = cbegin(y_map[y]);
			if (ity != cend(y_map[y])) {
				uf.unite(i, *ity);
			}

			x_map[x].insert(i);
			y_map[y].insert(i);
		}
		if (uf.size(0) == n) {
			return n + 1;
		}
		multiset<size_t, greater<size_t>> sizes;
		for (size_t i = 0; i < n; i++) {
			if (uf.is_root(i)) {
				sizes.insert(uf.size(i));
			}
		}

		int total = static_cast<int>(*cbegin(sizes) + *(next(cbegin(sizes)))) + 1;
		return total;
	}
};
static void test(vector<vector<int>>&& points) {
	cout << Solution().maxActivated(points) << endl;
}
static void run() {
	test(get_matrix_int("[[1,1],[1,2],[2,2]]"));
	test(get_matrix_int("[[2,2],[1,1],[3,3]]"));
	test(get_matrix_int("[[2,3],[2,2],[1,1],[4,5]]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
