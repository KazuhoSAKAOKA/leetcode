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
#include "./../utility/TreeNodeUtil.h"
using namespace std;

namespace problem1 {
class Solution {
public:
	int largestInteger(int n, int s) {
		int cur_sum = s;
		string v;
		for (int i = 0; i < n; i++) {
			if (cur_sum == 0) {
				v.push_back('0');
			}
			else {
				auto d = min(9, cur_sum);
				v.push_back('0' + d);
				cur_sum -= d;
			}
		}
		if (cur_sum > 0) { return -1; }
		return stoi(v);
	}
};
static void test(int n, int s) {
	cout << Solution().largestInteger(n, s) << endl;
}
static void run() {
	test(2, 9);
	test(2, 19);
	test(5, 0);
}
}

namespace problem2 {
class Solution {
public:
	vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2) {
		vector<vector<int>> ans;
		const auto n = size(series1);
		const auto m = size(series2);
		size_t i = 0;
		size_t j = 0;
		while (i < n && j < m) {
			int time;
			int cur_1 = series1[i][1];
			int cur_2 = series2[j][1];

			if (series1[i][0] == series2[j][0]) {
				time = series1[i][0];
				i++;
				j++;
			}
			else if (series1[i][0] < series2[j][0]) {
				time = series1[i][0];
				i++;
			}
			else {
				time = series2[j][0];
				j++;
			}

			ans.push_back({ time, cur_1 + cur_2 });
		}
		if (i < n || j < m) {
			if (i < n) {
				for (; i < n; i++) {
					ans.push_back(series1[i]);
				}
			}
			else {
				for (; j < m; j++) {
					ans.push_back(series2[j]);
				}
			}
		}
		return ans;
	}
};
static void test(vector<vector<int>>&& series1, vector<vector<int>>&&series2) {
	output_matrix(Solution().aggregateTimeSeries(series1, series2));
}
static void run() {
	test(get_matrix_int("[[1,3],[4,1]]"), get_matrix_int("[[2,2],[5,2]]"));
	test(get_matrix_int("[[1,5],[3,1]]"), get_matrix_int("[[2,2]]"));
	test(get_matrix_int("[[1,5]]"), get_matrix_int("[[1000000000,2]]"));
}
}

namespace problem3 {
class Solution {
public:

	static int tle(int n, int k) {
		const long long MODULO = 1e9 + 7;
		const long long remain = n - k;

		vector<vector<vector<long long>>> dp(k, vector<vector<long long>>(remain + 1, vector<long long>(2)));

		for (int j = 0; j <= remain; j++) {
			dp[0][j][0] = j % 2 == 0 ? 1LL : 0LL;
			dp[0][j][1] = j % 2 == 0 ? 0LL : 1LL;
		}

		for (int i = 1; i < k; i++) {
			long long total0 = 0LL;
			long long total1 = 0LL;
			for (int j = 0; j <= remain; j++) {

				total1 += dp[i - 1][j][1];
				total1 %= MODULO;
				dp[i][j][1] = total1;

				if (j % 2 == 0) {
					total0 += dp[i - 1][j][0];
					total0 %= MODULO;
					dp[i][j][0] = total0;
				}
				else {
					dp[i][j][1] += total0;
					dp[i][j][1] %= MODULO;
				}
			}
		}

		return static_cast<int>(dp.back()[remain][1]);
	}


	int countValidSequences(int N, int K) {
		const long long MODULO = 1e9 + 7;
		const long long remain = N - K;
		if (remain == 0) { return 0; }
		if (remain == 1) { return K; }
		const auto max_comb = remain + K - 1;
		vector<long long> fac(max_comb + 1);
		vector<long long> finv(max_comb + 1);
		vector<long long> inv(max_comb + 1);
		fac[0] = fac[1] = 1;
		finv[0] = finv[1] = 1;
		inv[1] = 1;
		for (long long i = 2; i < max_comb + 1; i++) {
			fac[i] = fac[i - 1] * i % MODULO;
			inv[i] = MODULO - inv[MODULO % i] * (MODULO / i) % MODULO;
			finv[i] = finv[i - 1] * inv[i] % MODULO;
		}
		auto get_comb = [&](int n, int k)-> long long {
			if (n < k) return 0;
			if (n < 0 || k < 0) return 0;
			return fac[n] * (finv[k] * finv[n - k] % MODULO) % MODULO;
			};

		const long long total_comb = get_comb(remain + K - 1, K - 1);
		if (remain % 2 != 0) {
			return total_comb;
		}
		const auto half_remain = remain / 2;
		const long long all_odds_comb = get_comb(half_remain + K - 1, K - 1);
		const long long ans = (total_comb + MODULO - all_odds_comb) % MODULO;
		return ans;
	}
};
static void test(int n, int k) {
	cout << Solution().countValidSequences(n, k) << endl;
}
static void run() {
	test(5, 3);
	test(3, 2);
	test(5, 5);
}
}

namespace problem4 {
class Solution {
public:
	long long minCost(int m, int n, vector<vector<int>>& penalty) {
		auto djikstra = [&]() {
			const long long half = m * n;
			const long long total = half * 2;
			const vector<vector<tuple<int, int, bool>>> directionss{
				{
					{ {0, -1, false},{-1, 0, false},{0, 1, true},{1, 0, true}, },
				},
				{
					{ {0, 1, false},{1, 0, false},{0, -1, true},{-1, 0, true}, },
				}, };

			vector<long long> costs(total, numeric_limits<long long>::max());
			struct point {
				long long cost;
				int y;
				int x;
				int odd;
				bool operator > (const point& other) const {
					return cost > other.cost;
				}
			};
			std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
			p_queue.push(point{ 1, 0,0,1 });
			costs[0] = 1LL;
			while (!p_queue.empty()) {
				const auto [current_cost, currenty, currentx, cur_odd] = p_queue.top();
				p_queue.pop();
				const auto index = (cur_odd ? 0LL : half) + currenty * n + currentx;
				if (costs[index] < current_cost) { continue; }

				for (auto&& [dy, dx, is_penarty] : directionss[cur_odd]) {
					const auto ny = dy + currenty;
					const auto nx = dx + currentx;
					if (0 <= ny && ny < m && 0 <= nx && nx < n) {
						const auto move_cost = (ny + 1) * (nx + 1) + (is_penarty ? penalty[currenty][currentx] : 0);
						const auto next_index = (cur_odd ? half : 0LL) + ny * n + nx;
						if (costs[next_index] > move_cost + current_cost) {
							costs[next_index] = move_cost + current_cost;
							p_queue.push(point{ costs[next_index] , ny, nx, (cur_odd + 1) % 2 });
						}
					}
				}
				const auto index2 = (cur_odd ? half : 0LL) + currenty * n + currentx;
				if (costs[index2] > penalty[currenty][currentx] + current_cost) {
					costs[index2] = penalty[currenty][currentx] + current_cost;
					p_queue.push(point{ costs[index2] , currenty, currentx, (cur_odd + 1) % 2 });
				}
			}
			return min(costs[half - 1], costs[total - 1]);
			};

		return djikstra();
	}
};
static void test(int m, int n, vector<vector<int>>&& penalty) {
	cout << Solution().minCost(m, n, penalty) << endl;
}
static void run() {
	//test(2, 2, get_matrix_int("[[5,3],[1,4]]"));
	test(2, 2, get_matrix_int("[[0,7],[3,2]]"));
	test(2, 3, get_matrix_int("[[8,0,9],[7,4,1]]"));
}
}

int main() {
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}
