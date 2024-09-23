// leetcode_Q1858.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

struct trie_tree {
	struct node {
		bool is_end_;
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
		current->is_end_ = true;
	}

	bool check(const string& s) const {
		const node* current = &root_;
		for (int i = 0; i < s.size() - 1; i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it == cend(current->nodes_)) {
				return false;
			}
			current = (it->second);
			if (!current->is_end_) {
				return false;
			}
		}
		return true;
	}

};

class Solution {
public:
    string longestWord(vector<string>& words) {
		trie_tree trie;
		for (auto&& word : words) {
			trie.add(word);
		}
		auto compare = [](const auto& a, const auto& b) {
			if (size(a) != size(b)) {
				return size(a) < size(b);
			}
			return a > b;
			};
		priority_queue<string, vector<string>, decltype(compare)> pqueue(compare);
		for (auto&& word : words) {
			if (trie.check(word)) {
				pqueue.push(word);
			}
		}
		if (pqueue.empty()) {
			return "";
		}
		return pqueue.top();
    }
};

void test(vector<string>&& words) {
    cout << Solution().longestWord(words) << endl;
}

int main()
{
    test(get_list_str(R"(["k","ki","kir","kira", "kiran"])"));
    test(get_list_str(R"(["a", "banana", "app", "appl", "ap", "apply", "apple"])"));
    test(get_list_str(R"(["abc", "bc", "ab", "qwe"])"));
    return 0;
}