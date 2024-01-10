// leetcode_Q0130.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    using POS = pair<int, int>;
    static POS add_pos(const POS& v1, const POS& v2) {
        return POS(v1.first + v2.first, v1.second + v2.second);
    }

    static bool dfs(const vector<vector<char>>& board, const POS& pos, set<POS>& progress, vector<vector<bool>>& checked) {
        static vector<POS> directions = { {-1,0},{1,0}, {0, -1}, {0, 1}, };

        progress.insert(pos);
        checked[pos.first][pos.second] = true;
        bool alive = false;
        if (pos.first == 0 || board.size() - 1 == pos.first || pos.second == 0 || board.front().size() - 1 == pos.second) {
            alive = true;
        }

        for (auto& dir : directions) {
            const auto next = add_pos(pos, dir);
            if (next.first < 0 || board.size() <= next.first || next.second < 0 || board.front().size() <= next.second) { continue; }
            if (board[next.first][next.second] == 'X') { continue; }
            if (checked[next.first][next.second]) { continue; }
            if (progress.find(next) != cend(progress)) { continue; }
            alive |= dfs(board, next, progress, checked);
        }
        return alive;
    }

    void solve(vector<vector<char>>& board) {
        vector<vector<bool>> checked(board.size(), vector<bool>(board.front().size(), false));
        for (auto i = 0; i < board.size(); i++) {
            for (auto j = 0; j < board.front().size(); j++) {
                if (checked[i][j]) { continue; }
                if (board[i][j] == 'O') {
                    set<POS> progress;
                    if (!dfs(board, POS(i, j), progress, checked)) {
                        for (auto&& captured_pos : progress) {
                            board[captured_pos.first][captured_pos.second] = 'X';
                        }
                    }
                }
            }
        }
    }
};

void test(vector<vector<char>>&& board)
{
    Solution().solve(board);
    for (auto&& row : board)
    {
        for (auto&& cell : row)
        {
			cout << cell << ",";
		}
		cout << endl;
	}
}	

int main()
{
    test({ {'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'} });
    test({ {'X',} });
    test({ {'O',} });
}