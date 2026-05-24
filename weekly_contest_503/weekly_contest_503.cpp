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
	vector<int> limitOccurrences(vector<int>& nums, int k) {
		map<int, int> freqs;
		for (auto&& num : nums) {
			freqs[num]++;
		}
		vector<int> ans;
		ans.reserve(size(nums));
		for (auto&& [num, f] : freqs) {
			for (int i = 0; i < min(k, f); i++) {
				ans.push_back(num);
			}
		}

		return ans;
	}
};
static void test(vector<int>&& nums, int k) {
	output(Solution().limitOccurrences(nums, k));
}
static void run() {
	test(get_list_int("[1,1,1,2,2,3]"), 2);
	test(get_list_int("[1,2,3]"), 1);
}
}

namespace problem2 {
class Solution {
public:
	int passwordStrength(string password) {
		const string symbols("!@#$");
		unordered_map<char, int> points;
		for (char c = 'a'; c < 'z' + 1; c++) {
			points.insert({ c,1 });
		}
		for (char c = 'A'; c < 'Z' + 1; c++) {
			points.insert({ c,2 });
		}
		for (char c = '0'; c < '9' + 1; c++) {
			points.insert({ c,3 });
		}
		for (auto&& c :symbols) {
			points.insert({ c,5 });
		}
		int ans = 0;
		for (auto&& c : password) {
			auto it = points.find(c);
			ans += it->second;
			it->second = 0;
		}
		return ans;
	}
};
static void test(string p) {
	cout << Solution().passwordStrength(p) << endl;
}
static void run() {
	test("aA1!");
	test("bbB11#");
}
}

namespace problem3 {
class Solution {
public:

	static int detect_rotate_count(int n, const vector<int>& nums, int min_value, int start, int detect_inc,int order_inc, int optional_add) {
		int rotate_count = 0;
		int start_index = start;
		int detect_index = start;
		for (int i = 0; i < n; i++) {
			if (nums[detect_index] == min_value) {
				start_index = detect_index;
				rotate_count = i;
				break;
			}
			detect_index += n + detect_inc;
			detect_index %= n;
		}
		int index = start_index;
		for (int i = 0; i < n - 1; i++) {
			if (nums[index] > nums[(index + order_inc + n) % n]) {
				return INT_MAX;
			}
			index += n + order_inc;
			index %= n;
		}
		return rotate_count + optional_add;
	}

	int minOperations(vector<int>& nums) {
		const int n = size(nums);
		auto min_value = *min_element(cbegin(nums), cend(nums));
		int ans = INT_MAX;

		const auto a = detect_rotate_count(n, nums, min_value, 0, 1, 1, 0);
		const auto b = detect_rotate_count(n, nums, min_value, 0, -1, 1, 2);
		const auto c = detect_rotate_count(n, nums, min_value, n - 1, 1, -1, 1);
		const auto d = detect_rotate_count(n, nums, min_value, n - 1, -1, -1, 1);

		ans = min(ans, a);
		ans = min(ans, b);
		ans = min(ans, c);
		ans = min(ans, d);

		if (ans == INT_MAX) { return-1; }
		return ans;
	}
};
static void test(vector<int>&& nums) {
	cout << Solution().minOperations(nums) << endl;
}
static void run() {
	test(get_list_int("[1,2,3]"));
	test(get_list_int("[2,3,4,5,1]"));
	test(get_list_int("[3,2,1]"));

	test(get_list_int("[0,2,1]"));
	test(get_list_int("[1,0,2]"));
	//test(get_list_int("[2,0,1,3]"));
}
}

namespace problem4 {
class Solution {
	vector<vector<int>> check_nums_collect;
public:


	vector<int> tle(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
		const int n2 = size(nums2);
		vector<int> ans;
		vector<int> diffs(n2 + 1, 0);
		unordered_map<int, int> nums1_map;
		for (auto&& num : nums1) { nums1_map[num]++; }


		for (auto&& query : queries) {
			if (query.front() == 1) {
				const auto left = query[1];
				const auto right = query[2];
				const auto val = query[3];
				diffs[left] += val;
				diffs[min(right + 1, n2)] -= val;


				vector<int> tempnums;
				int cur_count = 0;
				int cur_inc = 0;
				for (int i = 0; i < n2; i++) {
					cur_inc += diffs[i];
					const auto cur_num = nums2[i] + cur_inc;
					tempnums.push_back(cur_num);
				}
				check_nums_collect.emplace_back(move(tempnums));

			}
			else {
				const auto total = query[1];
				int cur_count = 0;
				int cur_inc = 0;
				for (int i = 0; i < n2; i++) {
					cur_inc += diffs[i];
					const auto cur_num = nums2[i] + cur_inc;
					auto remain = total - cur_num;
					if (remain > 0) {
						auto it = nums1_map.find(remain);
						if (it != cend(nums1_map)) {
							cur_count += it->second;
						}
					}
				}
				ans.push_back(cur_count);
			}
		}
		return ans;
	}

	vector<int> tle2(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {


		const int n2 = size(nums2);
		const int sqlen = static_cast<int>(ceil(sqrt(static_cast<double>(n2))));
		const int nsq = (n2 + sqlen - 1) / sqlen;
		vector<int> ans;
		vector<int> sqs(nsq, 0);
		unordered_map<int, int> nums1_map;
		for (auto&& num : nums1) { nums1_map[num]++; }
		vector<vector<int>> check_nums;

		for (auto&& query : queries) {
			if (query.front() == 1) {
				const auto left = query[1];
				const auto right = query[2];
				const auto val = query[3];

				const auto left_sq_index = left / sqlen + 1;
				const auto right_sq_index = right / sqlen - 1;
				if (left_sq_index >= right_sq_index) {
					for (int i = left; i <= right; i++) {
						nums2[i] += val;
					}
				}
				else {
					for (int i = left; i < left_sq_index * sqlen; i++) {
						nums2[i] += val;
					}
					for (int i = left_sq_index; i <= right_sq_index; i++) {
						sqs[i] += val;
					}
					for (int i = right_sq_index * sqlen + 1; i <= right; i++) {
						nums2[i] += val;
					}
				}

				vector<int> tempnums;
				for (int i = 0; i < n2; i++) {
					const auto cur_num = nums2[i] + sqs[i / sqlen];
					tempnums.push_back(cur_num);
				}
				check_nums.emplace_back(move(tempnums));
			}
			else {
				const auto total = query[1];
				int cur_count = 0;
				for (int i = 0; i < n2; i++) {
					const auto cur_num = nums2[i] + sqs[i / sqlen];
					auto remain = total - cur_num;
					if (remain > 0) {
						auto it = nums1_map.find(remain);
						if (it != cend(nums1_map)) {
							cur_count += it->second;
						}
					}
				}
				ans.push_back(cur_count);
			}
		}

		return ans;
	}


	vector<int> numberOfPairs(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
		auto tempdata(nums2);
		tle(nums1, tempdata, queries);
		vector<vector<int>> check_nums;


		const int n2 = size(nums2);
		const int sqlen = static_cast<int>(ceil(sqrt(static_cast<double>(n2))));
		const int nsq = (n2 + sqlen - 1) / sqlen;
		vector<int> ans;
		vector<int> sqs(nsq, 0);
		unordered_map<int, int> nums1_map;
		vector<int> diffs(n2 + 1, 0);
		for (auto&& num : nums1) { nums1_map[num]++; }

		for (auto&& query : queries) {
			if (query.front() == 1) {
				const auto left = query[1];
				const auto right = query[2];
				const auto val = query[3];

				const auto left_sq_index = (left % sqlen == 0) ? left / sqlen : left / sqlen + 1;
				const auto right_sq_index = (right % sqlen == 0) ? right / sqlen : right / sqlen - 1;
				if (left_sq_index >= right_sq_index) {
					diffs[left] += val;
					diffs[right + 1] -= val;
				}
				else {
					if (left % sqlen != 0) {
						diffs[left] += val;
						diffs[left_sq_index * nsq] -= val;
					}
					for (int i = left_sq_index; i <= right_sq_index; i++) {
						sqs[i] += val;
					}
					if (right % sqlen != 0) {
						diffs[(right_sq_index + 1) * nsq] += val;
						diffs[right + 1] -= val;
					}
				}


				int cur_diff = 0;
				vector<int> tempnums;
				for (int i = 0; i < n2; i++) {
					cur_diff += diffs[i];
					const auto cur_num = nums2[i] + cur_diff + sqs[i / sqlen];
					tempnums.push_back(cur_num);
				}
				check_nums.emplace_back(move(tempnums));


			}
			else {
				const auto total = query[1];
				int cur_count = 0;
				int cur_diff = 0;
				for (int i = 0; i < n2; i++) {
					cur_diff += diffs[i];
					const auto cur_num = nums2[i] + cur_diff + sqs[i / sqlen];
					auto remain = total - cur_num;
					if (remain > 0) {
						auto it = nums1_map.find(remain);
						if (it != cend(nums1_map)) {
							cur_count += it->second;
						}
					}
				}
				ans.push_back(cur_count);
			}
		}


		for (int i = 0; i < size(check_nums); i++) {
			if (check_nums[i] != check_nums_collect[i]) {
				cout << "invalid index" << i << endl;
				output(check_nums[i]);
				output(check_nums_collect[i]);
			}
		}


		return ans;
	}
};
static void test(vector<int>&& nums1, vector<int>&& nums2, vector<vector<int>>&& queries) {
	output(Solution().numberOfPairs(nums1, nums2, queries));
}
static void run() {
	test(get_list_int("[35,10,65,92,30]"), get_list_int("[1,18,46,69,64,14,45,33,5,27,81,18,6,81,58,30,83,22,3,3,30,2,93,48,13,53,85,68,87,82,60,7,9,48,88,42,15,57,71,22,91,14,47,3,10,72,41]"), get_matrix_int("[[2,87],[1,13,14,99],[2,98],[2,71],[2,121],[2,112],[2,67],[1,17,17,62],[2,93],[2,80],[2,46],[1,11,33,16],[1,30,40,8],[1,3,36,62],[2,180],[2,77],[2,135],[2,42],[1,15,45,94],[2,161],[2,359],[2,191]]"));
	//test(get_list_int("[49,10]"), get_list_int("[1,10,30,9,32,7,42,1,36,12,11,32,51,47,29,12,23,50,41,5,1,18,50,23,10,32,53]"), get_matrix_int("[[1,11,24,30],[2,35],[1,1,21,31],[2,93],[2,102]]"));
	//test(get_list_int("[1,2]"), get_list_int("[3,4]"), get_matrix_int("[[2,5],[1,0,0,2],[2,5]]"));
	//test(get_list_int("[1,1]"), get_list_int("[2,2,3]"), get_matrix_int("[[2,4],[1,0,1,1],[2,4]]"));
	//test(get_list_int("[2,5,8,4]"), get_list_int("[1,3,8]"), get_matrix_int("[[2,9],[1,1,2,1],[2,10]]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
