// leetcode_Q0773.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    struct board_t {
        int cell[6];

        int get_key() const {
            return cell[0] * 100000 + cell[1] * 10000 + cell[2] * 1000 + cell[3] * 100 + cell[4] * 10 + cell[5] * 1;
        }

        vector<board_t> get_next_states() const {
            if (cell[0] == 0) {
                return {
                    board_t{  cell[1], cell[0], cell[2], cell[3], cell[4], cell[5] },
                    board_t{  cell[3], cell[1], cell[2], cell[0], cell[4], cell[5] },
                };
            }
            else if (cell[1] == 0) {
                return {
                    board_t{  cell[1], cell[0], cell[2], cell[3], cell[4], cell[5] },
                    board_t{  cell[0], cell[2], cell[1], cell[3], cell[4], cell[5] },
                    board_t{  cell[0], cell[4], cell[2], cell[3], cell[1], cell[5] },
                };
            }
            else if (cell[2] == 0) {
                return {
                    board_t{  cell[0], cell[2], cell[1], cell[3], cell[4], cell[5] },
                    board_t{  cell[0], cell[1], cell[5], cell[3], cell[4], cell[2] },
                };
            }
            else if (cell[3] == 0) {
                return {
                    board_t{  cell[3], cell[1], cell[2], cell[0], cell[4], cell[5] },
                    board_t{  cell[0], cell[1], cell[2], cell[4], cell[3], cell[5] },
                };
            }
            else if (cell[4] == 0) {
                return {
                    board_t{  cell[0], cell[4], cell[2], cell[3], cell[1], cell[5] },
                    board_t{  cell[0], cell[1], cell[2], cell[4], cell[3], cell[5] },
                    board_t{  cell[0], cell[1], cell[2], cell[3], cell[5], cell[4] },
                };
            }
            else if (cell[5] == 0) {
                return {
                    board_t{  cell[0], cell[1], cell[2], cell[3], cell[5], cell[4] },
                    board_t{  cell[0], cell[1], cell[5], cell[3], cell[4], cell[2] },
                };
            }
            throw exception();
        }

    };
    int slidingPuzzle(vector<vector<int>>& board) {
        board_t start_state;
        start_state.cell[0] = board[0][0];
        start_state.cell[1] = board[0][1];
        start_state.cell[2] = board[0][2];
        start_state.cell[3] = board[1][0];
        start_state.cell[4] = board[1][1];
        start_state.cell[5] = board[1][2];
        using INFO = pair<board_t, int>;
        queue<INFO> qu;
        qu.push({ start_state, 0 });
        unordered_set<int> checked;
        const int GOAL = 123450;
        if (start_state.get_key() == GOAL) {
            return 0;
        }
        checked.insert(start_state.get_key());

        while (!qu.empty()) {
            const auto [current_state, step] = qu.front();
            qu.pop();
            const auto next_states = current_state.get_next_states();
            for (auto&& next : next_states) {
                const auto key = next.get_key();
                if (key == GOAL) {
                    return step + 1;
                }
                if (checked.find(key) == cend(checked)) {
                    qu.push({ next , step + 1 });
                    checked.insert(key);
                }
            }
        }
        return -1;
    }
};

void test(vector<vector<int>>&& board) {
    cout << Solution().slidingPuzzle(board) << endl;
}
int main()
{
    test(get_matrix_int("[[1,2,3],[4,0,5]]"));
    test(get_matrix_int("[[1,2,3],[5,4,0]]"));
    test(get_matrix_int("[[4,1,2],[5,0,3]]"));
    return 0;
}