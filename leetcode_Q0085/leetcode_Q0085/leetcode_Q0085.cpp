// leetcode_Q0085.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    
    int maximalRectangle(vector<vector<char>>& matrix) {
        using P = pair<int, int>;
        vector<vector<P>> dp(matrix.size(), vector<P>(matrix.front().size(), P(-1, -1)));

        auto calc = [](const P& ps, int i, int j){
                return (i - ps.first + 1) * (j - ps.second + 1);
            };
        auto valid = [](const P& p){
                return p.first >= 0 && p.second >= 0;
            };

        auto get_col_continue = [&](int y, int start_point, int end_point_include) {
                int index = end_point_include - 1;
                for (; index >= start_point; index--) {
                    if (matrix[y][index] == '0') {
                        return index + 1;
                    }
                }
                return start_point;
            };

        auto get_row_continue = [&](int x, int start_point, int end_point_include) {
                int index = end_point_include - 1;
                for (; index >= start_point; index--) {
                if (matrix[index][x] == '0') {
                        return index + 1;
                    }
                }
                return start_point;
            };


        int max_size = 0;

        if (matrix[0][0] == '1') {
            max_size = 1;
            dp[0][0] = P(0, 0);
        }

        for (int j = 1; j < matrix.front().size(); j++) {
            if (matrix[0][j] == '1') {
                dp[0][j] = valid(dp[0][j - 1]) ? dp[0][j - 1] : P(0, j);
                max_size = max(max_size, calc(dp[0][j], 0, j));
            }
        }
        for (int i = 1; i < matrix.size(); i++) {
            if (matrix[i][0] == '1') {
                dp[i][0] = valid(dp[i - 1][0]) ? dp[i - 1][0] : P(i, 0);
                max_size = max(max_size, calc(dp[i][0], i, 0));
            }
        }

        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix.front().size(); j++) {
                if (matrix[i][j] == '1') {
                    if (valid(dp[i][j - 1]) && valid(dp[i - 1][j])) {
                        if (dp[i][j - 1] == dp[i - 1][j]) {
                            dp[i][j] = dp[i - 1][j];
                        }
                        else {
                            const auto colindex = get_col_continue(i, dp[i][j - 1].second, j);
                            const auto box_1 = P(dp[i][j - 1].first, colindex);

                            const auto rowindex = get_row_continue(j, dp[i - 1][j].first, i);
                            const auto box_2 = P(rowindex, dp[i - 1][j].second);

                            if (calc(box_1, i, j) < calc(box_2, i, j)) {
                                dp[i][j] = box_2;
                            }
                            else {
                                dp[i][j] = box_1;
                            }
                        }
                    }
                    else {
                        if (valid(dp[i][j - 1])) {
                            dp[i][j] = P(i, dp[i][j - 1].second);
                        }
                        else if (valid(dp[i - 1][j])) {
                            dp[i][j] = P(dp[i - 1][j].first, j);
                        }
                        else {
                            dp[i][j] = P(i, j);
                        }
                    }
                    max_size = max(max_size, calc(dp[i][j], i, j));
                }
            }
        }

        return max_size;
       
    }
    /*
    using rectangle = pair<int, int>;
    using memo_t = unordered_map<rectangle, rectangle>;
    static rectangle get_size(const vector<vector<char>>& matrix, int i, int j, memo_t& memo) {
        if (matrix.size() == i) {
            return 0;
        }
        if (matrix.front().size() == j) {
            return 0;
        }
        const auto key = rectangle(i, j);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int value = 0;
        if (matrix[i][j] == '1') {
            value 

        }
        memo[key] = value;
        return value;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int max_size = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.front().size(); j++) {
                if (matrix[i][j] == '1') {
                    max_size = max(max_size, 1);
                    for (int k = i + 1; k < matrix.size(); k++) {
                        if (matrix[i][j] != '1') { break; }
                        for (int l = j + 1; j < matrix.front().size(); l++) {
                            if (matrix[i][j] != '1') { break; }
                        }
                    }
                }
            }
        }
        
    }    */

};

void test(vector<vector<char>>&& matrix) {
    cout << Solution().maximalRectangle(matrix) << endl;
}

int main()
{
    test({ {'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'} });
    test({ {'0'} });
    test({ {'1'} });
}