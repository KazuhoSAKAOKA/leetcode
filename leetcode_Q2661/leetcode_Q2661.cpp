// leetcode_Q2661.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>


#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        const auto H = size(mat);
        const auto W = size(mat.front());
        vector<int> rows(H);
        vector<int> cols(W);
        vector<pair<int, int>> refs(size(arr));
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                refs[mat[r][c] - 1] = { r,c };
            }
        }
        for (int i = 0; i < size(arr); i++) {
            const auto [row, col] = refs[arr[i] - 1];
            rows[row]++;
            if (rows[row] == W) { return i; }
            cols[col]++;
            if (cols[col] == H) { return i; }
        }
        return -1;
    }
};

void test(vector<int>&& arr, vector<vector<int>>&& mat) {
    cout << Solution().firstCompleteIndex(arr, mat) << endl;
}

int main()
{
    test(get_list_int("[1,4,5,2,6,3]"), get_matrix_int("[[4,3,5],[1,2,6]]"));
    test(get_list_int("[1,3,4,2]"), get_matrix_int("[[1,4],[2,3]]"));
    test(get_list_int("[2,8,7,4,1,3,5,6,9]"), get_matrix_int("[[3,2,5],[1,4,6],[8,7,9]]"));
    return 0;
}