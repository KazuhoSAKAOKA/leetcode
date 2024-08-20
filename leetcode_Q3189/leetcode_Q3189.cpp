// leetcode_Q3189.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minMoves(vector<vector<int>>& rooks) {
        vector<int> cols;
        vector<int> rows;
        cols.reserve(size(rooks));
        rows.reserve(size(rooks));
        for (auto&& rook : rooks) {
            cols.emplace_back(rook[0]);
            rows.emplace_back(rook[1]);
        }
        sort(begin(cols), end(cols));
        sort(begin(rows), end(rows));

        int moves = 0;
        for (int i = 0; i < size(rooks); i++) {
            moves += abs(i - cols[i]);
            moves += abs(i - rows[i]);
        }
        return moves;
    }
};

void test(vector<vector<int>>&& rooks) {
    cout << Solution().minMoves(rooks) << endl;
}
int main()
{
    test(get_matrix_int("[[0,0],[1,0],[1,1]]"));
    test(get_matrix_int("[[0,0],[0,1],[0,2],[0,3]]"));
    return 0;
}