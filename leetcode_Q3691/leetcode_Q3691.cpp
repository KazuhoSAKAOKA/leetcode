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
		template <typename Container>
		seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	};
	template <typename T = long long>
	struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
		template <typename Container>
		seqment_tree_range_minimum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
	};
    long long maxTotalValue(vector<int>& nums, int k) {
		const int n = size(nums);
		using segtree_max = seqment_tree_range_maximum_query<int>;
		using segtree_min = seqment_tree_range_minimum_query<int>;
		segtree_max stmax(nums);
		segtree_min stmin(nums);

		using V = tuple<int, int, long long>;
		auto compair = [](const V& a, const V& b)->bool {
			return get<2>(a) < get<2>(b);
			};
		priority_queue<V, vector<V>, decltype(compair)> pq(compair);

		long long ans = 0;
		set<pair<int,int>> visited;
		visited.insert({ 0,n });
		pq.push({ 0, n, stmax.query(0,n) - stmin.query(0,n) });
		for (int i = 0; i < k; i++) {
			const auto v = pq.top();
			const auto [s, e, score] = v;
			pq.pop();
			ans += score;
			if (s + 1 < e) {
				const auto sn = s + 1;
				const auto en = e - 1;
				if (visited.count({ sn,e }) == 0) {
					pq.push({ sn, e, stmax.query(sn,e) - stmin.query(sn, e) });
					visited.insert({ sn,e });
				}
				if (visited.count({s, en }) == 0) {
					pq.push({ s, en, stmax.query(s,en) - stmin.query(s, en) });
					visited.insert({ s,en });
				}
			}
		}
		return ans;
    }
};

static void test(vector<int>&& nums, int k) {
	cout << Solution().maxTotalValue(nums, k) << endl;
}
int main() {
	test(get_list_int("[28,21,50,32]"), 10);
	test(get_list_int("[1,3,2]"), 2);
	test(get_list_int("[4,2,5,1]"), 3);
	return 0;
}
