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
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
		constexpr long long MODULO = 1e9 + 7;
		const auto h = size(grid);
		const auto w = size(grid[0]);

		vector<vector<vector<long long>>> dp(h, vector<vector<long long>>(w, vector<long long>(2)));
		dp[0][0][0] = 1LL;

		for (size_t i = 0; i < h; i++) {
			for (size_t j = 0; j < w; j++) {
				if (grid[i][j] == 0) {
					const auto cur = (dp[i][j][0] + dp[i][j][1]) % MODULO;
					if (j < w - 1) {
						dp[i][j + 1][0] += cur;
						dp[i][j + 1][0] %= MODULO;

					}
					if (i < h - 1) {
						dp[i + 1][j][1] += cur;
						dp[i + 1][j][1] %= MODULO;
					}
				}
				else {
					if (j < w - 1) {
						dp[i][j + 1][0] += dp[i][j][1];
						dp[i][j + 1][0] %= MODULO;

					}
					if (i < h - 1) {
						dp[i + 1][j][1] += dp[i][j][0];
						dp[i + 1][j][1] %= MODULO;
					}
				}
			}
		}
		return static_cast<int>((dp[h - 1][w - 1][0] + dp[h - 1][w - 1][1]) % MODULO);
    }
};
static void test(vector<vector<int>>&& grid) {
	cout << Solution().uniquePaths(grid) << endl;
}
static void run() {
	test(get_matrix_int("[[0,1,0],[0,0,1],[1,0,0]]"));
	test(get_matrix_int("[[0,0],[0,0]]"));
	test(get_matrix_int("[[0,1,1],[1,1,0]]"));
}

int main() {
	run();
	return 0;
}


//
//if (grid[i][j + 1] == 0) {
//}
//else {
//	if (i < h - 1) {
//		dp[i + 1][j + 1][1] += cur;
//		dp[i + 1][j + 1][1] %= MODULO;
//	}
//}

//if (grid[i + 1][j] == 0) {
//}
//else {
//	if (j < w - 1) {
//		dp[i + 1][j + 1] += cur;
//		dp[i + 1][j + 1] %= MODULO;
//	}
//}
