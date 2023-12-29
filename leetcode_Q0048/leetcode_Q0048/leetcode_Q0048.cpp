// leetcode_Q0048.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    static void rotate1(vector<vector<int>>& matrix, int index) {
        const int left = index;
        const int right = static_cast<int>(matrix.size() - 1) - index;
        for (int i = 0; i < matrix.size() - 1 - 2 * index; i++) {
            const auto left_top = make_pair(left, left + i);
            const auto right_top = make_pair(left + i, right);
            const auto right_bottom = make_pair(right, right - i);
            const auto left_bottom = make_pair(right - i, left);

            auto temp = matrix[left_top.first][left_top.second];
            matrix[left_top.first][left_top.second] = matrix[left_bottom.first][left_bottom.second];
            matrix[left_bottom.first][left_bottom.second] = matrix[right_bottom.first][right_bottom.second];
            matrix[right_bottom.first][right_bottom.second] = matrix[right_top.first][right_top.second];
            matrix[right_top.first][right_top.second] = temp;
        }

    }

    void rotate(vector<vector<int>>& matrix) {
        for (int i = 0; i < static_cast<int>(matrix.size()) / 2; i++) {
            rotate1(matrix, i);
        }
    }
};

void test(vector<vector<int>>&& matrix) {
    Solution().rotate(matrix);
    for (auto&& list : matrix) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    test({ {1}, });

    test({ {1,2,3}, {4,5,6 }, {7,8,9}, });
    test({{5, 1, 9, 11}, {2, 4, 8, 10 }, {13, 3, 6, 7}, {15, 14, 12, 16}} );
    test({ {1,2,3,4,5,}, {6,7,8,9,10 }, {11,12,13,14,15}, {16, 17, 18, 19,20,},{21,22,23,24,25,} });
}

