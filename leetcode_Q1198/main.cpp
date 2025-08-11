#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        const auto height = size(mat);
        vector<int> ptrs(height, 0);
        map<int, int> values;
        auto compare = [&](int a, int b) {
            return mat[a][ptrs[a]] > mat[b][ptrs[b]];
            };
        priority_queue<int, vector<int>, decltype(compare)> q(compare);

        for (int i = 0; i < height; i++) {
            values[mat[i][0]]++;
            q.push(i);
        }

        while (size(values) > 1) {
            auto top = q.top();
            q.pop();
            auto cur_value = mat[top][ptrs[top]];
            auto it = values.find(cur_value);
            if (it->second == 1) {
                values.erase(it);
            }
            else {
                it->second--;
            }
            ptrs[top]++;
            if (size(mat[top]) == ptrs[top]) {
                return -1;
            }
            values[mat[top][ptrs[top]]]++;
            q.push(top);
        }
        return cbegin(values)->first;
    }
};
static void test(vector<vector<int>>&& mat) {
    cout << Solution().smallestCommonElement(mat) << endl;
}
int main() {
    test(get_matrix_int("[[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]"));
    test(get_matrix_int("[[1,2,3],[2,3,4],[2,3,5]]"));
    test(get_matrix_int("[[1,2,3],[4,5,6],[7,8,9]]"));
    return 0;
}