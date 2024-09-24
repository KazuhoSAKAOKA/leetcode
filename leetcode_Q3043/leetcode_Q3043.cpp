// leetcode_Q3043.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <unordered_map>
#include <string>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


struct trie_tree {
	struct node {
		std::unordered_map<char, node*> nodes_;
	};
	node root_;

	void add(const std::string& s) {
		node* current = &root_;
		for (size_t i = 0; i < s.size(); i++) {
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
	size_t get_length(const std::string& s) const {
		const node* current = &root_;
		for (size_t i = 0; i < s.size(); i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it == cend(current->nodes_)) {
				return i;
			}
			current = (it->second);
		}
		return size(s);
	}

};

class Solution {
public:

    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
		trie_tree trie;
		for (auto&& value : arr2) {
			trie.add(to_string(value));
		}

		size_t max_len = 0;
		for (auto&& value : arr1) {
			max_len = max(max_len, trie.get_length(to_string(value)));
		}
		return static_cast<int>(max_len);
    }
};

void test(vector<int>&& arr1, vector<int>&& arr2) {
	cout << Solution().longestCommonPrefix(arr1, arr2) << endl;
}

int main()
{
	test(get_list_int("[1,10,100]"), get_list_int("[1000]"));
	test(get_list_int("[1,2,3]"), get_list_int("[4,4,4]"));
	return 0;
}