// weekly_contest_402.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>
#include <string>
#include <functional>

#include "./../utility//leetcode_testcase_helper.h"

using namespace std;


namespace problem1 {

class Solution {
public:

	int countCompleteDayPairs(vector<int>& hours) {
		int count = 0;

		for (int i = 0; i < hours.size() - 1; i++) {
			for (int j = i + 1; j < hours.size(); j++) {
				const long long h = static_cast<long long>(hours[i]) + static_cast<long long>(hours[j]);
				if ((h % 24) == 0) {
					count++;
				}
			}
		}

		return count;
	}
};

void test(vector<int>&& hours) {
	cout << Solution().countCompleteDayPairs(hours) << endl;
}
void run() {
	test(get_list_int("[12,12,30,24,24]"));
	test(get_list_int("[72,48,24,3]"));
}
}

namespace problem2 {
class Solution {
public:

	long long countCompleteDayPairs(vector<int>& hours) {

		long long count = 0;
		constexpr int MODULO = 24;
		unordered_map<int, long long> freq_map;

		for (int i = 0; i < hours.size(); i++) {
			const auto m = hours[i] % MODULO;
			const auto remain = (MODULO - m) % MODULO;

			const auto it = freq_map.find(remain);
			if (it != cend(freq_map)) {
				count += it->second;
			}
			freq_map[m]++;
		}

		return count;
	}
};

void test(vector<int>&& hours) {
	cout << Solution().countCompleteDayPairs(hours) << endl;
}
void run() {
	test(get_list_int("[12,12,30,24,24]"));
	test(get_list_int("[72,48,24,3]"));
	test(get_list_int("[13,11]"));
}
}

namespace problem3 {
class Solution {
public:

	using memo_t = vector<vector<long long>>;

	static long long rec(const vector<int>& power, int index, int last_casted, memo_t& memo) {
		if (index== power.size()) {
			return 0;
		}
		const auto step = min(3, power[index] - last_casted);
		if (memo[index][step] >=0) {
			return memo[index][step];
		}

		long long damage = 0;

		damage = rec(power, index + 1, last_casted, memo);

		if (last_casted + 2 < power[index] || last_casted == power[index]) {
			const auto v1 = rec(power, index + 1, power[index], memo);
			damage = max(damage, v1 + power[index]);
		}
		memo[index][step] = damage;
		return damage;
	}

	long long maximumTotalDamage(vector<int>& power) {
		sort(begin(power), end(power));
		memo_t memo(power.size(), vector<long long>(4, -1));
		const auto result = rec(power, 0, -10, memo);
		return result;
	}
};
void test(vector<int>&& power) {
	cout << Solution().maximumTotalDamage(power) << endl;
}

void run() {
	test(get_list_int("[5,9,2,10,2,7,10,9,3,8]"));
	test(get_list_int("[1,1,3,4]"));
	test(get_list_int("[7,1,6,6]"));
}

/*
		map<int, int> freq_map;
		for (auto&& p : power) {
			freq_map[p]++;
		}
		vector<pair<int, int>> powers(freq_map.size());
		int index = 0;
		for (auto&& [k, v] : freq_map) {
			powers[index++] = make_pair(k, v);
		}

		vector<vector<long long>> dp(powers.size(), vector<long long>(2, 0));
		dp[0][0] = 0;
		dp[0][1] = powers[0].first * powers[0].second;

		if (powers.size() < 2) {
			return dp[0][1];
		}
		dp[1][0] = dp[0][1];
		if (powers[0].first + 2 < powers[1].first) {
			dp[1][1] = powers[0].first * powers[0].second;
		}
		else {
			dp[1][1] = powers[1].first * powers[1].second;
		}


		for (int i = 2; i < powers.size(); i++) {
			const long long damage = powers[i].first * powers[i].second;
			dp[i][1] =
				for (int j = 0; j < 2; j++) {
					int index1 = i + j + 1;
					if (powers.size() <= index1) {
						break;
					}
					if (powers[i].first + 1 == powers[index1].first) {
						dp[index1][0] = dp[i][0];
					}
				}
			dp[i][1] = powers[i].first * powers[i].second;
			if (powers.size() == 1) {
				return powers[i].first * powers[i].second;
			}
			if (powers[i].first + 2 < powers[i + 1].first) {

			}

		}
		int before2 = it->first;
		it++;
		if (it == cend(freq_map)) {
			return dp[0][1];
		}
		dp[1][0] = dp[0][1];
		dp[1][1] = it->first * it->second;
		dp[1][2] = it->first * it->second;
		int before1 = it->first;

		it++;
		for (int i = 1; i < dp.size(); i++, it++) {
			dp[i][0] = 0;
			const long long cast_value = it->first * it->second;
			dp[i][1] = cast_value + max(dp[i - 1][0], dp[i - 1][2]);
			dp[i][2] = 0;
		}*/
}

namespace problem4 {
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
			for(;;) {
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

	using s_tree = segment_tree<int, function<int(int, int)>>;

	vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
		vector<int> peaks(nums.size());
		for (int i = 1; i < nums.size() - 1; i++) {
			peaks[i] = nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
		}

		s_tree st(peaks, [](const auto a, const auto b) {return a + b; }, 0);

		vector<int> ans;
		ans.reserve(queries.size());

		for (auto&& query : queries) {
			if (query[0] == 1) {
				if (query[1] == query[2]) {
					ans.emplace_back(0);
				}
				else {
					const auto result = st.query(query[1], query[2]) - peaks[query[1]];
					ans.emplace_back(result);
				}
			}
			else {
				const auto index = query[1];
				const auto value = query[2];
				nums[index] = value;
				for (int i = max(index - 1, 1); i < min(index - 1 + 3, static_cast<int>(nums.size()) - 1); i++) {
					peaks[i] = nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
					st.update(i, peaks[i]);
				}
			}
		}
		return ans;
	}
};

void test(vector<int>&& nums, vector<vector<int>>&& queries) {
	const auto ans = Solution().countOfPeaks(nums, queries);
	for (auto&& value : ans) {
		cout << value << ",";
	}
	cout << endl;
}
void run() {
	test(get_list_int("[9,7,5,8,9]"), get_matrix_int("[[2,0,2],[1,0,3],[1,3,3],[2,3,5]]"));

	test(get_list_int("[5,4,8,6]"), get_matrix_int("[[1,2,2],[1,1,2],[2,1,6]]"));
	test(get_list_int("[8,5,9,3,5]"), get_matrix_int("[[1,2,4],[1,0,1],[2,2,4]]"));
	test(get_list_int("[3,1,4,2,5]"), get_matrix_int("[[2,3,4],[1,0,4]]"));
	test(get_list_int("[4,1,4,2,1,5]"), get_matrix_int("[[2,2,4],[1,0,2],[1,0,4]]"));
}
}


int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}