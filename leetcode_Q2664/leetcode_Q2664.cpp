// leetcode_Q2664.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

static const vector<pair<int, int>> directions{
    {0 + 2,0 + 1},
    {0 + 1,0 + 2},
    {0 - 1,0 + 2},
    {0 - 2,0 + 1},
    {0 - 2,0 - 1},
    {0 - 1,0 - 2},
    {0 + 1,0 - 2},
    {0 + 2,0 - 1},
};

class Solution {
public:

    static bool dfs(vector<vector<int>>& board, int current_row, int current_col, int count) {
        if (count == size(board) * size(board.front())) {
            return true;
        }
        
        for (auto&& [dy, dx] : directions) {
            const auto row = current_row + dy;
            const auto col = current_col + dx;
            if (0 <= row && row < size(board) && 0 <= col && col < size(board.front())) {
                if (board[row][col] < 0) {
                    board[row][col] = count;
                    if (dfs(board, row, col, count + 1)) {
                        return true;
                    }
                    board[row][col] = -1;
                }
            }
        }
        return false;
    }


    vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
        vector<vector<int>> board(m, vector<int>(n, -1));
        board[r][c] = 0;
        dfs(board, r, c, 1);
        return board;
    }
};

void test(int m, int n, int r, int c) {
    const auto ans = Solution().tourOfKnight(m, n, r, c);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
}

int main()
{
    test(1, 1, 0, 0);
    test(3, 4, 0, 0);
    return 0;
}