#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_set>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        const auto m = size(languages);
        vector<vector<bool>> language_matrix(n, vector<bool>(m));
        for (int i = 0; i < m; i++) {
            for (auto&& l : languages[i]) {
                language_matrix[l - 1][i] = true;
            }
        }

        auto check = [&](int a, int b)->bool {
            for (int i = 0; i < n; i++) {
                if (language_matrix[i][a] && language_matrix[i][b]) {
                    return true;
                }
            }
            return false;
            };
        unordered_set<int> not_connecteds;
        for (auto&& friendship : friendships) {
            const auto a = friendship[0] - 1;
            const auto b = friendship[1] - 1;
            if (!check(a, b)) {
                not_connecteds.insert(a);
                not_connecteds.insert(b);
            }
        }

        int min_count = m;
        for (int i = 0; i < n; i++) {
            int cur_count = 0;
            for (auto&& p : not_connecteds) {
                if (!language_matrix[i][p]) {
                    cur_count++;
                }
            }
            min_count = min(min_count, cur_count);
        }
        return min_count;
    }
};
static void test(int n, vector<vector<int>>&& languages, vector<vector<int>>&& friendships) {
    cout << Solution().minimumTeachings(n, languages, friendships) << endl;
}
int main() {
    test(11, get_matrix_int("[[3,11,5,10,1,4,9,7,2,8,6],[5,10,6,4,8,7],[6,11,7,9],[11,10,4],[6,2,8,4,3],[9,2,8,4,6,1,5,7,3,10],[7,5,11,1,3,4],[3,4,11,10,6,2,1,7,5,8,9],[8,6,10,2,3,1,11,5],[5,11,6,4,2]]"), get_matrix_int("[[7,9],[3,7],[3,4],[2,9],[1,8],[5,9],[8,9],[6,9],[3,5],[4,5],[4,9],[3,6],[1,7],[1,3],[2,8],[2,6],[5,7],[4,6],[5,8],[5,6],[2,7],[4,8],[3,8],[6,8],[2,5],[1,4],[1,9],[1,6],[6,7]]"));
    test(2, get_matrix_int("[[1],[2],[1,2]]"), get_matrix_int("[[1,2],[1,3],[2,3]]"));
    test(3, get_matrix_int("[[2],[1,3],[1,2],[3]]"), get_matrix_int("[[1,4],[1,2],[3,4],[2,3]]"));
    return 0;
}