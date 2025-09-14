#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

	static bool isvowel(char c) {
		return c == 'a' ||
			c == 'i' ||
			c == 'u' ||
			c == 'e' ||
			c == 'o';
	}

	static bool eq_cap(const string& v1, const string v2) {
		if (size(v1)!= size(v2)) { return false; }
		for (int i = 0; i < size(v1); i++) {
			if (toupper(v1[i]) != toupper(v2[i])) {
				return false;
			}
		}
		return true;
	}


	struct trie_tree {
		struct node {
			std::unordered_map<char, node*> nodes_;
			vector<string> words_;
		};
		node root_;
		void add(const std::string& s) {
			node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const char c = tolower(s[i]);
				const char c1 = isvowel(c) ? '_' : c;
				const auto it = current->nodes_.find(c1);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(c1, new node()));
					current = (itnew->second);
				}
			}
			current->words_.emplace_back(s);
		}

		string find(const std::string& s) const {
			const node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const char c = tolower(s[i]);
				const char c1 = isvowel(c) ? '_' : c;
				const auto it = current->nodes_.find(c1);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					return "";
				}
			}
			if (current->words_.empty()) { return ""; }
			for (auto&& word : current->words_) {
				if (word == s) {
					return word;
				}
			}
			for (auto&& word : current->words_) {
				if (eq_cap(word, s)) {
					return word;
				}
			}
			return current->words_[0];
		}

	};
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
		trie_tree trie;
		for (auto&& word : wordlist) {
			trie.add(word);
		}
		vector<string> ans;
		ans.reserve(size(queries));

		for (auto&& query : queries) {
			ans.emplace_back(trie.find(query));
		}

		return ans;
    }
};

static void test(vector<string>&& wordlist, vector<string>&& queries) {
	output(Solution().spellchecker(wordlist, queries));
}
int main() {
	test(get_list_str(R"(["KiTe","kite","hare","Hare"])"), get_list_str(R"(["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"])"));
	test(get_list_str(R"(["yellow"])"), get_list_str(R"(["YellOw"])"));
	return 0;
}