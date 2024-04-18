// leetcode_Q0463.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        using coodinate = pair<int, int>;
        vector<coodinate> directions{ {-1,0},{1,0},{0,-1}, {0,1}, };

        auto counting = [&](int k, int l) {
                if (k < 0 || grid.size() <= k || l < 0 || grid.front().size() <= l) {
                    return 1;
                }
                return grid[k][l] == 0 ? 1 : 0;
            };

        int total = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.front().size(); j++) {
                if (grid[i][j] == 1) {
                    total += accumulate(cbegin(directions), cend(directions), 0, [&](const auto a, const auto b)
                        {
                            return a + counting(i + b.first, j + b.second);
                        });
                }
            }
        }
        return total;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().islandPerimeter(grid) << endl;
}

int main()
{
    test({ { 0,1,0,0, }, { 1,1,1,0, }, { 0,1,0,0, }, { 1,1,0,0, } });
    test({ {1} });
    test({ {1,0,} });
}