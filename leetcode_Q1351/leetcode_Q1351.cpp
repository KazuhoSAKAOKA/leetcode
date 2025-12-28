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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int count = 0;
        for (auto&& row : grid) {
            auto it = upper_bound(cbegin(row), cend(row), 0, [](int a, int b)->bool { return a > b; });
            if (it != cend(row)) {
                count += distance(it, cend(row));
            }
        }
        return count;
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().countNegatives(grid) << endl;
}
int main()
{
    test(get_matrix_int("[[1,-1],[-1,-1]]"));
    test(get_matrix_int("[[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]"));
    test(get_matrix_int("[[3,2],[1,0]]"));
    return 0;
}