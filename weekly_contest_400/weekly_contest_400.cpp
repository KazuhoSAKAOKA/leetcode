// weekly_contest_400.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


namespace problem1 {

class Solution {
public:
	int minimumChairs(string s) {
		int char_used = 0;
		int max_used = 0;
		for (auto&& c : s) {
			if (c == 'E') {
				char_used++;
				max_used = max(max_used, char_used);
			}
			else {
				char_used--;
			}
		}
		return max_used;
	}
};

void test(string&& s) {
	cout << Solution().minimumChairs(s) << endl;
}

void run() {
	test("EEEEEEE");
	test("ELELEEL");
	test("ELEELEELLL");
}
}

namespace problem2 {
class Solution {
public:
	int countDays(int days, vector<vector<int>>& meetings) {
		int result = 0;

		sort(begin(meetings), end(meetings), [](const auto& a, const auto& b) { return a.front() < b.front(); });
		int last_free_day = 1;
		for (auto&& meeting : meetings) {
			const auto b = meeting[0];
			const auto e = meeting[1];
			if (last_free_day < b) {
				result += b - last_free_day;
			}
			last_free_day = max(last_free_day, e + 1);
		}
		if (last_free_day <= days) {
			result += days - last_free_day + 1;
		}

		return result;
	}
};

void test(int days, vector<vector<int>>&& meetings) {
	cout << Solution().countDays(days, meetings) << endl;
}
void run() {
	test(10, get_matrix_int("[[2,3],[5,6],[8,9]]"));
	test(10, get_matrix_int("[[5,7],[1,3],[9,10]]"));
	test(5, get_matrix_int("[[2,4],[1,3]]"));
	test(6, get_matrix_int("[[1,6]]"));
}
}

namespace problem3 {
class Solution {
public:
	string clearStars(string s) {
		struct index_info {
			size_t index;
			char c;
		};

		auto compare = [](const index_info& a, const index_info& b) {
			if (a.c != b.c) {
				return a.c > b.c;
			}
			return a.index < b.index;
			};
		priority_queue<index_info, vector<index_info>, decltype(compare)> pq(compare);
		
		for (size_t i = 0; i < s.size(); i++) {
			if(s[i] == '*'){
				pq.pop();
			}
			else {
				pq.push(index_info{ i, s[i] });
			}
		}

		vector<index_info> v;
		v.reserve(pq.size());
		while (!pq.empty()) {
			v.emplace_back(pq.top());
			pq.pop();
		}		
		sort(begin(v), end(v), [](const index_info& a, const index_info& b) { return a.index < b.index; });
		string result(v.size(), 'X');
		for (int i = 0; i < v.size(); i++) {
			result[i] = v[i].c;
		}
		return result;
	}
};

void test(string&& s) {
	cout << Solution().clearStars(s) << endl;
}

void run() {
	test("aaba*");
	test("abc");
}
}

namespace problem4 {

class Solution {
public:

	int minimumDifference(vector<int>& nums, int k) {

		unordered_set<int> before;
		int min_value = abs(nums[0] - k);
		before.insert(nums[0]);
		for (int i = 1; i < nums.size(); i++) {
			unordered_set<int> current;
			for (auto&& v : before) {
				const int bitwise_and = v & nums[i];
				min_value = min(min_value, abs(bitwise_and - k));
				current.insert(bitwise_and);
			}
			current.insert(nums[i]);
			min_value = min(min_value, abs(nums[i] - k));
			before = current;
		}
		return min_value;
	}
};

void test(vector<int>&& nums, int k) {
	cout << Solution().minimumDifference(nums, k) << endl;
}

void run() {
	test(get_list_int("[13,2,66,52,59]"), 38);
	test(get_list_int("[1,2,4,5]"), 3);
	test(get_list_int("[1,2,1,2]"), 2);
	test(get_list_int("[1]"), 10);
}
}

int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
}