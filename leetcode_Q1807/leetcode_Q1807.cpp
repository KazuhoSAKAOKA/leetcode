
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
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


class Solution {
public:
	string evaluate(string s, vector<vector<string>>& knowledge) {
		unordered_map<string, string> dic;
		for (auto&& k : knowledge) {
			dic.insert({ k[0],k[1] });
		}

		string ans;
		string key;
		bool inbracket = false;
		for (auto&& c : s) {
			if (c == '(') {
				inbracket = true;
			}
			else if (c == ')') {
				inbracket = false;
				auto it = dic.find(key);
				if (it == cend(dic)) {
					ans += '?';
				}
				else {
					ans += it->second;
				}
				key.clear();
			}
			else {
				if (inbracket) {
					key += c;
				}
				else {
					ans += c;
				}
			}
		}


		return ans;
	}
};

static void test(string s, vector<vector<string>>&& knowledge) {
	cout << Solution().evaluate(s, knowledge) << endl;
}
int main() {
	test("(name)is(age)yearsold", get_matrix_str(R"([["name","bob"],["age","two"]])"));
	test("hi(name)", get_matrix_str(R"([["a","b"]])"));
	test("(a)(a)(a)aaa", get_matrix_str(R"([["a","yes"]])"));
	return 0;
}
