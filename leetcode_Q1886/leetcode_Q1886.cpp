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

    static pair<int, int> add(const pair<int, int>& a, const pair<int, int>& b) {
        return { a.first + b.first, a.second + b.second };
    }

    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        const int n = size(mat);
        if (n % 2 == 1) {
            if (mat[n / 2][n / 2] != target[n / 2][n / 2]) {
                return false;
            }
        }
        static vector<pair<int, int>> directions{
            {0,1},{1,0},{0,-1}, {-1,0},
        };
        auto create_start = [](int n, int rotate_index, int offset)->pair<int,int>{
            if (rotate_index == 0) {
                return { offset,offset };
            }
            else if (rotate_index == 1) {
                return { offset, n - offset - 1 };
            }
            else if (rotate_index == 2) {
                return { n - offset - 1, n - offset - 1 };
            }
            else {
                return { n - offset - 1, offset };
            }
        };
        for (int r = 0; r < 4; r++) {
            bool ok = true;
            for (int offset = 0; offset < n / 2 && ok; offset++) {
                const auto len = n - offset * 2;
                pair<int, int> base_current{ offset, offset };
                pair<int, int> target_current = create_start(n, r, offset);
                for (int edge = 0; edge < 4 && ok; edge++) {
                    const auto base_current_dir = directions[edge];
                    const auto target_current_dir = directions[(r + edge) % 4];
                    for (int j = 0; (j < len - 1) && ok; j++) {
                        if (mat[base_current.first][base_current.second] != target[target_current.first][target_current.second]) {
                            ok = false;
                        }
                        base_current = add(base_current, base_current_dir);
                        target_current = add(target_current, target_current_dir);
                    }
                }
            }
            if (ok) {
                return true;
            }
        }
        return false;
    }
};

static void test(vector<vector<int>>&& mat, vector<vector<int>>&& target) {
    cout << Solution().findRotation(mat, target) << endl;
}

int main() {
    test(get_matrix_int("[[0,0,0,0],[0,1,0,0],[1,1,1,1],[1,1,1,1]]"), get_matrix_int("[[0,0,0,0],[0,1,0,0],[1,0,1,1],[1,1,1,1]]"));
    test(get_matrix_int("[[0,0,0],[0,1,0],[1,1,1]]"), get_matrix_int("[[1,1,1],[0,1,0],[0,0,0]]"));
    test(get_matrix_int("[[0,1],[1,0]]"), get_matrix_int("[[1,0],[0,1]]"));
    test(get_matrix_int("[[0,1],[1,1]]"), get_matrix_int("[[1,0],[0,1]]"));
    return 0;
}

