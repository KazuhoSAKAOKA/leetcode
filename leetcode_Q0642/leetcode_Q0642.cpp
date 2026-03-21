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

class AutocompleteSystem {

	struct trie_tree {
		struct node {
			size_t ended_count_;
			unordered_map<char, node*> nodes_;
			map<size_t, set<char>, greater<size_t>> count_map_;
		};
		node root_;


		void add(const std::string& s, size_t count) {
			node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);

				auto& mp = current->count_map_;
				size_t cur_count = count;
				for (auto&& [count, chars] : mp) {
					auto it1 = chars.find(s[i]);
					if (it1 != cend(chars)) {
						cur_count += count;
						chars.erase(it1);
						if (chars.empty()) {
							mp.erase(count);
						}
						break;
					}
				}
				mp[cur_count].insert(s[i]);

				if (it != cend(current->nodes_)) {

					current = (it->second);
				}
				else {
					auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
					current = (itnew->second);
				}
			}
			current->ended_count_ += count;
		}
		static void dfs(string& temp, const node* current, map<size_t, set<string>, greater<size_t>>& cur_map) {
			if (current == nullptr) {
				return;
			}
			if (current->ended_count_ > 0) {
				cur_map[current->ended_count_].insert(temp);
			}
			for (auto&& [_, chars] : current->count_map_) {
				for (auto&& c : chars) {
					temp.push_back(c);
					dfs(temp, current->nodes_.at(c), cur_map);
					temp.pop_back();
				}
			}
		}
		vector<string> search(const std::string& s) {
			const node* current = &root_;
			for (int i = 0; i < s.size(); i++) {
				const auto it = current->nodes_.find(s[i]);
				if (it != cend(current->nodes_)) {
					current = (it->second);
				}
				else {
					return {};
				}
			}
			string temp(s);
			map<size_t, set<string>, greater<size_t>> cur_map;
			dfs(temp, current, cur_map);
			vector<string> ans;
			[&]() {
				for (auto&& [_, ss] : cur_map) {
					for (auto&& s : ss) {
						ans.emplace_back(s);
						if (size(ans) == 3) {
							return;
						}
					}
				}
				}();
			return ans;
		}

	};
	trie_tree trie_;
	string current_query_;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
		for (size_t i = 0; i < size(sentences); i++) {
			trie_.add(sentences[i], times[i]);
		}
    }

    vector<string> input(char c) {
		if (c == '#') {
			trie_.add(current_query_, 1);
			current_query_.clear();
			return {};
		}
		current_query_.push_back(c);
		return trie_.search(current_query_);
    }
};

static void test1() {
	cout << "test1" << endl;
	auto a1 = get_list_str(R"(["i love you", "island", "iroman", "i love leetcode"])");
	auto a2 = get_list_int("[5, 3, 2, 2]");
	AutocompleteSystem as(a1, a2);
	output(as.input('i'));
	output(as.input(' '));
	output(as.input('a'));
	output(as.input('#'));
}
static void test2() {
	cout << "test2" << endl;
	auto a1 = get_list_str(R"(["i love you","island","iroman","i love leetcode"])");
	auto a2 = get_list_int("[5, 3, 2, 2]");
	AutocompleteSystem as(a1, a2);
	output(as.input('i'));
	output(as.input(' '));
	output(as.input('a'));
	output(as.input('#'));
	output(as.input('i'));
	output(as.input(' '));
	output(as.input('a'));
	output(as.input('#'));
	output(as.input('i'));
	output(as.input(' '));
	output(as.input('a'));
	output(as.input('#'));
}

int main(){
	//test1();
	test2();
	return 0;
}