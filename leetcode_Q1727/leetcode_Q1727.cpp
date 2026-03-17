#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        const auto n = size(matrix);
        const auto m = size(matrix.front());

        vector<vector<int>> streaks(n, vector<int>(m));

        for (int j = 0; j < m; j++) {
            int cur_streak = 0;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] == 1) {
                    cur_streak++;
                    streaks[i][j] = cur_streak;
                }
                else {
                    cur_streak = 0;
                }
            }
        }
        int largest = 0;
        for (int i = 0; i < n; i++) {
            map<int, int, greater<int>> freqs;
            for (int j = 0; j < m; j++) {
                freqs[streaks[i][j]]++;
            }
            int cur_width = 0;
            for (auto&& [height, width] : freqs) {
                cur_width += width;
                largest = max(largest, height * cur_width);
            }
        }

        return largest;
    }
};
static void test(vector<vector<int>>&& matrix) {
    cout << Solution().largestSubmatrix(matrix) << endl;
}
int main()
{
    test(get_matrix_int("[[0,0,1],[1,1,1],[1,0,1]]"));
    test(get_matrix_int("[[1,0,1,0,1]]"));
    test(get_matrix_int("[[1,1,0],[1,0,1]]"));

    return 0;
}