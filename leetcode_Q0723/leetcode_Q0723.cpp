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

class Solution {
public:
    
    static void shift(vector<vector<int>>& board) {
        const int h = size(board);
        const int w = size(board.front());
        for (int x = 0; x < w; x++) {
            int zero_top = h - 1;
            while (zero_top >= 0) {
                if (board[zero_top][x] == 0) {
                    break;
                }
                zero_top--;
            }
            if (zero_top > 0) {
                int value_top = zero_top - 1;
                while (value_top >= 0) {
                    while (value_top >= 0 && board[value_top][x] == 0) {
                        value_top--;
                    }
                    if (value_top >= 0) {
                        board[zero_top--][x] = board[value_top--][x];
                    }
                }
                while (zero_top >= 0) {
                    board[zero_top--][x] = 0;
                }
            }
        }
    }

    static bool crush(vector<vector<int>>& board) {
        const int h = size(board);
        const int w = size(board.front());
        const int s = h * w;
        vector<tuple<int, int, int>> left_points;
        vector<tuple<int, int, int>> top_points;
        bool exist = false;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (board[i][j] != 0) {
                    const auto v = board[i][j];
                    if (j < w - 2) {
                        if (v == board[i][j + 1] && v == board[i][j + 2]) {
                            int len = 3;
                            while (j + len < w && board[i][j + len] == v) {
                                len++;
                            }
                            left_points.push_back({ i,j, len });
                            exist = true;
                        }
                    }
                    if (i < h - 2) {
                        if (v == board[i + 1][j] && v == board[i + 2][j]) {
                            int len = 3;
                            while (i + len < h && board[i + len][j] == v) {
                                len++;
                            }
                            top_points.push_back({ i,j,len });
                            exist = true;
                        }
                    }
                }
            }
        }

        for (auto&& [i, j, len] : left_points) {
            for (int k = 0; k < len; k++) {
                board[i][j + k] = 0;
            }
        }
        for (auto&& [i, j, len] : top_points) {
            for (int k = 0; k < len; k++) {
                board[i + k][j] = 0;
            }
        }
        return exist;
    }


    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        while (crush(board)) {
            shift(board);
        }
        return board;
    }
};

static void test(vector<vector<int>>&& board) {
    output_matrix(Solution().candyCrush(board));
}

int main() {
    //auto temp = get_matrix_int("[[1,1,1,1],[1,1,0,1],[1,1,1,1],[1,1,0,1]]");
    //Solution::shift(temp);
    //output_matrix(temp);

    test(get_matrix_int("[[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]"));
    test(get_matrix_int("[[1,3,5,5,2],[3,4,3,3,1],[3,2,4,5,2],[2,4,4,5,5],[1,4,4,1,1]]"));
    return 0;
}
