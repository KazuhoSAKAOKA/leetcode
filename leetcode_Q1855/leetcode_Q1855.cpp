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
		template <typename Container>
		seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	};

public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        const auto n = size(nums1);
		map<long long, size_t> mp;
		for (auto&& num : nums2) {
			mp[num] = 0;
		}
		const auto m = size(mp);
		size_t index = 0;
		for (auto&& [num, ind] : mp) {
			ind = index++;
		}

		using seg_tree = seqment_tree_range_maximum_query<size_t>;
		seg_tree st(m);
		for (size_t j = 0; j < size(nums2); j++) {
			st.update(mp[nums2[j]], j);
		}

        long long max_distance = 0;

		for (size_t i = 0; i < n; i++) {
			const auto it = mp.lower_bound(nums1[i]);
			if (it != cend(mp)) {
				const auto target_index = it->second;
				const auto target_j = st.query(target_index, m);
				if (i <= target_j) {
					max_distance = max(max_distance, static_cast<long long>(target_j - i));
				}
			}
        }
        return static_cast<int>(max_distance);
    }
};

static void test(vector<int>&& nums1, vector<int>&& nums2) {
    cout << Solution().maxDistance(nums1, nums2) << endl;
}

int main() {
	test(get_list_int("[5,4]"), get_list_int("[3,2]"));
	test(get_list_int("[55,30,5,4,2]"), get_list_int("[100,20,10,10,5]"));
    test(get_list_int("[2,2,2]"), get_list_int("[10,10,1]"));
    test(get_list_int("[30,29,19,5]"), get_list_int("[25,25,25,25,25]"));
    return 0;
}
