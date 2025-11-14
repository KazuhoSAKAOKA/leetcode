#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff_matrixes(n + 1, vector<int>(n + 1));
        for (auto&& q : queries) {
            diff_matrixes[q[0]][q[1]]++;
            diff_matrixes[q[2] + 1][q[1]]--;
            diff_matrixes[q[0]][q[3] + 1]--;
            diff_matrixes[q[2] + 1][q[3] + 1]++;
        }

        vector<vector<int>> diff_matrixes2(n + 1, vector<int>(n + 1));
        for (int j = 0; j < n; j++) {
            int cur = 0;
            for (int i = 0; i < n; i++) {
                cur += diff_matrixes[i][j];
                diff_matrixes2[i][j] = cur;
            }
        }
        vector<vector<int>> ans(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            int cur = 0;
            for (int j = 0; j < n; j++) {
                cur += diff_matrixes2[i][j];
                ans[i][j] = cur;
            }
        }

        return ans;
    }
};

static void test(int n, vector<vector<int>>&& queries) {
	output_matrix(Solution().rangeAddQueries(n, queries));
}

int main()
{
    test(2, get_matrix_int("[[0,0,1,1]]"));
    test(13, get_matrix_int("[[3,1,7,3],[7,5,7,8],[4,12,6,12],[2,8,6,11],[9,11,10,11],[9,3,11,11],[0,12,10,12],[10,5,11,12],[4,7,6,12],[0,2,9,6],[12,7,12,11],[2,7,3,8],[2,9,6,12],[10,7,10,12],[11,6,11,7],[3,2,12,9]]"));
    test(3, get_matrix_int("[[1,1,2,2],[0,0,1,1]]"));
    return 0;
}
