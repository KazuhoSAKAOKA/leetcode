// leetcode_Q0200.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    static void check_connected(const vector<vector<char>>& grid, vector<vector<bool>>& checked, int i, int j) {
        static vector<pair<int, int>> directions{ {-1, 0}, {1,0}, {0, -1}, {0, 1}, };
        for (auto&& dir : directions) {
            const auto i1 = i + dir.first;
            const auto j1 = j + dir.second;
            if (i1 < 0 || grid.size() <= i1 || j1 < 0 || grid.front().size() <= j1) {
                continue;
            }
            if (checked[i1][j1]) { continue; }
            if (grid[i1][j1] != '1') { continue; }
            checked[i1][j1] = true;
            check_connected(grid, checked, i1, j1);
        }
    }


    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> checked(grid.size(), vector<bool>(grid.front().size(), false));

        int count = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.front().size(); j++) {
                if (checked[i][j]) { continue; }
                if (grid[i][j] == '1') {
                    count++;
                    checked[i][j] = true;
                    check_connected(grid, checked, i, j);
                }
            }
        }


        return count;
    }
};

void test(vector<vector<char>>&& grid) {
    cout << Solution().numIslands(grid) << endl;
}
int main()
{
    test({ 
        {'1','1', '1', '1', '0'},
        {'1','1', '0', '1', '0'},
        {'1','1', '0', '0', '0'},
        {'0','0', '0', '0', '0'},
        });
    
    test({
        {'1','1', '0', '0', '0'},
        {'1','1', '0', '0', '0'},
        {'0','0', '1', '0', '0'},
        {'0','0', '0', '1', '1'},
        });
}