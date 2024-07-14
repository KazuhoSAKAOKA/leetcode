// weekly_contest_406.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

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

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;


namespace problem1 {

class Solution {
public:

	static bool is_even(char c) {
		if (c == '0' || c == '2' || c == '4' || c == '6' || c == '8') {
			return true;
		}
		else {
			return false;
		}
	}

	string getSmallestString(string s) {

		for (int i = 0; i < s.size() - 1; i++) {
			if (s[i] > s[i + 1] && is_even(s[i]) == is_even(s[i + 1])) {
				const char temp = s[i];
				s[i] = s[i + 1];
				s[i + 1] = temp;
				break;
			}
		}

		return s;
	}
};

void test(string&& s) {
	cout << Solution().getSmallestString(s) << endl;
}
void run() {
	test("45320");
	test("001");
}
}
namespace problem2 {

class Solution {
public:
	ListNode* modifiedList(vector<int>& nums, ListNode* head) {
		unordered_set<int> nums_set(cbegin(nums), cend(nums));
		ListNode dummy_head;
		dummy_head.next = head;
		ListNode* prev = &dummy_head;
		ListNode* current = head;

		while (current != nullptr) {
			if (nums_set.count(current->val) > 0) {
				prev->next = current->next;
				current = current->next;
			}
			else {
				prev = current;
				current = current->next;
			}
		}
		return dummy_head.next;
	}
};

void test(vector<int>&& nums, vector<int>&& values) {
	ListNode* head = create_listnode(values);
	const ListNode* ans = Solution().modifiedList(nums, head);
	output_listnode(ans);
}

void run() {
	test(get_list_int("[1,2,3]"), get_list_int("[1,2,3,4,5]"));
	test(get_list_int("[1]"), get_list_int("[1,2,1,2,1,2]"));
	test(get_list_int("[5]"), get_list_int("[1,2,3,4]"));
}
}
namespace problem3 {
class Solution {
public:
	struct memo_key_t {
		int m;
		int n;
		int h_offset;
		int v_offset;
		bool operator < (const memo_key_t& other) const {
			if (m != other.m) {
				return m < other.m;
			}
			if (n != other.n) {
				return n < other.n;
			}
			if (h_offset != other.h_offset) {
				return h_offset < other.h_offset;
			}
			return v_offset < other.v_offset;
		}
	};
	using memo_t = map<memo_key_t, int>;

	static int rec(int m, int n,int h_offset, int v_offset, vector<int>& horizontalCut, vector<int>& verticalCut, memo_t& memo) {
		if (m == 1 && n == 1) {
			return 0;
		}

		const auto key = memo_key_t{ m, n, h_offset, v_offset };
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}
		int min_cost = INT_MAX;

		for (int y = 0; y < m - 1; y++) {
			const int cost1 = rec(y + 1, n, h_offset, v_offset, horizontalCut, verticalCut, memo);
			const int cost2 = rec(m - y - 1, n, h_offset + y + 1, v_offset, horizontalCut, verticalCut, memo);
			const int current_cost = cost1 + cost2 + horizontalCut[y + h_offset];
			min_cost = min(min_cost, current_cost);
		}
		for (int x = 0; x < n - 1; x++) {
			const int cost1 = rec(m, x + 1, h_offset, v_offset, horizontalCut, verticalCut, memo);
			const int cost2 = rec(m, n - x - 1, h_offset, v_offset + x + 1, horizontalCut, verticalCut, memo);
			const int current_cost = cost1 + cost2 + verticalCut[x + v_offset];
			min_cost = min(min_cost, current_cost);
		}

		memo[key] = min_cost;
		return min_cost;
	}


	int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
		memo_t memo;
		return rec(m, n, 0, 0, horizontalCut, verticalCut, memo);
	}
};
void test(int m, int n, vector<int>&& horizontalCut, vector<int>&& verticalCut) {
	cout << Solution().minimumCost(m, n, horizontalCut, verticalCut) << endl;
}
void run() {
	test(3, 2, get_list_int("[1,3]"), get_list_int("[5]"));
	test(2, 2, get_list_int("[7]"), get_list_int("[4]"));
}
}
namespace problem4 {
class Solution {
public:
	struct memo_key_t {
		int m;
		int n;
		int h_offset;
		int v_offset;
		bool operator < (const memo_key_t& other) const {
			if (m != other.m) {
				return m < other.m;
			}
			if (n != other.n) {
				return n < other.n;
			}
			if (h_offset != other.h_offset) {
				return h_offset < other.h_offset;
			}
			return v_offset < other.v_offset;
		}
		bool operator == (const memo_key_t& other)const {
			return 	(m == other.m) &&
					(n == other.n) &&
					(h_offset == other.h_offset) &&
					(v_offset == other.v_offset);
		}
	};

	struct hasher {
		size_t operator()(const memo_key_t& value) const {
			const auto h1 = hash<int>()(value.m);
			const auto h2 = hash<int>()(value.n);
			const auto h3 = hash<int>()(value.h_offset);
			const auto h4 = hash<int>()(value.v_offset);
			return h1 ^ h2 ^ h3 ^ h4;
		}
	};

	using memo_t = unordered_map<memo_key_t, long long, hasher>;

	static long long greedy_rec(int m, int n, int h_offset, int v_offset, vector<int>& horizontalCut, vector<int>& verticalCut, long long total_horizontals, long long total_verticals,memo_t& memo) {
		if (m == 1 && n == 1) {
			return 0;
		}
		const auto key = memo_key_t{ m, n, h_offset, v_offset };
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}

		long long max_cut_cost = LLONG_MIN;
		vector<pair<bool, int>> greedies;
		for (int y = 0; y < m - 1; y++) {
			const long long current_cost = horizontalCut[y + h_offset];
			if (max_cut_cost < current_cost) {
				greedies.clear();
				greedies.push_back({true, y});
				max_cut_cost = current_cost;
			}
			else if (max_cut_cost == current_cost) {
				greedies.push_back({ true, y });
			}
		}
		for (int x = 0; x < n - 1; x++) {
			const long long current_cost = verticalCut[x + v_offset];
			if (max_cut_cost < current_cost) {
				greedies.clear();
				greedies.push_back({ false, x });
				max_cut_cost = current_cost;
			}
			else if (max_cut_cost == current_cost) {
				greedies.push_back({ false, x });
			}
		}
		long long min_cost = LLONG_MAX;
		for (auto&& [target_horizontal, target_index] : greedies) {
			if (target_horizontal) {
				const long long cost1 = greedy_rec(target_index + 1, n, h_offset, v_offset, horizontalCut, verticalCut, total_horizontals, total_verticals, memo);
				const long long cost2 = greedy_rec(m - target_index - 1, n, h_offset + target_index + 1, v_offset, horizontalCut, verticalCut, total_horizontals, total_verticals, memo);
				min_cost = min(min_cost, cost1 + cost2 + static_cast<long long>(horizontalCut[target_index + h_offset]));
			}
			else {
				const long long cost1 = greedy_rec(m, target_index + 1, h_offset, v_offset, horizontalCut, verticalCut, total_horizontals, total_verticals, memo);
				const long long cost2 = greedy_rec(m, n - target_index - 1, h_offset, v_offset + target_index + 1, horizontalCut, verticalCut, total_horizontals, total_verticals, memo);
				min_cost = min(min_cost, cost1 + cost2 + static_cast<long long>(verticalCut[target_index + v_offset]));
			}

		}
		memo[key] = min_cost;
		return min_cost;
	}

	static long long greedy_rec2(int m, int n, int h_offset, int v_offset, vector<int>& horizontalCut, vector<int>& verticalCut) {
		if (m == 1 && n == 1) {
			return 0;
		}

		bool target_horizontal = false;
		int target_index = -1;
		int max_cost = INT_MIN;

		for (int y = 0; y < m - 1; y++) {
			const long long current_cost = horizontalCut[y + h_offset];
			if (max_cost < current_cost) {
				target_index = y;
				max_cost = current_cost;
				target_horizontal = true;
			}
		}
		for (int x = 0; x < n - 1; x++) {
			const long long current_cost = verticalCut[x + v_offset];
			if (max_cost < current_cost) {
				target_index = x;
				max_cost = current_cost;
				target_horizontal = false;
			}
		}

		long long cost;
		if (target_horizontal) {
			const long long cost1 = greedy_rec2(target_index + 1, n, h_offset, v_offset, horizontalCut, verticalCut);
			const long long cost2 = greedy_rec2(m - target_index - 1, n, h_offset + target_index + 1, v_offset, horizontalCut, verticalCut);
			cost = cost1 + cost2 + static_cast<long long>(horizontalCut[target_index + h_offset]);
		}
		else {
			const long long cost1 = greedy_rec2(m, target_index + 1, h_offset, v_offset, horizontalCut, verticalCut);
			const long long cost2 = greedy_rec2(m, n - target_index - 1, h_offset, v_offset + target_index + 1, horizontalCut, verticalCut);
			cost = cost1 + cost2 + static_cast<long long>(verticalCut[target_index + v_offset]);
		}
		return cost;
	}


	static long long greedy(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {

		sort(begin(horizontalCut), end(horizontalCut), [](const auto& a, const auto& b) {return b < a; });
		sort(begin(verticalCut), end(verticalCut), [](const auto& a, const auto& b) {return b < a; });

		auto is_horizontal = [&](int h_index, int v_index)->bool {
			if (h_index < horizontalCut.size() && v_index < verticalCut.size()) {
				return horizontalCut[h_index] > verticalCut[v_index];
				}
			return h_index < horizontalCut.size();
			};
		long long total_cost = 0;
		int horizontal_index = 0;
		int vertical_index = 0;
		long long horizontal_count = 1;
		long long vertical_count = 1;
		for (; horizontal_index < horizontalCut.size() || vertical_index < verticalCut.size();) {
			if (is_horizontal(horizontal_index, vertical_index)) {
				total_cost += static_cast<long long>(horizontalCut[horizontal_index]) * vertical_count;
				horizontal_count++;
				horizontal_index++;
			}
			else {
				total_cost += static_cast<long long>(verticalCut[vertical_index]) * horizontal_count;
				vertical_count++;
				vertical_index++;
			}
		}
		return total_cost;
	}

	long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
		return greedy(m, n, horizontalCut, verticalCut);
	}

	static long long tle(int m, int n, int h_offset, int v_offset, vector<int>& horizontalCut, vector<int>& verticalCut, memo_t& memo) {
		if (m == 1 && n == 1) {
			return 0;
		}

		const auto key = memo_key_t{ m, n, h_offset, v_offset };
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}
		long long min_cost = LLONG_MAX;

		for (int y = 0; y < m - 1; y++) {
			const long long cost1 = tle(y + 1, n, h_offset, v_offset, horizontalCut, verticalCut, memo);
			const long long cost2 = tle(m - y - 1, n, h_offset + y + 1, v_offset, horizontalCut, verticalCut, memo);
			const long long current_cost = cost1 + cost2 + static_cast<long long>(horizontalCut[y + h_offset]);
			min_cost = min(min_cost, current_cost);
		}
		for (int x = 0; x < n - 1; x++) {
			const long long cost1 = tle(m, x + 1, h_offset, v_offset, horizontalCut, verticalCut, memo);
			const long long cost2 = tle(m, n - x - 1, h_offset, v_offset + x + 1, horizontalCut, verticalCut, memo);
			const long long current_cost = cost1 + cost2 + static_cast<long long>(verticalCut[x + v_offset]);
			min_cost = min(min_cost, current_cost);
		}

		memo[key] = min_cost;
		return min_cost;
	}

};
void test(int m, int n, vector<int>&& horizontalCut, vector<int>&& verticalCut) {
	cout << Solution().minimumCost(m, n, horizontalCut, verticalCut) << endl;
}

void run() {
	test(7, 4, get_list_int("[13,6,12,14,4,7]"), get_list_int("[14,15,11]"));
	test(6, 3, get_list_int("[2,3,2,3,1]"), get_list_int("[1,2]"));
	test(3, 2, get_list_int("[1,3]"), get_list_int("[5]"));
	test(2, 2, get_list_int("[7]"), get_list_int("[4]"));
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