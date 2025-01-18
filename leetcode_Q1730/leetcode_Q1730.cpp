// leetcode_Q1730.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        const size_t H = size(grid);
        const size_t W = size(grid.front());

        auto get_start = [&]()->pair<int,int> {
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (grid[i][j] == '*') {
                        return { i,j };
                    }
                }
            }
            return { -1,-1 };
            };
        const auto [starty, startx] = get_start();

        queue<tuple<int, int, int>> q;
        q.push({ starty,startx, 0 });
        vector<vector<bool>> visited(H, vector<bool>(W, false));
        visited[starty][startx] = true;

        const vector<pair<int, int>> directions{
            {-1,0},{1,0}, {0,-1}, {0, 1},
        };

        while (!q.empty()) {
            const auto [y, x, step] = q.front();
            q.pop();
            for (auto&& [dy, dx] : directions) {
                const auto next_y = y + dy;
                const auto next_x = x + dx;
                if (0 <= next_y && next_y < H && 0 <= next_x && next_x < W && !visited[next_y][next_x]) {
                    if (grid[next_y][next_x] == '#') {
                        return step + 1;
                    }
                    else if (grid[next_y][next_x] == 'O') {
                        visited[next_y][next_x] = true;
                        q.push({ next_y,next_x, step + 1 });
                    }
                }
            }
        }

        return -1;
    }
};

void test(vector<vector<char>>&& grid) {
    cout << Solution().getFood(grid) << endl;
}

int main()
{
    test(get_matrix_char(R"([["X","X","X","X","X","X"],["X","*","O","O","O","X"],["X","O","O","#","O","X"],["X","X","X","X","X","X"]])"));
    test(get_matrix_char(R"([["X","X","X","X","X"],["X","*","X","O","X"],["X","O","X","#","X"],["X","X","X","X","X"]])"));
    test(get_matrix_char(R"([["X","X","X","X","X","X","X","X"],["X","*","O","X","O","#","O","X"],["X","O","O","X","O","O","X","X"],["X","O","O","O","O","#","O","X"],["X","X","X","X","X","X","X","X"]])"));
    return 0;
}