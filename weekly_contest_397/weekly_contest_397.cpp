// weekly_contest_397.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <queue>
#include <stack>
#include <functional>
#include <cmath>
using namespace std;

namespace problem1 {
class Solution {
public:
	int findPermutationDifference(string s, string t) {
		unordered_map<char, int> t_map;
		for (int i = 0; i < s.size(); i++) {
			t_map[t[i]] = i;
		}
		int total = 0;
		for (int i = 0; i < s.size(); i++) {
			const int l = abs(i - t_map[s[i]]);
			total += l;
		}
		return total;
	}
};

void test(string&& s, string&& t) {
	cout << Solution().findPermutationDifference(s, t) << endl;
}
void run() {
	test("abc", "bac");
	test("abcde", "edbac");
}
}

namespace problem2 {
class Solution {
public:
	int maximumEnergy(vector<int>& energy, int k) {
		long long max_energy = LLONG_MIN;


		for (int i = 0; i < k; i++) {
			if (i < energy.size()) {
				long long current_total = 0;
				for (int j = i; j < energy.size(); j += k) {
					current_total += static_cast<long long>(energy[j]);
				}
				max_energy = max(max_energy, current_total);
				if (k < energy.size()) {
					for (int j = i; j < energy.size() - k; j += k) {
						current_total -= static_cast<long long>(energy[j]);
						max_energy = max(max_energy, current_total);
					}
				}
			}
		}

		return static_cast<int>(max_energy);
	}
};

void test(vector<int>&& energy, int k) {
	cout << Solution().maximumEnergy(energy, k) << endl;
}
void run() {
	test({ -10 }, 3);
	test({ -10, -20, }, 2);
	test({ 5,2,-10,-5,1 }, 3);
	test({ -2,-3,-1 }, 2);
}
}

namespace problem3 {

class Solution {
public:

	int maxScore1(vector<vector<int>>& grid) {

		const size_t H = grid.size();
		const size_t W = grid.front().size();

		vector<vector<long long>> dp(H, vector<long long>(W, LLONG_MIN));
	
		vector<vector<long long>> row_max_values(W, vector<long long>(2, LLONG_MIN));

		long long max_score = LLONG_MIN;
		{
			int col_min = grid[0][0];
			for (int j = 1; j < W; j++) {
				dp[0][j] = grid[0][j] - col_min;
				max_score = max(max_score, dp[0][j]);
				col_min = min(col_min, grid[0][j]);

				row_max_values[j][0] = max(0LL, dp[0][j]) - grid[0][j];
				row_max_values[j][1] = 0;
			}
			int row_min = grid[0][0];
			for (int i = 1; i < H; i++) {
				dp[i][0] = grid[i][0] - row_min;
				max_score = max(max_score, dp[i][0]);
				col_min = min(row_min, grid[i][0]);
			}
		}


		for (int i = 1; i < H; i++) {
			vector<long long> col_max_value{ max(0LL,dp[i][0]) - grid[i][0]  ,0LL };
			for (int j = 1; j < W; j++) {
				const auto col_max = col_max_value[0];
				const auto row_max = row_max_values[j][0];

				if (col_max < row_max) {
					const int row_index = row_max_values[j][1];
					dp[i][j] = max(0LL, dp[row_index][j]) + grid[i][j] - grid[row_index][j];
				}
				else {
					const int col_index = col_max_value[1];
					dp[i][j] = max(0LL, dp[i][col_index]) + grid[i][j] - grid[i][col_index];
				}
				if (col_max < dp[i][j] - grid[i][j]) {
					col_max_value[0] = dp[i][j] - grid[i][j];
					col_max_value[1] = j;
				}
				if (row_max < dp[i][j] - grid[i][j]) {
					row_max_values[j][0] = dp[i][j] - grid[i][j];
					row_max_values[j][1] = i;
				}

				max_score = max(max_score, dp[i][j]);
			}
		}
		return static_cast<int>(max_score);
	}


	template <typename T, typename F>
	struct SegmentTree2D {
	private:
		int id(int h, int w) const { return h * 2 * W + w; }

	public:
		int H, W;
		vector<T> seg;
		const F f;
		const T I;

		SegmentTree2D(int h, int w, F _f, const T& i) : f(_f), I(i) { init(h, w); }

		void init(int h, int w) {
			H = W = 1;
			while (H < h) H <<= 1;
			while (W < w) W <<= 1;
			seg.assign(4 * H * W, I);
		}

		// build にのみ呼ぶ
		void set(int h, int w, const T& x) { seg[id(h + H, w + W)] = x; }

		void build() {
			// w in [W, 2W)
			for (int w = W; w < 2 * W; w++) {
				for (int h = H - 1; h; h--) {
					seg[id(h, w)] = f(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]);
				}
			}
			// h in [0, 2H)
			for (int h = 0; h < 2 * H; h++) {
				for (int w = W - 1; w; w--) {
					seg[id(h, w)] = f(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]);
				}
			}
		}

		T get(int h, int w) const { return seg[id(h + H, w + W)]; }
		T operator()(int h, int w) const { return seg[id(h + H, w + W)]; }

		void update(int h, int w, const T& x) {
			h += H, w += W;
			seg[id(h, w)] = x;
			for (int i = h >> 1; i; i >>= 1) {
				seg[id(i, w)] = f(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]);
			}
			for (; h; h >>= 1) {
				for (int j = w >> 1; j; j >>= 1) {
					seg[id(h, j)] = f(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]);
				}
			}
		}

		T _inner_query(int h, int w1, int w2) {
			T res = I;
			for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
				if (w1 & 1) res = f(res, seg[id(h, w1)]), w1++;
				if (w2 & 1) --w2, res = f(res, seg[id(h, w2)]);
			}
			return res;
		}

		// [ (h1,w1), (h2,w2) ) 半開
		T query(int h1, int w1, int h2, int w2) {
			if (h1 >= h2 || w1 >= w2) return I;
			T res = I;
			h1 += H, h2 += H, w1 += W, w2 += W;
			for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
				if (h1 & 1) res = f(res, _inner_query(h1, w1, w2)), h1++;
				if (h2 & 1) --h2, res = f(res, _inner_query(h2, w1, w2));
			}
			return res;
		}
	};

	static int get_max(int a, int b) { return max(a, b); }

	using st = SegmentTree2D<int, std::function<int(int, int)>>;

	int maxScore(vector<vector<int>>& grid) {
		const auto H = grid.size();
		const auto W = grid.front().size();
		st st1(grid.size(), grid.front().size(), get_max, INT_MIN);

		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid.front().size(); j++) {
				st1.set(i, j, grid[i][j]);
			}
		}
		st1.build();

		int max_score = INT_MIN;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid.front().size(); j++) {

				auto max_value = INT_MIN;
				if (i < grid.size() - 1) {
					max_value = max(max_value, st1.query(i + 1, j, H, j + 1));
				}
				if (j < grid.front().size() - 1) {
					max_value = max(max_value, st1.query(i, j + 1, H, W));
				}
				if (max_value != INT_MIN) {
					max_score = max(max_score, max_value - grid[i][j]);
				}
			}
		}

		return max_score;
	}

};

void test(vector<vector<int>>&& grid) {
	cout << Solution().maxScore(grid) << endl;
}

void run() {
	test({ {2,8},{1,4,},{4,7},{3,1},{9,5}, });
	test({ {4,8,7,},{6,3,10},{5,3,10,},{8,8,3,}, });
	test({ {9,5,7,3,},{8,9,6,1,},{6,7,14,3,},{2,5,3,1,}, });
	test({ {4,3,2,},{3,2,1,}, });
}
}

namespace problem4 {


void run() {

}
}


int main()
{
	//problem1::run();
	//problem2::run();
	problem3::run();
	//problem4::run();
}