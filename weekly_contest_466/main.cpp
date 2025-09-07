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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int minOperations(vector<int>& nums) {
        const auto v1 = nums[0];
        return all_of(cbegin(nums), cend(nums), [&](int v) { return v == v1; }) ? 0 : 1;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().minOperations(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2]"));
    test(get_list_int("[5,5,5]"));
}
}
namespace problem2 {
class Solution {
public:
    int minOperations(string s) {
        vector<bool> exists(26);
        for (auto&& c : s) {
            exists[c - 'a'] = true;
        }
        int count = 0;
        bool bring = false;
        for (int i = 1; i < 26; i++) {
            if (exists[i] || bring) {
                count++;
                bring = true;
            }
        }
        return count;
    }
};
static void test(string&& s) {
    cout << Solution().minOperations(s) << endl;
}
static void run() {
    test("b");
    test("yz");
    test("a");
}
}
namespace problem3 {


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
	struct seqment_tree_range_maximum_query : public segment_tree<T, std::function<T(T, T)>> {
		seqment_tree_range_maximum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
		template <typename Container>
		seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	};

	static long long tel(const vector<int>& nums) {
		const auto n = size(nums);
		seqment_tree_range_maximum_query<int> segtree(n);
		segtree.build(cbegin(nums), cend(nums));
		long long count = 0;

		for (int i = 0; i < n; i++) {
			for (int j = i + 2; j < n; j++) {
				if (segtree.query(i + 1, j) < min(nums[i], nums[j])) {
					count++;
				}
			}
		}
		return count;
	}


	template <typename T = long long>
	T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
		while (abs(ng - ok) > 1) {
			const auto mid = (ok + ng) / 2;
			if (check(mid)) {
				ok = mid;
			}
			else {
				ng = mid;
			}
		}
		return ok;
	}
    long long bowlSubarrays(vector<int>& nums) {
		const auto n = size(nums);
		if (n < 3) { return 0LL; }
		long long count = 0;
		vector<int> mono_stack;
		if (nums[0] < nums[1]) {
			mono_stack.emplace_back(1);
		}
		else {
			mono_stack.emplace_back(0);
			mono_stack.emplace_back(1);
		}


		for (int i = 2; i < n; i++) {
			const auto limit_index = binary_search_meguru<int>(0, static_cast<int>(size(mono_stack)),
				[&](int index)->bool {
					return nums[mono_stack[index]] > nums[i];
				});
			long long cur_count;
			if (nums[mono_stack[limit_index]] > nums[i]) {
				cur_count = size(mono_stack) - limit_index;
			}
			else {
				cur_count = size(mono_stack);
			}
			if (cur_count > 0 && !mono_stack.empty() && mono_stack.back() == i - 1) {
				cur_count--;
			}
			count += cur_count;
			while (!mono_stack.empty() && nums[mono_stack.back()] < nums[i]) {
				mono_stack.pop_back();
			}
			mono_stack.emplace_back(i);
		}
		return count;
	}
};
static void test(vector<int>&& nums) {
    cout << Solution().bowlSubarrays(nums) << endl;
}

static void run() {
	test(get_list_int("[1000000000,999999999,999999998]"));
	test(get_list_int("[2,5,3,1,4]"));
    test(get_list_int("[5,1,2,3,4]"));
}
}
namespace problem4 {
class Solution {
public:

	static int get_msb(long long num) {
		int position = -1;
		while (num > 0) {
			num >>= 1;
			position++;
		}
		return position;
	}

	int get_full(int bitwidth) {
		const auto c = bitwidth / 2;
		int count = 1 * pow(2, c - 1);
		if (bitwidth % 2 != 0) { return count * 2; }
		return count;
	}

	int digit_dp(int bitwidth, long long val) {
		vector<int> palindrome_limit_digits(bitwidth);
		vector<int> val_digits(bitwidth);
		for (int i = 0; i < bitwidth; i++) {
			const auto lbit = 1LL << (bitwidth - i - 1);
			if ((val & lbit) != 0) {
				val_digits[i] = 1;
			}
		}
		for (int i = 0; i < bitwidth / 2; i++) {
			palindrome_limit_digits[i] = palindrome_limit_digits[bitwidth - i - 1] = val_digits[i];
		}
		if (bitwidth % 2 != 0) {
			palindrome_limit_digits[bitwidth % 2] = val_digits[bitwidth % 2];
		}

		vector<vector<int>> dp(bitwidth, vector<int>(2));
		dp[0][1] = 1;

		for (int i = 1; i < bitwidth / 2; i++) {
			dp[i][1] = dp[i - 1][1];
			dp[i][0] = dp[i - 1][0] * 2;
			if (val_digits[i] > 0) {
				dp[i][0] += dp[i - 1][1];
			}
		}
		int mid = bitwidth / 2;
		if (bitwidth % 2 != 0) {
			dp[mid][1] = dp[mid - 1][1];
			dp[mid][0] = dp[mid - 1][0] * 2;
			if (val_digits[mid] > 0) {
				dp[mid][0] += dp[mid - 1][1];
			}
			mid++;
		}

		for (int i = mid; i< bitwidth; i++){
			if (palindrome_limit_digits[i] == val_digits[i]) {
				dp[i][1] = dp[i - 1][1];
			}
			dp[i][0] = dp[i - 1][0];
			if (palindrome_limit_digits[i] < val_digits[i]) {
				dp[i][0] += dp[i - 1][1];
			}
		}

		return (dp.back()[0] + dp.back()[1]);
	}


	int countBinaryPalindromes(long long n) {
		if (n == 0) { return 1; }
		if (n == 1) { return 2; }
		const auto bitlen = get_msb(n) + 1;
		int count = 2;
		for (int i = 2; i < bitlen; i++) {
			count += get_full(i);
		}
		count += digit_dp(bitlen, n);
		return count;
	}
};
static void test(long long n) {
	cout << Solution().countBinaryPalindromes(n) << endl;
}
static void run() {
	test(4);
	test(2);
	test(9);
	test(10);
	test(0);
}
}

int main() {
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}