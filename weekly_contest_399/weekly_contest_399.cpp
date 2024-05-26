// weekly_contest_399.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

namespace problem1 {
class Solution {
public:

	int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		if (k == 0) { return 0; }
		int result = 0;
		for (int i = 0; i < nums1.size(); i++) {
			for (int j = 0; j < nums2.size(); j++) {
				if (nums2[j] != 0 && nums1[i] % (nums2[j] * k) == 0) {
					result++;
				}
			}
		}
		return result;
	}
};
void test(vector<int>&& nums1, vector<int>&& nums2, int k) {
	cout << Solution().numberOfPairs(nums1, nums2, k) << endl;
}
void run() {
	test(get_list_int("[1,3,4]"), get_list_int("[1,3,4]"), 1);
	test(get_list_int("[1,2,4,12]"), get_list_int("[2,4]"), 3);
}
}

namespace problem2 {
class Solution {
public:
	string compressedString(string word) {

		struct compresser {
			string buffer;
			char current = 0;
			int current_streak = 0;

			void append(char c) {
				if (current == c) {
					current_streak++;
					if (current_streak == 9) {
						flush();
					}
				}
				else {
					flush();
					current = c;
					current_streak = 1;
				}
			}

			void flush() {
				if (current_streak != 0) {
					buffer += (static_cast<char>(current_streak) + '0');
					buffer += current;
					current_streak = 0;
					current = 0;
				}
			}
			const string& get_buffer() const {
				return buffer;
			}
		};
		compresser comp;
		for (int i = 0; i < word.size(); i++) {
			comp.append(word[i]);
		}
		comp.flush();
		return comp.get_buffer();
	}
};
void test(string&& word) {
	cout << Solution().compressedString(word) << endl;
}
void run() {
	test("abcde");
	test("aaaaaaaaaaaaaabb");
}
}

namespace problem3 {
class Solution {
public:

	long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		if (k == 0) { return 0; }
		map<int, int> work;
		for (int i = 0; i < nums1.size(); i++) {
			if (nums1[i] % k == 0) {
				work[nums1[i]]++;
			}
		}
		map<int, int> m2;
		for (int i = 0; i < nums2.size(); i++) {
			m2[nums2[i]]++;
		}
		long long result = 0;
		for (auto&& [key,v] : m2) {
			const auto d = key * k;
			auto it = work.lower_bound(d);// lower_bound(cbegin(work), cend(work), d);
			if (it != cend(work)) {
				for (; it != cend(work); ++it) {
					if (it->first % d == 0) {
						result += static_cast<long long>(v) * static_cast<long long>(it->second);
					}
				}
			}
		}

		return result;
	}
};
void test(vector<int>&& nums1, vector<int>&& nums2, int k) {
	cout << Solution().numberOfPairs(nums1, nums2, k) << endl;
}
void run() {
	test(get_list_int("[1,2]"), get_list_int("[3,2]"), 2);
	test(get_list_int("[1,3,4]"), get_list_int("[1,3,4]"), 1);
	test(get_list_int("[1,2,4,12]"), get_list_int("[2,4]"), 3);
}

}

namespace problem4 {

void run() {

}
}




int main() {
	//problem1::run();
	//problem2::run();
	problem3::run();
	problem4::run();
}

