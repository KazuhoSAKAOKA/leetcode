// weekly_contest_405.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {

class Solution {
public:
	string getEncryptedString(string s, int k) {
		auto get_char = [&](int i) {
			const int index = (i + s.size() + k) % s.size();
			return s[index];
			};

		string ans;
		ans.reserve(s.size());
		for (int i = 0; i < s.size(); i++) {
			ans += get_char(i);
		}
		return ans;
	}
};

void test(string&& s, int k) {
	cout << Solution().getEncryptedString(s, k) << endl;
}
void run() {
	test("dart", 3);
	test("aaa", 1);
}
}

namespace problem2 {
class Solution {
public:

	static void rec(int n, int index, string& current, vector<string>& ans) {
		if (n == index) {
			ans.push_back(current);
			return;
		}

		if (current.empty() || current.back() == '1') {
			current += '0';
			rec(n, index + 1, current, ans);
			current.pop_back();
		}
		current += '1';
		rec(n, index + 1, current, ans);
		current.pop_back();
	}

	vector<string> validStrings(int n) {
		vector<string> ans;
		string current;
		rec(n, 0, current, ans);
		return ans;
	}
};

void test(int n) {
	const auto ans = Solution().validStrings(n);
	for (auto&& value : ans) {
		cout << value << ",";
	}
	cout << endl;
}
void run() {
	test(3);
	test(1);
}
}

namespace problem3 {
class Solution {
public:

	static int get_prefix(const vector<vector<int>>& prefix_sum, int i, int j) {
		return prefix_sum[i + 1][j + 1];
	}

	int numberOfSubmatrices(vector<vector<char>>& grid) {
		const size_t y = grid.size();
		const size_t x = grid.front().size();
		vector<vector<int>> prefix_sum_x(y + 1, vector<int>(x + 1));
		vector<vector<int>> prefix_sum_y(y + 1, vector<int>(x + 1));
		auto get_count = [&](char c, char expect) {
			return c == expect ? 1 : 0;
			};
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				prefix_sum_x[i + 1][j + 1] = prefix_sum_x[i + 1][j] + get_count(grid[i][j], 'X');
				prefix_sum_y[i + 1][j + 1] = prefix_sum_y[i + 1][j] + get_count(grid[i][j], 'Y');
			}
		}

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				prefix_sum_x[i + 1][j + 1] += prefix_sum_x[i][j + 1];
				prefix_sum_y[i + 1][j + 1] += prefix_sum_y[i][j + 1];
			}
		}
		int count = 0;

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				const auto xcount = get_prefix(prefix_sum_x, i, j);
				if (xcount > 0 && xcount == get_prefix(prefix_sum_y, i, j)) {
					count++;
				}
			}
		}
		
		return count;
	}
};
void test(vector<vector<char>>&& grid) {
	cout << Solution().numberOfSubmatrices(grid) << endl;
}
void run() {
	test(get_matrix_char(R"([["X","Y","."],["Y",".","."]])"));
	test(get_matrix_char(R"([["X","X"],["X","Y"]])"));
	test(get_matrix_char(R"([[".","."],[".","."]])"));
}
}

namespace problem4 {
class Solution {
public:


	static int tle(const string& target, const vector<string>& words, const vector<int>& costs, int index, vector<int>& memo) {
		if (target.size() < index) {
			return INT_MAX;
		}
		if (target.size() == index) {
			return 0;
		}
		if (memo[index] != INT_MAX - 1) {
			return memo[index];
		}
		int min_cost = INT_MAX;
		for (int i = 0; i < words.size(); i++) {
			const auto& word = words[i];
			if (word.size() + index <= target.size()) {
				if (target.compare(index, word.size(), word) == 0) {
					const auto cost = tle(target, words, costs, index + word.size(), memo);
					if (cost != INT_MAX) {
						min_cost = min(min_cost, cost + costs[i]);
					}
				}
			}
		}
		memo[index] = min_cost;
		return min_cost;
	}
	/*
	static int rec(const string& target, const trie_tree& trie, int index, vector<int>& memo) {
		if (target.size() < index) {
			return INT_MAX;
		}
		if (target.size() == index) {
			return 0;
		}
		if (memo[index] != INT_MAX - 1) {
			return memo[index];
		}
		int min_cost = INT_MAX;
		const auto list = trie.search(target, index);
		for (auto&& [new_index, mycost] : list) {
			const auto cost = rec(target, trie, new_index, memo);
			if (cost != INT_MAX) {
				min_cost = min(min_cost, cost + mycost);
			}
		}
		memo[index] = min_cost;
		return min_cost;
	}
	*/

	struct trie_tree {
		struct node {
			int cost_ = INT_MAX;
			unordered_map<char, node*> nodes_;
		};
		node root_;

		void add(const std::string& s, int cost) {
			node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
					current = (itnew->second);
				}
			}
			current->cost_ = min(current->cost_, cost);
		}

		vector<pair<int, int>> search(const std::string& s, int index) const {
			vector<pair<int, int>> index_costs;
			const node* current = &root_;
			for (int i = index; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
					if (current->cost_ != INT_MAX) {
						index_costs.push_back({ i + 1, current->cost_ });
					}
				}
				else {
					break;
				}
			}
			return index_costs;
		}
	};


	int minimumCost(string target, vector<string>& words, vector<int>& costs) {
		vector<int> memo(target.size() + 1, INT_MAX);
		trie_tree trie;
		for (int i = 0; i < words.size(); i++) {
			trie.add(words[i], costs[i]);
		}
		memo[0] = 0;
		for (int i = 0; i < target.size(); i++) {
			if (memo[i] != INT_MAX) {
				const auto list = trie.search(target, i);
				for (auto&& [new_index, mycost] : list) {
					memo[new_index] = min(memo[new_index], mycost + memo[i]);
				}
			}
		}

		if (memo[target.size()] >= INT_MAX) {
			return -1;
		}
		return memo[target.size()];
	}
};
void test(string&& target, vector<string>&& words, vector<int>&& costs) {
	cout << Solution().minimumCost(target, words, costs) << endl;
}
void run() {
	test("wvgafw", get_list_str(R"(["wvgafw","w"])"), get_list_int("[1,2]"));
	test("abcdef", get_list_str(R"(["abdef","abc","d","def","ef"])"), get_list_int("[100,1,1,10,5]"));
	test("r", get_list_str(R"(["r","r","r","r"])"), get_list_int("[1,6,3,3]"));

	test("aaaaa", get_list_str(R"(["a","aa","aaa"])"), get_list_int("[1,10,100]"));
	test("aaaa", get_list_str(R"(["z","zz","zzz"])"), get_list_int("[1,10,100]"));
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