// leetcode_Q1380.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        vector<int> indexes(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            const auto it = min_element(cbegin(matrix[i]), cend(matrix[i]));
            indexes[i] = distance(cbegin(matrix[i]), it);
        }

        auto get_min_element_index_row = [&](int col_index) {
            int max_element_index = -1;
            int max_value = INT_MIN;
            for (int i = 0; i < matrix.size(); i++) {
                if (max_value < matrix[i][col_index]) {
                    max_value = matrix[i][col_index];
                    max_element_index = i;
                }
            }
            return max_element_index;
            };
        vector<int> ans;
        for (int i = 0; i < matrix.front().size(); i++) {
            const auto min_element_index = get_min_element_index_row(i);
            if (indexes[min_element_index] == i) {
                ans.push_back(matrix[min_element_index][i]);
            }
        }

        return ans;
    }
};

void test(vector<vector<int>>&& matrix) {
    const auto ans = Solution().luckyNumbers(matrix);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(get_matrix_int("[[3,7,8],[9,11,13],[15,16,17]]"));
    test(get_matrix_int("[[1,10,4,2],[9,3,8,7],[15,16,17,12]]"));
    test(get_matrix_int("[[7,8],[1,2]]"));
    return 0;
}