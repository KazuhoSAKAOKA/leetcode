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


    int maximumJumps(vector<int>& nums, int target) {
		const auto n = size(nums);
		set<long long> values(cbegin(nums), cend(nums));
		const auto m = size(values);
		size_t index = 0;
		map<long long, size_t> value_map;
		for (auto&& num : values) {
			value_map.insert({ num, index });
			index++;
		}
		seqment_tree_range_maximum_query<int> st(m + 1);
		constexpr int INF = INT_MAX / 2;
		vector<int> dp(n, INF);
		dp[0] = 0;
		auto get_lower_index = [&](int num)-> size_t {
			auto it_lower = value_map.lower_bound(static_cast<long long>(num) - target);
			if (it_lower == cend(value_map)) {
				return m;
			}
			return it_lower->second;
			};

		auto get_upper_index = [&](int num)-> size_t {
			auto it_upper = value_map.upper_bound(static_cast<long long>(num) + target);
			if (it_upper == cend(value_map)) {
				return m;
			}
			return it_upper->second;
			};
		st.update(value_map[nums[0]], 0);
		for (int i = 1; i < n; i++) {
			auto lower_index = get_lower_index(nums[i]);
			auto upper_index = get_upper_index(nums[i]);
			const auto past = st.query(lower_index, upper_index);
			if(past>=0){
				dp[i] = past + 1;
				st.update(value_map[nums[i]], dp[i]);
			}
		}
		return dp.back() == INF ? -1 : dp.back();
    }
};

static void test(vector<int>&& nums, int target) {
    cout << Solution().maximumJumps(nums, target) << endl;
}

int main() {
	test(get_list_int("[758043978,79060681,785252849,287889790,-983845055,224430896,-477101480]"), 1769097904);
	test(get_list_int("[1,3,6,4,1,2]"), 2);
    test(get_list_int("[1,3,6,4,1,2]"), 3);
    test(get_list_int("[1,3,6,4,1,2]"), 0);
    return 0;
}
