// leetcode_Q2416.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

#include "./../utility/leetcode_testcase_helper.h"

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

	size_t get_sum(const std::string& s) const {
		size_t total = 0;
		const node* current = &root_;
		for (int i = 0; i < s.size(); i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it == cend(current->nodes_)) {
				return total;
			}
			current = (it->second);
			total += current->count_;
		}
		return total;
	}

};

class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
		trie_tree trie;
		for (auto&& word : words) {
			trie.add(word);
		}
		vector<int> ans;
		ans.reserve(size(words));
		for (auto&& word : words) {
			ans.emplace_back(trie.get_sum(word));
		}
		return ans;
    }
};

void test(vector<string>&& words) {
    output(Solution().sumPrefixScores(words));
}

int main()
{
    test(get_list_str(R"(["abc","ab","bc","b"])"));
    test(get_list_str(R"(["abcd"])"));

    return 0;
}