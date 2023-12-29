// leetcode_Q0059.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ret(n, vector<int>(n, 0));
        int index = 0;
        int col = 0;
        int row = 0;
        enum Direction {
            R,D,L,U,
        };
        int colMin = 0;
        int colMax = n - 1;
        int rowMin = 0;
        int rowMax = n - 1;
        Direction currentDirection = Direction::R;
        while (index < n * n) {
            ret[row][col] = (index + 1);

            switch (currentDirection)
            {
            case R:
                if (col < colMax) {
                    col++;
                }
                else {
                    currentDirection = Direction::D;
                    row++;
                    rowMin++;
                }
                break;
            case D:
                if (row < rowMax) {
                    row++;
                }
                else {
                    currentDirection = Direction::L;
                    col--;
                    colMax--;
                }
                break;
            case L:
                if (colMin < col) {
                    col--;
                }
                else {
                    currentDirection = Direction::U;
                    row--;
                    rowMax--;
                }
                break;
            case U:
                if (rowMin < row) {
                    row--;
                }
                else {
                    currentDirection = Direction::R;
                    col++;
                    colMin++;
                }
                break;
            default:
                break;
            }

            index++;
        }


        return ret;
    }
};


void test(int n) {
    const auto ans = Solution().generateMatrix(n);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    test(3);
    test(1);

    test(10);
}

