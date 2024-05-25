// leetcode_Q0140.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;




class Solution {
	struct trie_tree {
		struct node {
			size_t count_ = 0;
			std::unordered_map<char, node> nodes_;
		};
		node root_;

		void add(const std::string& s) {
			node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = &(it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], node()));
					current = &(itnew->second);
				}
			}
			current->count_++;
		}

		int count(const std::string& s, int offset, int length) const {
			const node* current = &root_;
			for (int i = 0; i < length; i++) {
				const auto it = current->nodes_.find(s[i + offset]);
				if (it == cend(current->nodes_)) {
					return false;
				}
				current = &(it->second);
			}
			return current->count_;
		}
	};

public:

	static void rec(const string& s, int before, int index, const trie_tree& trie, vector<string>& current, vector<string>& ans) {
		if (s.size() == before) {
			string temp;
			for (int i = 0; i < current.size() - 1; i++) {
				temp += current[i] + ' ';
			}
			temp += current.back();
			ans.emplace_back(temp);
			return;
		}
		if (s.size() <= index) {
			return;
		}

		rec(s, before, index + 1, trie, current, ans);
		
		int count = trie.count(s, before, index - before + 1);
		if (0 < count) {
			const auto ss = s.substr(before, index - before + 1);
			current.emplace_back(ss);
			rec(s, index + 1, index + 1, trie, current, ans);
			current.pop_back();
		}
	}

    vector<string> wordBreak(string s, vector<string>& wordDict) {
		trie_tree trie;
		for (auto&& word : wordDict) {
			trie.add(word);
		}
		vector<string> ans;
		vector<string> current;
		unordered_map<string, int> used_counts;
		rec(s, 0, 0, trie, current, ans);

		return ans;
    }
};


void test(string&& s, vector<string>&& wordDict) {
    const auto ans = Solution().wordBreak(s, wordDict);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
	test("abc", get_list_str(R"(["abc"])"));

    test("catsanddog", get_list_str(R"(["cat","cats","and","sand","dog"])"));
    test("pineapplepenapple", get_list_str(R"(["apple","pen","applepen","pine","pineapple"])"));
    test("catsandog", get_list_str(R"(["cats","dog","sand","and","cat"])"));
}