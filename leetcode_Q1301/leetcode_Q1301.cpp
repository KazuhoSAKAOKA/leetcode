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

constexpr long long MODULO = 1e9 + 7;
class Solution {
public:


    static pair<long long, long long> dfs(const vector<string>& board, int i, int j, vector<vector<pair<long long, long long>>>& memo) {
        if (i == 0 && j == 0) {
            return { 0,1 };
        }

        if (memo[i][j].second >= 0) {
            return memo[i][j];
        }

        long long cur_score = board[i][j] != 'S' ? static_cast<long long>(board[i][j] - '0') : 0LL;
        long long max_score = LLONG_MIN;
        long long total_count = 0LL;
        if (i > 0 && board[i-1][j] != 'X') {
            auto [score, count] = dfs(board, i-1, j, memo);
            if (max_score < score + cur_score) {
                max_score = score + cur_score;
                total_count = count;
            }
            else if (max_score == score + cur_score) {
                total_count += count;
                total_count %= MODULO;
            }
        }
        if (j > 0 && board[i][j-1] != 'X') {
            auto [score, count] = dfs(board, i, j-1, memo);
            if (max_score < score + cur_score) {
                max_score = score + cur_score;
                total_count = count;
            }
            else if (max_score == score + cur_score) {
                total_count += count;
                total_count %= MODULO;
            }
        }
        if (i > 0 && j > 0 && board[i - 1][j - 1] != 'X') {
            auto [score, count] = dfs(board, i - 1, j - 1, memo);
            if (max_score < score + cur_score) {
                max_score = score + cur_score;
                total_count = count;
            }
            else if (max_score == score + cur_score) {
                total_count += count;
                total_count %= MODULO;
            }
        }
        memo[i][j] = { max_score, total_count };
        return { max_score, total_count };
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        const auto n = size(board);
        const auto m = size(board[0]);
        vector<vector<pair<long long, long long>>> memo(n, vector<pair<long long, long long>>(m, make_pair(0, -1)));

        const auto p = dfs(board, n - 1, m - 1, memo);
        if (p.first < 0) { return { 0,0 }; }
        return { static_cast<int>(p.first), static_cast<int>(p.second) };
    }
};

static void test(vector<string>&& board) {
    output(Solution().pathsWithMaxScore(board));
}

int main() {
    test(get_list_str(R"(["E23","2X2","12S"])"));
    test(get_list_str(R"(["E12","1X1","21S"])"));
    test(get_list_str(R"(["E11","XXX","11S"])"));
    return 0;
}
