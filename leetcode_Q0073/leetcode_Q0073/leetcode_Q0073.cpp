// leetcode_Q0073.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<bool> rows(matrix.size(), false);
        vector<bool> cols(matrix.front().size(), false);

        for (auto i = 0; i < matrix.size(); i++) {
            for (auto j = 0; j < matrix.front().size(); j++) {
                if (matrix[i][j] == 0) {
                    rows[i] = true;
                    cols[j] = true;
                }
            }
        }

        for (auto i = 0; i < matrix.size(); i++) {
            if (rows[i]) {
                for (auto j = 0; j < matrix.front().size(); j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (auto j = 0; j < matrix.front().size(); j++) {
            if (cols[j]) {
                for (auto i = 0; i < matrix.size(); i++) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

void test(vector<vector<int>>&& matrix) {
    Solution().setZeroes(matrix);

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
    test({ {1, 1, 1}, { 1,0,1 }, { 1,1,1 } });
    test({ {0, 1, 2, 0}, { 3,4,5,2 }, { 1,3,1,5 } });

}
