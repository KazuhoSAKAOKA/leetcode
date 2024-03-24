// weekly_contest390.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <string>
#include <stack>
#include <optional>

using namespace std;


namespace problem1 {

class Solution {
public:
	int maximumLengthSubstring(string s) {
		unordered_map<char, int> counts_map;

		int forward = 0;
		int backward = 0;
		int max_len = 0;
		
		while (backward < s.size()) {
			while (forward < s.size()) {
				const auto occ = ++counts_map[s[forward]];
				forward++;
				if (occ < 3) {
					max_len = max(max_len, forward - backward);
				}
				else {
					break;
				}
			}

			while (backward < forward) {
				const auto occ = --counts_map[s[backward]];
				backward++;
				if (occ == 2) {
					break;
				}
			}
		}

		return max_len;
	}
};

void test(string&& s) {
	cout << Solution().maximumLengthSubstring(s) << endl;
}


void run() {
	test("bcbbbcba");
	test("aaaa");
}

}


namespace problem2 {

class Solution {
public:

	using memo_key_t = pair<int, int>;
	using memo_t = map<memo_key_t, int>;

	static int rec(int k, int currentValue, int currentNum, memo_t& memo) {
		if (k <= currentValue * currentNum) {
			return 0;
		}
		const auto key = memo_key_t(currentValue, currentNum);
		const auto it = memo.find(key);
		if (it != cend(memo)) {
			return it->second;
		}

		const auto v1 = rec(k, currentValue + 1, currentNum, memo) + 1;
		const auto v2 = rec(k, currentValue, currentNum + 1, memo) + 1;
		const auto value = min(v1, v2);
		memo[key] = value;
		return value;
	}

	int minOperations(int k) {
		int min_value = INT_MAX;
		const int m = static_cast<int>(sqrt(k)) + 1;
		for (int i = 1; i < m; i++) {
			const int j = ceil((double)k / i);
			min_value = min(min_value, i - 1 + j - 1);
		}
		return min_value;
	}
};

void test(int k) {
	cout << Solution().minOperations(k) << endl;
}


void run() {
	test(11);
	test(1);
	test(100000);
}

}


namespace problem3 {

class Solution {
public:
	vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
		vector<long long> ans(nums.size(), 0);

		unordered_map<int, long long> id_map;

		int max_id = 0;
		long long max_freq = 0;
		for (int i = 0; i < nums.size(); i++) {
			id_map[nums[i]] += freq[i];
			if (max_freq < id_map[nums[i]]) {
				max_freq = id_map[nums[i]];
				max_id = nums[i];
			}
			if (max_id == nums[i] && freq[i] < 0) {
				max_id = 0;
				max_freq = 0;
				for (auto&& [k, v] : id_map) {
					if (max_freq < v) {
						max_freq = v;
						max_id = k;
					}
				}
			}

			ans[i] = max_freq;
		}


		return ans;
	}
};

void test(vector<int>&& nums, vector<int>&& freq) {
	const auto ans = Solution().mostFrequentIDs(nums, freq);
	for (auto&& value : ans) {
		cout << value << ",";
	}
	cout << endl;
}


void run() {
	test({2,3,2,1}, {3,2,-3,1});
	test({ 5,5,3, }, {2,-2, 1});
}

}


namespace problem4 {

class Solution {
public:

	//int get_common_suffix(const string s, const string q) {
	//	const int len = min(s.size(), q.size());
	//	for (int i = 0; i < len; i++) {
	//		if (s[s.size() - i - 1] != q[q.size() - i - 1]) {
	//			return i;
	//		}
	//	}
	//	return len;
	//}

	struct trie {
		struct node {
			unordered_map<char, node> nexts_;
			vector<int> ids_;
		};
		node root_;
		trie(){
		}

		void insert_reversestr(const string& word, int id) {
			node* current = &root_;
			current->ids_.emplace_back(id);
			for (int i = 0; i < static_cast<int>(word.size()); i++) {
				auto* next_node = &current->nexts_[word[word.size() - i - 1]];
				current = next_node;
				current->ids_.emplace_back(id);
			}
		}

		pair<int, vector<int>> get_common_suffix_length(const string& word) {
			node* current = &root_;
			for (int i = 0; i < static_cast<int>(word.size()); i++) {
				const auto it = current->nexts_.find(word[word.size() - i - 1]);
				if (it == cend(current->nexts_)) {
					return make_pair(i, current->ids_);
				}
				auto& next_node = it->second;
				current = &next_node;
			}
			return make_pair(static_cast<int>(word.size()), current->ids_);
		}
	};


	vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
		vector<int> ans(wordsQuery.size(), 0);
		trie trie_container;
		for (int i = 0; i < wordsContainer.size(); i++) {
			trie_container.insert_reversestr(wordsContainer[i], i);
		}

		for (int i = 0; i < wordsQuery.size(); i++) {

			auto [len, ids] = trie_container.get_common_suffix_length(wordsQuery[i]);
			if (ids.empty()) {
				throw exception();
			}
			const auto it = min_element(cbegin(ids), cend(ids), [&](const auto& a, const auto& b) { return wordsContainer[a].size() < wordsContainer[b].size(); });

			ans[i] = *it;
		}


		return ans;
	}
};

void test(vector<string>&& wordsContainer, vector<string>&& wordsQuery) {
	const auto ans = Solution().stringIndices(wordsContainer, wordsQuery);
	for (auto&& value : ans) {
		cout << value << ",";
	}
	cout << endl;
}


void run() {
	test({ "abcd", "bcda" }, { "cdf", "afa" });

	test({ "abcd", "bcd", "xbcd" }, { "cd", "bcd", "xyz" });
	test({ "abcdefgh", "poiuygh", "ghghgh" }, { "gh", "acbfgh", "acbfegh" });
}

}



int main()
{
//	problem1::run();
//	problem2::run();
//	problem3::run();
	problem4::run();
}