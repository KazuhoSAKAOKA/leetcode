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

class NumMatrix {

    vector<vector<int>> base_matrix;
    vector<vector<long long>> prefix_sums;
    vector<pair<pair<int, int>, int>> lazys;

    static vector<vector<long long>> create_prefix_sums(const vector<vector<int>>& matrix) {
        const auto n = size(matrix);
        const auto m = size(matrix[0]);
        vector<vector<long long>> prefix_sums(n + 1, vector<long long>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + static_cast<long long>(matrix[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }
        return prefix_sums;
    }
public:
    NumMatrix(vector<vector<int>>& matrix) :base_matrix(matrix), prefix_sums(create_prefix_sums(matrix)){

    }

    void update(int row, int col, int val) {
        const auto diff = val - base_matrix[row][col];
        lazys.push_back({ {row,col},diff });
        base_matrix[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        auto sum = prefix_sums[row2 + 1][col2 + 1] - prefix_sums[row2 + 1][col1] - prefix_sums[row1][col2 + 1] + prefix_sums[row1][col1];

        for (auto&& [p, diff] : lazys) {
            const auto [y, x] = p;
            if (row1 <= y && y <= row2 && col1 <= x && x <= col2) {
                sum += diff;
            }
        }
        return static_cast<int>(sum);
    }
};


int main() {


    return 0;
}