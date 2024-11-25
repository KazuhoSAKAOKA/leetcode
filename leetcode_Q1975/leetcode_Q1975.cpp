// leetcode_Q1975.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int get_current_value(const vector<vector<int>>& matrix, vector<vector<bool>>& operates, const pair<int, int>& coodinate) {
        return (operates[coodinate.second][coodinate.first] ? -1 : 1) * matrix[coodinate.second][coodinate.first];
    }
    static long long rec(const vector<vector<int>>& matrix, vector<vector<bool>>& operates, const vector<pair<pair<int,int>, pair<int,int>>>& coodinates, size_t index, long long total) {
        if (index==size(coodinates)) {
            return total;
        }
        long long max_sum = rec(matrix, operates, coodinates, index + 1, total);
        const auto& p1 = coodinates[index].first;
        const auto& p2 = coodinates[index].second;
        const auto cur_v1 = get_current_value(matrix, operates, p1);
        const auto cur_v2 = get_current_value(matrix, operates, p2);
        operates[p1.second][p1.first] = !operates[p1.second][p1.first];
        operates[p2.second][p2.first] = !operates[p2.second][p2.first];
        const auto op_total = total - 2 * (cur_v1 + cur_v2);
        max_sum = max(max_sum, rec(matrix, operates, coodinates, index + 1, op_total));
        operates[p1.second][p1.first] = !operates[p1.second][p1.first];
        operates[p2.second][p2.first] = !operates[p2.second][p2.first];

        return max_sum;
    }

    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long total = 0;
        vector<vector<bool>> operates(size(matrix), vector<bool>(size(matrix.front())));
        vector<pair<pair<int, int>, pair<int, int>>> coodinates;
        for (int i = 0; i < size(matrix); i++) {
            for (int j = 0; j < size(matrix[i]); j++) {
                total += static_cast<long long>(matrix[i][j]);
                if (i < size(matrix) - 1 && j < size(matrix.front())) {
                    coodinates.emplace_back(make_pair(make_pair(j, i), make_pair(j, i + 1)));
                }
                if (i < size(matrix) && j < size(matrix.front()) - 1) {
                    coodinates.emplace_back(make_pair(make_pair(j, i), make_pair(j + 1, i)));
                }
            }
        }


        return rec(matrix, operates, coodinates, 0, total);
    }
};

void test(vector < vector<int>>&& matrix) {
    cout << Solution().maxMatrixSum(matrix) << endl;
}

int main()
{
    test(get_matrix_int("[[-9,9,9,-9],[-10,10,7,5],[4,-8,-9,6],[10,2,-6,1]]"));

    test(get_matrix_int("[[1,2,3],[-1,-2,-3],[1,2,3]]"));
    test(get_matrix_int("[[1,-1],[-1,1]]"));
    return 0;
}