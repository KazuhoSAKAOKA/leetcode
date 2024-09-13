// leetcode_Q1310.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> prefix_xors(size(arr) + 1);

        for (size_t i = 0; i < size(arr); i++) {
            prefix_xors[i + 1] = prefix_xors[i] ^ arr[i];
        }

        vector<int> ans(size(queries));

        for (size_t i = 0; i < size(queries); i++) {
            const auto l = queries[i][0];
            const auto r = queries[i][1];
            ans[i] = prefix_xors[r + 1] ^ prefix_xors[l];
        }
        return ans;
    }
};

void test(vector<int>&& arr, vector<vector<int>>&& queries) {
    output(Solution().xorQueries(arr, queries));
}

int main()
{
    test(get_list_int("[1,3,4,8]"), get_matrix_int("[[0,1],[1,2],[0,3],[3,3]]"));
    test(get_list_int("[4,8,2,10]"), get_matrix_int("[[2,3],[1,3],[0,0],[0,3]]"));
    return 0;
}