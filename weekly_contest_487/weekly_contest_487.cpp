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
	int countMonobit(int n) {
		set<int> monobits;
		auto get_count = [](int v)->int {
			int c = 0;
			for (int i = 0; i < 32; i++) {
				if (v & (1 << i)) {
					c++;
				}
			}
			return c;
			};
		for (int i = 0; i <= n; i++) {
			monobits.insert(get_count(i));
		}

		return static_cast<int>(size(monobits));
	}
};
static void test(int n) {
	cout << Solution().countMonobit(n) << endl;
}
static void run() {
	test(1);
	test(4);
}
}

namespace problem2 {
class Solution {
public:
	int finalElement(vector<int>& nums) {
		const auto n = size(nums);
		if (n == 1) {
			return nums[0];
		}
		const auto max_index = distance(cbegin(nums), max_element(cbegin(nums), cend(nums)));
		if (max_index == 0) {
			return nums[0];
		}
		if (max_index == n - 1) {
			return nums[n - 1];
		}
		return max(nums[0], nums[n - 1]);
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().finalElement(nums) << endl;
}
static void run() {
	test(get_list_int("[1,5,2]"));
	test(get_list_int("[3,7]"));
}
}

namespace problem3 {
class RideSharingSystem {
	map<int, int> rider_map;
	int rider_tag = 0;
	map<int, int> rider_reverse_map;
	map<int, int> driver_map;
	int dirver_tag = 0;

public:
	RideSharingSystem() {

	}

	void addRider(int riderId) {
		rider_map.insert({ rider_tag, riderId });
		rider_reverse_map.insert({ riderId, rider_tag });
		rider_tag++;
	}

	void addDriver(int driverId) {
		driver_map.insert({ dirver_tag, driverId });
		dirver_tag++;
	}

	vector<int> matchDriverWithRider() {
		if (rider_map.empty() || driver_map.empty()) {
			return { -1,-1 };
		}
		const auto [rider_key, rider_id] = *cbegin(rider_map);
		const auto [driver_key, driver_id] = *cbegin(driver_map);
		rider_reverse_map.erase(rider_id);
		rider_map.erase(rider_key);
		driver_map.erase(driver_key);
		return { driver_id,rider_id };
	}

	void cancelRider(int riderId) {
		auto it = rider_reverse_map.find(riderId);
		if (it != cend(rider_reverse_map)) {
			const auto rider_tag = it->second;
			rider_map.erase(rider_tag);
			rider_reverse_map.erase(it);
		}
	}
};
static void run() {
}
}

namespace problem4 {
class Solution {
public:
	int longestAlternating(vector<int>& nums) {
		const auto n = size(nums);
		if (n == 1) { return 1; }
		vector<vector<int>> dp1(n, vector<int>(2));
		vector<vector<int>> dp2(n, vector<int>(2));
		dp1[0][0] = 1;
		dp1[0][1] = 0;
		dp2[0][0] = 1;
		dp2[0][1] = 0;
		if (nums[0] < nums[1]) {
			dp2[1][0] = 2;
			dp1[1][0] = 1;
		}
		else if(nums[0] > nums[1]) {
			dp1[1][0] = 2;
			dp2[1][0] = 1;
		}
		else {
			dp1[1][0] = 1;
			dp2[1][0] = 1;
		}
		dp1[1][1] = 1;
		dp2[1][1] = 1;

		int max_len = max(dp1[1][0], dp2[1][0]);

		auto tran = [&nums](int i, vector<vector<int>>& cur_low_dp, vector<vector<int>>& cur_high_dp) {
			if (nums[i - 1] < nums[i]) {
				cur_high_dp[i][0] = cur_high_dp[i - 1][0] + 1;
				cur_low_dp[i][0] = 1;

				cur_high_dp[i][1] = cur_high_dp[i - 1][1] + 1;
				if (nums[i - 2] < nums[i]) {
					cur_high_dp[i][1] = max(cur_high_dp[i][1], cur_low_dp[i - 2][0] + 1);
				}

				cur_low_dp[i][1] = 1;
				if (nums[i - 2] > nums[i]) {
					cur_low_dp[i][1] = max(cur_low_dp[i][1], cur_high_dp[i - 2][0] + 1);
				}
			}
			else if (nums[i - 1] > nums[i]) {
				cur_high_dp[i][0] = 1;
				cur_low_dp[i][0] = cur_low_dp[i - 1][0] + 1;

				if (nums[i - 2] > nums[i]) {
					cur_high_dp[i][1] = max(cur_high_dp[i][1], cur_low_dp[i - 2][0] + 1);
				}

				cur_high_dp[i][1] = 1;
				if (nums[i - 2] < nums[i]) {
					cur_high_dp[i][1] = max(cur_high_dp[i][1], cur_low_dp[i - 2][0] + 1);
				}

				cur_low_dp[i][1] = cur_low_dp[i - 1][1] + 1;
				if (nums[i - 2] > nums[i]) {
					cur_low_dp[i][1] = max(cur_low_dp[i][1], cur_high_dp[i - 2][0] + 1);
				}
			}
			else {
				cur_high_dp[i][0] = 1;
				cur_low_dp[i][0] = 1;
				
				cur_high_dp[i][1] = 1;
				if (nums[i - 2] < nums[i]) {
					cur_high_dp[i][1] = max(cur_high_dp[i][1], cur_low_dp[i - 2][0] + 1);
				}
				cur_low_dp[i][1] = 1;
				if (nums[i - 2] > nums[i]) {
					cur_low_dp[i][1] = max(cur_low_dp[i][1], cur_high_dp[i - 2][0] + 1);
				}
			}
			};


		for (int i = 2; i < n; i++) {
			if (i % 2 == 0) {
				tran(i, dp2, dp1);
			}
			else {
				tran(i, dp1, dp2);
			}

			max_len = max(max_len, dp1[i][0]);
			max_len = max(max_len, dp1[i][1]);
			max_len = max(max_len, dp2[i][0]);
			max_len = max(max_len, dp2[i][1]);
		}
		return max_len;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().longestAlternating(nums) << endl;
}
static void run() {
	test(get_list_int("[1,2,2,3]"));

	test(get_list_int("[3,2,1,2,3,2,1]"));
	test(get_list_int("[100000,100000]"));
	test(get_list_int("[2,1,3,2]"));
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

/*if (i % 2 == 0) {
				if (nums[i - 1] < nums[i]) {
					dp1[i][0] = dp1[i - 1][0] + 1;
					dp2[i][0] = 1;

					dp1[i][1] = 1;
					if (nums[i - 2] > nums[i]) {
						dp1[i][1] = max(dp1[i][1], dp2[i - 2][0] + 1);
					}

					dp2[i][1] = dp2[i - 1][1] + 1;
					if (nums[i - 2] < nums[i]) {
						dp2[i][1] = max(dp2[i][1], dp1[i - 2][0] + 1);
					}
				}
				else if (nums[i - 1] > nums[i]) {
					dp1[i][0] = 1;
					dp2[i][0] = dp2[i - 1][0] + 1;

					dp1[i][1] = dp1[i - 1][1] + 1;
					if (nums[i - 2] > nums[i]) {
						dp1[i][1] = max(dp1[i][1], dp2[i - 2][0] + 1);
					}

					dp2[i][1] = 1;
					if (nums[i - 2] < nums[i]) {
						dp2[i][1] = max(dp2[i][1], dp1[i - 2][0] + 1);
					}
				}
				else {
					dp1[i][0] = 1;
					dp2[i][0] = 1;
				}
			}
			else {
				if (nums[i - 1] > nums[i]) {
					dp1[i][0] = dp1[i - 1][0] + 1;
					dp2[i][0] = 1;


				}
				else if (nums[i - 1] < nums[i]) {
					dp1[i][0] = 1;
					dp2[i][0] = dp2[i - 1][0] + 1;



				}
				else {
					dp1[i][0] = 1;
					dp2[i][0] = 1;
				}
			}*/