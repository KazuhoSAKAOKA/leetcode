#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:
	struct trie_tree {
		struct node {
			map<char, node*> nodes_;
		};
		node root_;

		void add(const std::string& s, size_t offset, size_t len) {
			node* current = &root_;
			for (int i = 0; i < len; i++) {
				const auto it = current->nodes_.find(s[i + offset]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i + offset], new node()));
					current = (itnew->second);
				}
			}
		}

		string get_largest_string() const {
			string ans;
			const node* current = &root_;
			while (current != nullptr && !current->nodes_.empty()) {
				const auto it = crbegin(current->nodes_);
				ans += it->first;
				current = it->second;
			}
			return ans;
		}

	};

	static string mle(string word, int numFriends) {
		if (numFriends == 1) {
			return word;
		}
		const auto n = size(word);
		trie_tree trie;
		const size_t max_len = n - static_cast<size_t>(numFriends - 1);
		for (size_t i = 0; i < n; i++) {
			trie.add(word, i, min(n - i, max_len));
		}
		return trie.get_largest_string();
	}

	string answerString(string word, int numFriends) {
		if (numFriends == 1) {
			return word;
		}
		const auto n = size(word);
		const size_t max_len = n - static_cast<size_t>(numFriends - 1);
		auto check = [&](const string& current_max, size_t offset)->bool {
			for (size_t i = 0; i < min(min(n - i, max_len), size(current_max)); i++) {
				if (current_max[i] > word[offset + i]) {
					return false;
				}
				else if (current_max[i] < word[offset + i]) {
					return true;
				}
			}
			return size(current_max) < max_len;
			};

		string current_max = word.substr(0, max_len);
		for (size_t i = 1; i < n; i++) {
			if (check(current_max, i)) {
				current_max = word.substr(i, min(n - i, max_len));
			}
		}
		return current_max;
	}
};

void test(string&& word, int numFriends) {
	cout << Solution().answerString(word, numFriends) << endl;
}

int main() {
	test("gh", 1);
	test("bif", 2);
	test("dbca", 2);
	test("gggg", 4);
	return 0;
}