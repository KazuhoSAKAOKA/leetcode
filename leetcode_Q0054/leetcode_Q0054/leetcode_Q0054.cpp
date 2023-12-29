// leetcode_Q0054.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        const auto w = matrix[0].size();
        const auto h = matrix.size();
        const auto size = w * h;
        ans.reserve(size);

        size_t index = 0;
        int x = 0;
        int y = 0;
        int xLower = 0;
        int xHigher = static_cast<int>(w) - 1;
        int yLower = 0;
        int yHigher = static_cast<int>(h) - 1;
        enum class Direction {
            R,D,L,U,
        };
        auto currentDir = Direction::R;
        while (index < size) {
            ans.emplace_back(matrix[y][x]);
            switch (currentDir)
            {
            case Direction::R:
                if (x < xHigher) {
                    x++;
                }
                else {
                    currentDir = Direction::D;
                    y++;
                    yLower++;
                }
                break;
            case Direction::D:
                if (y < yHigher) {
                    y++;
                }
                else {
                    currentDir = Direction::L;
                    x--;
                    xHigher--;
                }
                break;
            case Direction::L:
                if (xLower < x) {
                    x--;
                }
                else {
                    currentDir = Direction::U;
                    y--;
                    yHigher--;
                }
                break;
            case Direction::U:
                if (yLower < y) {
                    y--;
                }
                else {
                    currentDir = Direction::R;
                    x++;
                    xLower++;
                }
                break;
            default:
                break;
            }
            index++;
        }
        return ans;
    }
};

void test(vector<vector<int>>&& matrix) {
    const auto ret = Solution().spiralOrder(matrix);
    for (auto&& value : ret) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test({ {1,2,3} , {4,5,6},{7,8,9} });
    test({ {1,2,3,4 }, { 5,6,7,8 }, { 9,10,11,12 } });
}

