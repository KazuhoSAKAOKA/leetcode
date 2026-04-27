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

namespace problem1 {
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
		template <typename Container>
		seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	};
	template <typename T = long long>
	struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
		seqment_tree_range_minimum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
		template <typename Container>
		seqment_tree_range_minimum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
	};
	int firstStableIndex(vector<int>& nums, int k) {
		const auto n = size(nums);
		seqment_tree_range_maximum_query<int> st_max(n);
		seqment_tree_range_minimum_query<int> st_min(n);

		for (size_t i = 0; i < n; i++) {
			st_max.update(i, nums[i]);
			st_min.update(i, nums[i]);
		}

		size_t ans = INT_MAX;
		for (size_t i = 0; i < n; i++) {
			const auto max_val = st_max.query(0, i + 1);
			const auto min_val = st_min.query(i, n);
			const auto v = max_val - min_val;
			if (v <= k) {
				ans = i;
				break;
			}
		}
		if (ans == INT_MAX) { return -1; }
		return static_cast<int>(ans);
	}
};
static void test(vector<int>&& nums, int k) {
	cout << Solution().firstStableIndex(nums, k) << endl;
}
static void run() {
	test(get_list_int("[5,0,1,4]"), 3);
	test(get_list_int("[3,2,1]"), 1);
	test(get_list_int("[0]"), 0);
}
}



namespace problem2 {
	// p1と同じ
}

namespace problem3 {
	using point_t = pair<long long, long long>;
	static inline point_t operator +(const point_t& p1, const point_t& p2) {
		return point_t{ p1.first + p2.first, p1.second + p2.second };
	}
class Solution {
public:


	vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
		const point_t UP_DIR{ -1,0 };
		const point_t DOWN_DIR{ 1,0 };
		const point_t LEFT_DIR{ 0,-1 };
		const point_t RIGHT_DIR{ 0, 1 };
		const vector<point_t> dirs{ UP_DIR,DOWN_DIR, LEFT_DIR, RIGHT_DIR };

		vector<vector<int>> grid(n, vector<int>(m));

		set<point_t> befores;
		for (auto&& source : sources) {
			const auto y = source[0];
			const auto x = source[1];
			const auto c = source[2];
			grid[y][x] = c;
			befores.insert(point_t{ y,x });
		}

		while (!befores.empty()) {
			set<point_t> current;

			for (auto&& p : befores) {
				const auto color = grid[p.first][p.second];
				for (auto&& dir : dirs) {
					const auto np = p + dir;
					if (0 <= np.first && np.first < n && 0 <= np.second && np.second < m) {
						if (grid[np.first][np.second] == 0) {
							grid[np.first][np.second] = color;
							current.insert(np);
						}
						else {
							auto it = current.find(np);
							if (it != end(current)) {
								grid[np.first][np.second] = max(grid[np.first][np.second], color);
							}
						}
					}
				}
			}

			swap(befores, current);
		}

		return grid;
	}
};
static void test(int n, int m, vector<vector<int>>&& sources) {
	output_matrix(Solution().colorGrid(n, m, sources));
}
static void run() {
	test(3, 3, get_matrix_int("[[0,0,1],[2,2,2]]"));
	test(3, 3, get_matrix_int("[[0,1,3],[1,1,5]]"));
	test(2, 2, get_matrix_int("[[1,1,5]]"));
}
}

namespace problem4 {
class Solution {
public:
	static vector<int> get_digits_16(long long value) {
		if (value == 0) {
			return{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
		}
		vector<int> digits;
		while (value > 0) {
			digits.push_back(value % 10);
			value /= 10;
		}
		if (size(digits) < 16) {
			digits.insert(end(digits), 16 - size(digits), 0);
		}
		return vector<int>(crbegin(digits), crend(digits));
	}

	static long long powr(long long base, long long v) {
		if (base % 2 != 0) {
			return powr(base * base, v / 2) * base;
		}
		else {
			return powr(base * base, v / 2);
		}
	}

	static long long digit_dp(long long value, const vector<size_t>& indexes) {
		
		const vector<int> digits = get_digits_16(value);

		vector<vector<vector<long long>>> dp(7, vector<vector<long long>>(10, vector<long long>(2)));
		dp[0][0][1] = 1;

		for (size_t i = 1; i < size(indexes); i++) {
			const auto digi_len = indexes[i] - indexes[i - 1];
			const long long base = powr(10, digi_len);
			if (digits[indexes[i - 1]] <= digits[indexes[i]]) {
				dp[i][digits[indexes[i]]][1] = dp[i - 1][digits[indexes[i - 1]]][1];
			}
			for (int s = 0; s < 10; s++) {
				for (int d = s; d < 10; d++) {
					dp[i][d][0] += dp[i - 1][s][0] * base;
				}
			}
		}
		return 0;
	}


	static long long digit_dp1(long long value) {
		vector<vector<vector<long long>>> dp(16, vector<vector<long long>>(10, vector<long long>(2)));
		const vector<int> digits = get_digits_16(value);

		dp[0][0][1] = 1;
		dp[0][0][0] = 0;
		for (size_t i = 1; i < 16; i++) {
			dp[i][digits[i]][1] = dp[i - 1][digits[i - 1]][1];
			for (int s = 0; s < 10; s++) {
				for (int d = 0; d < digits[i]; d++) {
					dp[i][d][0] += dp[i - 1][s][0] + dp[i - 1][s][1];
				}
				for (int d = digits[i]; d < 10; d++) {
					dp[i][d][0] += dp[i - 1][s][0];
				}
			}
		}
		long long count = 0;
		for (size_t d = 0; d < 10; d++) {
			count += dp.back()[d][0] + dp.back()[d][1];
		}
		return count;
	}

	long long countGoodIntegersOnPath(long long l, long long r, string directions) {
		vector<size_t> indexes;
		indexes.reserve(7);
		indexes.push_back(0);
		size_t index = 0;
		for (auto&& c: directions) {
			if (c == 'D') {
				index += 4;
			}
			else {
				index++;
			}
			indexes.push_back(index);
		}

		return 0;
	}
};
static void test(long long l, long long r, string directions) {
	cout << Solution().countGoodIntegersOnPath(l, r, directions) << endl;
}
static void run() {

	cout << Solution().digit_dp1(123);

	test(8, 10, "DDDRRR");
	test(123456789, 123456790, "DDRRDR");
	test(1288561398769758, 1288561398769758, "RRRDDD");
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
