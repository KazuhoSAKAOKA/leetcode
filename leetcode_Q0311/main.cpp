#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        const auto m = size(mat1);
        const auto k = size(mat1.front());
        const auto k1 = size(mat2);
        const auto n = size(mat2.front());
        if (k != k1) { throw exception(); }

        vector<vector<int>> ans(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int s = 0;
                for (int l = 0; l < k; l++) {
                    s += mat1[i][l] * mat2[l][j];
                }
                ans[i][j] = s;
            }
        }

        return ans;
    }
};

void test(vector<vector<int>>&& mat1, vector<vector<int>>&& mat2) {
    output_matrix(Solution().multiply(mat1, mat2));
}
int main() {
    test(get_matrix_int("[[1,0,0],[-1,0,3]]"), get_matrix_int("[[7,0,0],[0,0,0],[0,0,1]]"));
    test(get_matrix_int("[[0]]"), get_matrix_int("[[0]]"));
    return 0;
}