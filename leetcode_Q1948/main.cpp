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
			std::map<string, node*> nodes_;
			string key_;
		};
		node root_;

		void add(const vector<string>& s) {
			node* current = &root_;
			for (int i = 0; i < size(s); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
					current = (itnew->second);
				}
			}
		}


		static string dfs(node* cur_node,  map<string, int>& underlyings) {
			if (cur_node == nullptr) { return ""; }
			string s;
			for (auto&& [k, child_node] : cur_node->nodes_) {
				const auto temp = dfs(child_node, underlyings);
				s += k + "[" + temp + "]";
			}
			if (!s.empty()) {
				underlyings[s]++;
			}
			cur_node->key_ = s;
			return s;
		}

		void get_underlyings(map<string, int>& underlyings) {
			dfs(&root_, underlyings);
		}

		static void dfs_ans(vector<string>& cur_key, const node* cur_node, vector<vector<string>>& ans, const set<string>& duplicates) {
			if (cur_node == nullptr) { return; }
			if (cur_node->nodes_.empty()) {
				ans.emplace_back(cur_key);
				return;
			}
			if (duplicates.find(cur_node->key_) != cend(duplicates)) {
				return;
			}
			for (auto&& [k, child_node] : cur_node->nodes_) {
				cur_key.emplace_back(k);
				dfs_ans(cur_key, child_node, ans, duplicates);
				cur_key.pop_back();
			}
			if (!cur_key.empty()) {
				ans.emplace_back(cur_key);
			}
		}
		void get_ans(vector<vector<string>>& ans, const set<string>& duplicates) const {
			vector<string> cur_key;
			dfs_ans(cur_key, &root_, ans, duplicates);
		}

	};
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths)  {
		trie_tree trie;
		for (auto&& path : paths) {
			trie.add(path);
		}
		map<string, int> underlyings;
		trie.get_underlyings(underlyings);
		
		set<string> duplicates;
		for (auto&& [k, v] : underlyings) {
			if (v > 1) {
				duplicates.insert(k);
			}
		}
		vector<vector<string>> ans;
		trie.get_ans(ans, duplicates);
		return ans;
    }
};

static void test(vector<vector<string>>&& paths) {
    output_matrix(Solution().deleteDuplicateFolder(paths));
}
int main() {
	test(get_matrix_str(R"([["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]])"));



	//test(get_matrix_str(R"([["a"],["a","x"],["a","x","y"],["a","z"],["b"],["b","x"],["b","x","y"],["b","z"]])"));
	//test(get_matrix_str(R"([["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]])"));
 //   test(get_matrix_str(R"([["a","b"],["c","d"],["c"],["a"]])"));
    return 0;
}