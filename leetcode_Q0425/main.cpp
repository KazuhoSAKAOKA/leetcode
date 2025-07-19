#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

	struct trie_tree {
		struct node {
			vector<size_t> indexes_;
			std::unordered_map<char, node*> nodes_;
		};
		node root_;
		vector<size_t> empty_;
		void add(const std::string& s, size_t index) {
			node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					it->second->indexes_.emplace_back(index);
					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
					itnew->second->indexes_.emplace_back(index);
					current = (itnew->second);
				}
			}
		}

		const vector<size_t> get_list(const std::string& s) const {
			const node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it == cend(current->nodes_)) {
					return empty_;
				}
				current = (it->second);
			}
			return current->indexes_;
		}

	};

	static string get_prefix(const vector<string>& words, const vector<size_t>& current_list) {
		string s;
		const auto m = size(current_list);
		for (auto&& index : current_list) {
			s += words[index][m];
		}
		return s;
	}
	static void rec(size_t len, const trie_tree& trie, const vector<string>& words, const vector<size_t>& candidates, vector<size_t>& current_list, vector<vector<string>>& ans) {

		if (size(current_list) == len) {
			vector<string> str_list;
			for (auto&& index : current_list) {
				str_list.emplace_back(words[index]);
			}
			ans.emplace_back(str_list);
		}

		for (auto&& index : candidates) {
			current_list.emplace_back(index);
			const auto& next_candidates = trie.get_list(get_prefix(words, current_list));
			rec(len, trie, words, next_candidates, current_list, ans);
			current_list.pop_back();
		}
	}

    vector<vector<string>> wordSquares(vector<string>& words) {
		trie_tree trie;
		const auto n = size(words);
		vector<size_t> all_indexes;
		for (size_t i = 0; i < n; i++) {
			trie.add(words[i], i);
			all_indexes.emplace_back(i);
		}
		const auto len = size(words[0]);
		vector<vector<string>> ans;
		vector<size_t> current_list;
		rec(len, trie, words, all_indexes, current_list, ans);
		return ans;
    }
};

static void test(vector<string>&& words) {
    output_matrix(Solution().wordSquares(words));
}
int main() {
	test(get_list_str(R"(["abat","baba","atan","atal"])"));
	test(get_list_str(R"(["ab","ba"])"));
	test(get_list_str(R"(["area","lead","wall","lady","ball"])"));
	return 0;
}