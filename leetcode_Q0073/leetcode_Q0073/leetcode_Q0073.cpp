// leetcode_Q0073.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    static void ignore(vector<vector<int>>& matrix) {
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

    void setZeroes(vector<vector<int>>& matrix) {
        const auto m = size(matrix.front());
        const auto n = size(matrix);
        bool iszero_first_row = false;
        for (int j = 0; j < m; j++) {
            if (matrix[0][j] == 0) {
                iszero_first_row = true;
                break;
            }
        }
        bool iszero_first_col = false;
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0) {
                iszero_first_col = true;
                break;
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (int i = 1; i < n; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 0; j < m; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int j = 1; j < m; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 0; i < n; i++) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (iszero_first_row) {
            for (int j = 0; j < m; j++) {
                matrix[0][j] = 0;
            }
        }
        if (iszero_first_col) {
            for (int i = 0; i < n; i++) {
                matrix[i][0] = 0;
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
    test({ {0,0,0,5},{4,3,1,4},{0,1,1,4},{1,2,1,3},{0,0,1,1} });
    test({ {0, 1, 2, 0}, { 3,4,5,2 }, { 1,3,1,5 } });
    test({ {1, 2, 3, 4}, { 5,0,7,8 }, {0,10,11,12 },{13,14,15,0}, });
    test({ {1, 1, 1}, { 1,0,1 }, { 1,1,1 } });

}
