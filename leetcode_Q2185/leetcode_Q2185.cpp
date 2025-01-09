// leetcode_Q2185.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct trie_tree {
	struct node {
		size_t count_ = 0;
		std::unordered_map<char, node*> nodes_;
	};
	node root_;

	void add(const std::string& s) {
		node* current = &root_;
		for (int i = 0; i < s.size(); i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it != cend(current->nodes_)) {
				it->second->count_++;
				current = (it->second);
			}
			else {
				auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
				itnew->second->count_++;
				current = (itnew->second);
			}
		}
	}

	int get_count(const string& s) const {
		const node* current = &root_;
		for (int i = 0; i < s.size(); i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it == cend(current->nodes_)) {
				return 0;
			}
			current = (it->second);
		}
		return current->count_;
	}
};
class Solution {
public:
	int prefixCount(vector<string>& words, string pref) {
		trie_tree trie;
		for (auto&& word : words) {
			trie.add(word);
		}

		const auto ans = trie.get_count(pref);
		return ans;
	}
};

int main()
{

	return 0;
}