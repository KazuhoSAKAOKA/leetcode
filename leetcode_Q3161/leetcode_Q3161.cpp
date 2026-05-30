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
	template <typename T = long long>
	struct seqment_tree_range_maximum_query : public segment_tree<T, std::function<T(T, T)>> {
		seqment_tree_range_maximum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	};



    vector<bool> getResults(vector<vector<int>>& queries) {
		set<int> value_set;
		for (auto&& query : queries) {
			value_set.insert(query[1]);
		}
		vector<int> values(cbegin(value_set), cend(value_set));
		map<long long, size_t> mp;
		for (size_t i = 0; i < size(values); i++) {
			mp[values[i]] = i;
		}

		using seg_tree = seqment_tree_range_maximum_query<long long>;
		seg_tree st(size(values));
		map<int, long long> obstacles;

		auto get_prev = [](const map<int, long long>& omap, int value)->int {
			auto it_low = omap.lower_bound(value);
			if (it_low == cbegin(omap)) {
				return 0;
			}
			else {
				auto it_prev = prev(it_low);
				return it_prev->first;
			}
			};

		vector<bool> ans;
		for (auto&& query : queries) {
			if (query.front() == 1) {
				const auto pos = query[1];
				const auto st_index = mp[pos];
				auto it = obstacles.upper_bound(pos);
				if (it == cend(obstacles)) {
					long long len;
					if (obstacles.empty()) {
						len = pos;
					}
					else {
						auto ittail = rbegin(obstacles);
						len = pos - ittail->first;
					}
					obstacles.insert({ pos, len });
					st.update(st_index, len);
				}
				else {
					const long long upper_len = it->first - pos;
					long long len;
					if (it == cbegin(obstacles)) {
						len = pos;
					}
					else {
						auto itbefore = prev(it);
						len = pos - itbefore->first;
					}
					st.update(mp[it->first], upper_len);
					st.update(st_index, len);
					obstacles.insert({ pos, len });
					it->second = upper_len;
				}
			}
			else {
				const auto pos = query[1];
				const auto sz = query[2];
				if (obstacles.empty()) {
					ans.push_back(sz <= pos);
				}
				else {
					const auto prev_pos = get_prev(obstacles, pos);
					if (sz <= pos - prev_pos) {
						ans.push_back(true);
					}
					else {
						const auto it = lower_bound(cbegin(values), cend(values), pos);
						const auto st_index = distance(cbegin(values), it);
						auto len = st.query(0, st_index);
						ans.push_back(sz <= len);
					}
				}
			}
		}


		return ans;
    }
};

static void test(vector<vector<int>>&& queries) {
    output(Solution().getResults(queries));
}

int main() {
    //test(get_matrix_int("[[1,2],[2,3,3],[2,3,1],[2,2,2]]"));
    test(get_matrix_int("[[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]"));

    return 0;
}