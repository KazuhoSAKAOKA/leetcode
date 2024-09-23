// leetcode_Q2707.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

struct trie_tree {
	struct node {
		bool is_end_ = false;
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

	vector<size_t> get_candidates(const string& s, size_t offset) const {
		const node* current = &root_;
		vector<size_t> candidates;
		for (int i = offset; i < s.size(); i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it != cend(current->nodes_)) {
				current = (it->second);
				if (current->is_end_) {
					candidates.emplace_back(i - offset + 1);
				}
			}
			else {
				break;
			}
		}
		return candidates;
	}

};

class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
		trie_tree trie;
		for (auto&& word : dictionary) {
			trie.add(word);
		}
		vector<int> dp(size(s) + 1, INT_MAX);
		dp[0] = 0;
		for (size_t i = 0; i < size(s); i++) {
			dp[i + 1] = min(dp[i] + 1, dp[i + 1]);
			const auto candidates = trie.get_candidates(s, i);
			for (auto&& candidate : candidates) {
				dp[i + candidate] = min(dp[i], dp[i + candidate]);
			}
		}
		return dp.back();
    }
};

void test(string&& s, vector<string>&& dictionary) {
    cout << Solution().minExtraChar(s, dictionary) << endl;
}
int main()
{
	test("dwmodizxvvbosxxw", get_list_str(R"(["ox","lb","diz","gu","v","ksv","o","nuq","r","txhe","e","wmo","cehy","tskz","ds","kzbu"])"));
	test("leetscode", get_list_str(R"(["leet","code","leetcode"])"));
    test("sayhelloworld", get_list_str(R"(["hello","world"])"));
    return 0;
}