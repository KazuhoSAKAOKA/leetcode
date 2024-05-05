// weekly_contest_396.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;


namespace problem1 {
class Solution {
public:
	bool isValid(string word) {
		unordered_set<char> chars_set;

		for (auto&& c : word) {
			chars_set.insert(c);
		}
		if (chars_set.size() < 3) {
			return false;
		}
		const unordered_set<char> vowels_set = { 'a','i','u','e','o','A','I','U','E','O', };

		bool vowels = false;
		bool consonats = false;

		for (auto&& c : chars_set) {
			if (isdigit(c)) {
			}
			else {
				if (isalpha(c)) {
					if (vowels_set.find(c) != cend(vowels_set)) {
						vowels = true;
					}
					else {
						consonats = true;
					}
				}
				else {
					return false;
				}
			}
		}
		return vowels && consonats;
	}
};

void test(string&& word) {
	cout << Solution().isValid(word) << endl;
}
void run() {
	test("IS");
	test("AhI");
	test("234Adas");
	test("b3");
	test("a3$e");
}
}


namespace problem2 {

class Solution {
public:
	int minimumOperationsToMakeKPeriodic(string word, int k) {
		unordered_map<string, int> periodic_map;
		const auto rpt = word.size() / k;
		for (int i = 0; i < rpt; i++) {
			const auto ss = word.substr(i * k, k);
			periodic_map[ss]++;
		}

		int max_size = 0;
		string max_key = "";
		for (auto&& [k, v] : periodic_map) {
			if (max_size < v) {
				max_size = v;
				max_key = k;
			}
		}

		return rpt - max_size;
	}
};

void test(string&& word, int k) {
	cout << Solution().minimumOperationsToMakeKPeriodic(word, k) << endl;
}
void run() {
	test("leetcodeleet", 4);
	test("leetcoleet", 2);
}
}


namespace problem3 {
class Solution {
public:
	int minAnagramLength(string s) {
		

		auto check = [&](int expect)->bool {
				unordered_map<char, int> chars_map;

				for (int i = 0; i < expect; i++) {
					chars_map[s[i]]++;
				}
				int count = s.size() / expect - 1;
				for (int j = 0; j < count; j++) {
					unordered_map<char, int> chars_map2;
					for (int i = 0; i < expect; i++) {
						chars_map2[s[(j + 1) * expect + i]]++;
					}
					if (chars_map2 != chars_map) {
						return false;
					}
				}
				return true;
			};

		for (int i = 1; i <= s.size() / 2; i++) {
			if (s.size() % i == 0) {
				if (check(i)) {
					return i;
				}
			}
		}
		return s.size();
	}
};

void test(string s) {
	cout << Solution().minAnagramLength(s) << endl;
}
void run() {
	test("abcbaccab");
	test("aaaaaaa");
	test("abba");
	test("cdef");
}
}


namespace problem4 {

class Solution {
public:
	int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
		constexpr long long MODULO = 1000000007;
		
		const int max_value = *max_element(cbegin(nums), cend(nums));

		if (cost1 * 2 <= cost2) {
			int current = 0;
			for (auto&& value : nums) {
				const int diff = max_value - value;
				current += diff;
				current %= static_cast<int>(MODULO);
			}
			return current;
		}

		// 差、その差のある値の数
		unordered_map<int, int> diff_map;

		for (auto&& v : nums) {
			diff_map[max_value - v]++;
		}
		
		long long total_diffs = 0;
		long long diff_count = 0;
		for (auto&& [k, v] : diff_map) {
			if (k != 0) {
				diff_count += v;
				total_diffs += k * v;
			}
		}

		if (diff_count % 2 == 0) {

			return static_cast<int>(((total_diffs / 2) % MODULO) * cost2 % MODULO);
		}



		return -1;
	}
};
void test(vector<int>&& nums, int cost1, int cost2) {
	cout << Solution().minCostToEqualizeArray(nums, cost1, cost2) << endl;
}
void run() {
	test({ 4,1 }, 5, 2);
	test({ 2,3,3,3,5 }, 2, 1);
	test({ 3,5,3, }, 1, 3);
}
}



int main()
{

	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
}