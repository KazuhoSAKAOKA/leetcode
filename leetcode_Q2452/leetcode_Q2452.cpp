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
class Solution {
public:


	struct trie_tree {
		struct node {
			std::unordered_map<char, node*> nodes_;
		};
		node root_;

		void add(const std::string& s) {
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
		}
		bool exist(const string& s, size_t index, const node* node_ptr, size_t remain_change) const {
			if (index == size(s)) {
				return true;
			}
			for (auto&& [c, ptr] : node_ptr->nodes_) {
				if (c == s[index]) {
					if (exist(s, index + 1, ptr, remain_change)) {
						return true;
					}
				}
				else {
					if(remain_change>0){
						if (exist(s, index + 1, ptr, remain_change - 1)) {
							return true;
						}
					}
				}
			}
			return false;
		}
		bool exist(const string& s, size_t remain_change) const {
			return exist(s, 0, &root_, remain_change);
		}
	};

    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
		trie_tree trie;
		for (auto&& word : dictionary) {
			trie.add(word);
		}
		vector<string> ans;
		for (auto&& query : queries) {
			if (trie.exist(query, 2)) {
				ans.push_back(query);
			}
		}

		return ans;
    }
};

static void test(vector<string>&& queries, vector<string>&& dictionary) {
    output(Solution().twoEditWords(queries, dictionary));
}

int main() {
	test(get_list_str(R"(["word","note","ants","wood"])"), get_list_str(R"(["wood","joke","moat"])"));
	test(get_list_str(R"(["yes"])"), get_list_str(R"(["not"])"));
	return 0;
}
