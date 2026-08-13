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
class Solution {
public:


	template <typename T, typename Q>
	struct segment_tree {
		T inf_;
		vector<T> data_;
		Q query_;
		size_t n_;

		segment_tree(size_t n, Q query, T inf)
			: inf_(inf), query_(query) {
			n_ = 1;
			while (n_ < n) {
				n_ <<= 1;
			}
			data_.assign(2 * n_, inf_);
		}

		template<typename Container>
		segment_tree(Container& source, Q query, T inf)
			: inf_(inf), query_(query) {
			size_t n = size(source);
			n_ = 1;
			while (n_ < n) {
				n_ <<= 1;
			}
			data_.assign(2 * n_, inf_);
			build(cbegin(source), cend(source));
		}

		template<typename IT>
		void build(IT b, IT e) {
			size_t len = std::distance(b, e);
			for (size_t i = 0; i < len; i++) {
				data_[n_ + i] = *(b + i);
			}
			for (size_t i = n_ - 1; i > 0; i--) {
				data_[i] = query_(data_[i << 1], data_[(i << 1) | 1]);
			}
		}

		void update(size_t index, T value) {
			size_t i = index + n_;
			data_[i] = value;
			while (i > 1) {
				i >>= 1;
				data_[i] = query_(data_[i << 1], data_[(i << 1) | 1]);
			}
		}

		T query(size_t a, size_t b) {
			return query(a, b, 1, 0, n_);
		}

		T query(size_t a, size_t b, size_t index, size_t l, size_t r) {
			if (r <= a || b <= l) {
				return inf_;
			}
			if (a <= l && r <= b) {
				return data_[index];
			}
			size_t mid = (l + r) >> 1;
			T vl = query(a, b, index << 1, l, mid);
			T vr = query(a, b, (index << 1) | 1, mid, r);
			return query_(vl, vr);
		}
	};


	static void dec_freq_map(map<int, int, greater<int>>& mp, int value) {
		auto it = mp.find(value);
		if (it->second == 1) {
			mp.erase(it);
		}
		else {
			it->second--;
		}
	}

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
		const int n = size(s);
		set<pair<int, int>> segments;
		multiset<int, greater<int>> lengths;
		char cur_char = s[0];
		int cur_left = 0;
		for (int i = 1; i < n; i++) {
			if (cur_char != s[i]) {
				segments.insert({cur_left, i-1});
				lengths.insert(i - cur_left);
				cur_left = i;
				cur_char = s[i];
			}
		}
		segments.insert({ cur_left, n - 1 });
		lengths.insert(n - cur_left);

		const int m = size(queryIndices);
		vector<int> ans;
		ans.reserve(m);

		for (int i = 0; i < m; i++) {
			const auto pos = queryIndices[i];
			const auto new_char = queryCharacters[i];
			if (s[pos] != new_char) {
				
				auto it = segments.upper_bound({ pos, INT_MAX });
				--it;
				int L = it->first, R = it->second;
				segments.erase(it);
				lengths.erase(lengths.find(R - L + 1));

				if (L <= pos - 1) {
					segments.insert({ L, pos - 1 });
					lengths.insert(pos - L);
				}
				if (pos + 1 <= R) {
					segments.insert({ pos + 1, R });
					lengths.insert(R - pos);
				}

				int newL = pos, newR = pos;

				auto rightIt = segments.lower_bound({ pos + 1, 0 });
				if (rightIt != segments.end() && rightIt->first == pos + 1 &&
					s[pos + 1] == new_char) {
					lengths.erase(lengths.find(rightIt->second - rightIt->first + 1));
					newR = rightIt->second;
					segments.erase(rightIt);
				}

				auto leftIt = segments.lower_bound({ pos, 0 });
				if (leftIt != segments.begin()) {
					--leftIt;
					if (leftIt->second == pos - 1 && s[pos - 1] == new_char) {
						lengths.erase(lengths.find(leftIt->second - leftIt->first + 1));
						newL = leftIt->first;
						segments.erase(leftIt);
					}
				}

				segments.insert({ newL, newR });
				lengths.insert(newR - newL + 1);
				s[pos] = new_char;
			}

			ans.push_back(*cbegin(lengths));
		}
		return ans;
    }
};
static void test(string&& s, string&& queryCharacters, vector<int>&& queryIndices) {
    output(Solution().longestRepeating(s, queryCharacters, queryIndices));
}

int main() {
    //test("babacc", "bcb", get_list_int("[1,3,3]"));
    test("abyzz", "aa", get_list_int("[2,1]"));
    return 0;
}
