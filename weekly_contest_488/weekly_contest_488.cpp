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
	int dominantIndices(vector<int>& nums) {
		const auto n = size(nums);
		long long total = accumulate(cbegin(nums), cend(nums), 0LL, [](long long t, int num) { return t + static_cast<long long>(num); });
		int count = 0;
		for (int i = 0; i < n - 1; i++) {
			total -= nums[i];
			const double cur_ave = static_cast<double>(total) / static_cast<double>(n - i - 1);
			if (static_cast<double>(nums[i]) > cur_ave) {
				count++;
			}
		}
		return count;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().dominantIndices(nums) << endl;
}
static void run() {
	test(get_list_int("[5,4,3]"));
	test(get_list_int("[4,1,2]"));
}
}

namespace problem2 {
class Solution {
public:
	vector<long long> mergeAdjacent(vector<int>& nums) {
		const auto n = size(nums);
		vector<long long> ans;
		ans.reserve(n);

		for (int i = 0; i < n; i++) {
			long long num = static_cast<long long>(nums[i]);
			while (!ans.empty() && ans.back() == num) {
				num *= 2;
				ans.pop_back();
			}
			ans.emplace_back(num);
		}
		return ans;
	}
};
static void test(vector<int>&& nums) {
	output(Solution().mergeAdjacent(nums));
}
static void run() {
	test(get_list_int("[3,1,1,2]"));
	test(get_list_int("[2,2,4]"));
	test(get_list_int("[3,7,5]"));
}
}

namespace problem3 {
class Solution {
public:
	long long countSubarrays(vector<int>& nums, long long k) {
		const auto n = size(nums);

		long long count = 0;
		map<long long, size_t> freq_map;

		auto check = [&](long long width) {
			const long long min_val = cbegin(freq_map)->first;
			const long long max_val = crbegin(freq_map)->first;
			return (max_val - min_val) * width <= k;
			};
		long long l = 0;
		for (long long r = 0; r < n; r++) {
			freq_map[nums[r]]++;
			while (l < r && !check(r - l + 1)) {
				auto it = freq_map.find(nums[l]);
				if (it->second == 1) {
					freq_map.erase(it);
				}
				else {
					it->second--;
				}
				l++;
			}
			count += r - l + 1;
		}
		return count;
	}
};
static void test(vector<int>&& nums, long long k) {
	cout << Solution().countSubarrays(nums, k) << endl;
}
static void run() {
	test(get_list_int("[1,3,2]"), 4);
	test(get_list_int("[5,5,5,5]"), 0);
	test(get_list_int("[1,2,3]"), 0);
}
}

namespace problem4 {
class Solution {
public:

	long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
		const auto n = size(nums1);
		const auto m = size(nums2);

		auto mul = [&](int i, int j)->long long {
			return static_cast<long long>(nums1[i]) * static_cast<long long>(nums2[j]);
			};

		vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(m, vector<long long>(k + 1, LLONG_MIN / 2)));

		dp[0][0][0] = 0LL;
		dp[0][0][1] = mul(0, 0);;

		for (int i = 1; i < n; i++) {
			dp[i][0][0] = 0LL;
			dp[i][0][1] = max(dp[i - 1][0][1], mul(i, 0));
		}
		for (int j = 1; j < m; j++) {
			dp[0][j][0] = 0LL;
			dp[0][j][1] = max(dp[0][j - 1][1], mul(0, j));
		}

		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++) {
				dp[i][j][0] = 0LL;
				for (int l = 1; l <= k; l++) {
					long long v = dp[i - 1][j - 1][l - 1] + mul(i, j);
					v = max(v, dp[i - 1][j][l]);
					v = max(v, dp[i][j - 1][l]);
					dp[i][j][l] = max(dp[i][j][l], v);
				}
			}
		}
		return dp.back().back()[k];
	}
}; 
static void test(vector<int>&& nums1, vector<int>&& nums2, int k) {
	cout << Solution().maxScore(nums1, nums2, k) << endl;
}
static void run() {
	test(get_list_int("[-29,-27]"), get_list_int("[7,4,3,3]"), 1);
	test(get_list_int("[1,3,2]"), get_list_int("[4,5,1]"), 2);
	test(get_list_int("[-2,0,5]"), get_list_int("[-3,4,-1,2]"), 2);
	test(get_list_int("[-3,-2]"), get_list_int("[1,2]"), 2);
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
