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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
	template <typename T, typename Q>
	struct segment_tree {
		T inf_;
		std::vector<std::vector<T>> data_;
		Q query_;

		segment_tree(size_t n, Q query, T inf) :query_(query), inf_(inf) {
			allocate_buffer(n);
		}
		template<typename Container>
		segment_tree(Container& source, Q query, T inf) : query_(query), inf_(inf) {
			const size_t n = source.size();
			allocate_buffer(n);
			build(cbegin(source), cend(source));
		}

		void allocate_buffer(size_t n) {
			size_t count = 1;
			for (;;) {
				data_.emplace_back(std::vector<T>(count, inf_));
				if (n <= count) {
					break;
				}
				count *= 2;
			}
		}

		template<typename IT>
		void build(IT begin, IT end) {
			size_t index = 0;
			for (auto it = begin; it != end; ++it) {
				data_[data_.size() - 1][index++] = *it;
			}
			for (size_t depth_index = data_.size() - 1; depth_index > 0; depth_index--) {
				const auto& source = data_[depth_index];
				auto& destination = data_[depth_index - 1];
				for (size_t i = 0; i < destination.size(); i++) {
					destination[i] = query_(source[i * 2], source[i * 2 + 1]);
				}
			}
		}

		void update(size_t index, T value) {
			data_[data_.size() - 1][index] = value;
			for (size_t depth_index = data_.size() - 1; depth_index > 0; --depth_index) {
				index /= 2;
				data_[depth_index - 1][index] = query_(data_[depth_index][index * 2], data_[depth_index][index * 2 + 1]);
			}
		}

		T query(size_t a, size_t b) {
			return query(a, b, 0, 0, 0, data_.back().size());
		}

		T query(size_t a, size_t b, size_t depth_index, size_t index, size_t l, size_t r) {
			if (r <= a || b <= l) {
				return inf_;
			}
			if (a <= l && r <= b) {
				return data_[depth_index][index];
			}
			const auto left = query(a, b, depth_index + 1, index * 2, l, (l + r) / 2);
			const auto right = query(a, b, depth_index + 1, index * 2 + 1, (l + r) / 2, r);
			return query_(left, right);
		}


	};

	template <typename T = long long>
	struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
		seqment_tree_range_minimum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
		template <typename Container>
		seqment_tree_range_minimum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
	};


    long long maximumScore(vector<int>& nums) {
		const auto n = size(nums);
		seqment_tree_range_minimum_query<long long> st(nums);
		long long max_score = LLONG_MIN;
		long long prefix = 0LL;
		for (int i = 0; i < size(nums) - 1; i++) {
			prefix += nums[i];
			const auto suffix = st.query(i + 1, n);
			max_score = max(max_score, prefix - suffix);
		}

        return max_score;
    }
}; 
static void test(vector<int>&& nums) {
    cout << Solution().maximumScore(nums) << endl;
}
static void run() {
    test(get_list_int("[10,-1,3,-4,-5]"));
    test(get_list_int("[-7,-5,3]"));
    test(get_list_int("[1,1]"));
}

}

namespace problem2 {
class Solution {
public:
	long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
		if (costBoth <= cost1 && costBoth <= cost2) {
			return static_cast<long long>(costBoth) * static_cast<long long>(max(need1, need2));
		}
		if (need1 == 0) {
			return static_cast<long long>(min(cost2, costBoth)) * static_cast<long long>(need2);
		}
		if (need2 == 0) {
			return static_cast<long long>(min(cost1, costBoth)) * static_cast<long long>(need1);
		}
		if (costBoth <= static_cast<long long>(cost1) + static_cast<long long>(cost2)) {
			long long common_count;
			long long remain_count;
			long long remain_cost;
			if (need1 < need2) {
				common_count = need1;
				remain_count = need2 - need1;
				remain_cost = min(cost2, costBoth);
			}
			else {
				common_count = need2;
				remain_count = need1 - need2;
				remain_cost = min(cost1, costBoth);;
			}
			return static_cast<long long>(costBoth) * common_count + remain_count * remain_cost;
		}
		else {
			return static_cast<long long>(cost1) * need1 + static_cast<long long>(cost2) * need2;
		}
	}
};
static void test(int cost1, int cost2, int costBoth, int need1, int need2) {
	cout << Solution().minimumCost(cost1, cost2, costBoth, need1, need2) << endl;
}
static void run() {
	test(1, 1, 2, 1, 1);
	test(3, 2, 1, 3, 2);
	test(5, 4, 15, 2, 3);
	test(5, 4, 15, 0, 0);
}

}

namespace problem3 {
class Solution {
public:
	static bool is_divisible(size_t len, long long k) {
		long long current = 1 % k;
		for (int i = 0; i < len - 1; i++) {
			current %= k;
			current *= 10;
			current++;
		}
		return (current % k) == 0;
	}
	static size_t get_len(long long k) {
		if (k == 0) { return 1; }
		size_t len = 0;
		long long current = k;
		while (current > 0) {
			current /= 10;
			len++;
		}
		return len;
	}
	static int tle(int k) {
		if (k % 2 == 0) { return -1; }
		if (k % 5 == 0) { return -1; }
		const auto klen = get_len(k);
		auto len = klen;
		while (!is_divisible(len, k)) {
			len++;
		}
		return static_cast<int>(len);
	}
	static vector<int> get_digits(long long k) {
		if (k == 0) { return { 0 }; }
		vector<int> digits;
		long long current = k;
		while (current > 0) {
			digits.emplace_back(current % 10);
			current /= 10;
		}
		return vector<int>(crbegin(digits), crend(digits));
	}

	optional<int> check_multiple(const vector<int>& digits, int mul) {
		long long carry = 0;
		vector<int> target;
		for (size_t i = 0; i < size(digits); i++) {
			long long cur = 1LL * digits[i] * mul + carry;
			if (cur % 10 != 1) {
				return nullopt;
			}
			carry = cur / 10;
		}
		int len = static_cast<int>(size(digits));
		while (carry > 0) {
			if (carry % 10 != 1) {
				return nullopt;
			}
			carry /= 10;
			len++;
		}
		return len;
	}


	int minAllOneMultiple(int k) {
		if (k % 2 == 0) { return -1; }
		if (k % 5 == 0) { return -1; }
		const auto digits = get_digits(k);
		long long cur_multiple;
		if (digits[0] == 1) {
			cur_multiple = 1;
		}
		else if(digits[0] == 3) {
			cur_multiple = 7;
		}
		else if (digits[0] == 7) {
			cur_multiple = 3;
		}
		else if (digits[0] == 9) {
			cur_multiple = 9;
		}
		else {
			return -1;
		}
		long long rem = 1;
		for (;;) {
			auto a = check_multiple(digits, rem);
			if (a.has_value()) {
				return a.value();
			}
			rem = (rem * 10 + 1) % k;
		}
	}
};
static void test(int k) {
	cout << Solution().minAllOneMultiple(k) << endl;
}
static void run() {
	test(3);
	test(7);
	test(2);
	test(34641);
	test(27673);
}
}

namespace problem4 {
class Solution {
public:
	static long long count_balanced(const vector<int>& digits) {
		//const auto len = size(digits);
		//vector<map<int, long long>> dp_eq(len);
		//vector<map<int, long long>> dp(len);
		//dp_eq[0][digits[0]] = 1LL;
		//for (int i = 1; i < digits[0]; i++) {
		//	dp[0][i] = 1LL;
		//}

		//for (int i = 1; i < len; i++) {
		//	int mul = ((i % 2 == 0) ? 1 : -1);
		//	for (auto&& [v, count] : dp_eq[i - 1]) {
		//		dp_eq[i][v + mul * digits[i]] = count;
		//		for (int j = 0; j < 10; j++) {
		//			dp[i][v + mul * j] += count;
		//		}
		//	}

		//	for (auto&& [v, count] : dp[i - 1]) {
		//		for (int j = 0; j < 10; j++) {
		//			dp[i][v + mul * j] += count;
		//		}
		//	}
		//}
		//return dp.back()[0];

	}
	static long long count_balanced(int len) {
		vector<map<int, long long>> dp(len);
		for (int i = 1; i < 10; i++) {
			dp[0][i] = 1LL;
		}
		for (int i = 1; i < len; i++) {
			int mul = ((i % 2 == 0) ? 1 : -1);
			for (auto&& [v, count] : dp[i - 1]) {
				for (int j = 0; j < 10; j++) {
					dp[i][v + mul * j] += count;
				}
			}
		}
		return dp.back()[0];
	}

	long long countBalanced(long long low, long long high) {

	}
};
static void test(long long low, long long high) {
	cout << Solution().countBalanced(low, high) << endl;
}
static void run() {
	test(1, 199);
	test(120, 129);
	test(1234, 1234);
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    //problem4::run();
    return 0;
}