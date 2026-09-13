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
#include <bitset>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        const int n = size(img1);

        auto counting = [&](int offsety, int offsetx)->int {
            const auto ycount = n - abs(offsety);
            const auto xcount = n - abs(offsetx);
            int count = 0;
            for (int y = 0; y < ycount; y++) {
                const auto y1 = y - min(0, offsety);
                const auto y2 = y + max(0, offsety);
                for (int x = 0; x < xcount; x++) {
                    const auto x1 = x - min(0, offsetx);
                    const auto x2 = x + max(0, offsetx);
                    if (img1[y1][x1] == 1 && img2[y2][x2] == 1) {
                        count++;
                    }
                }
            }
            return count;
            };

        int ans = 0;
        for (int oy = -n + 1; oy <= n - 1; oy++) {
            for (int ox = -n + 1; ox <= n - 1; ox++) {
                ans = max(ans, counting(oy, ox));
            }
        }
        return ans;
    }
};

static void test(vector<vector<int>>&& img1, vector<vector<int>>&& img2) {
    cout << Solution().largestOverlap(img1, img2) << endl;
}

int main() {
    test(get_matrix_int("[[1,1,0],[0,1,0],[0,1,0]]"), get_matrix_int("[[0,0,0],[0,1,1],[0,0,1]]"));
    test(get_matrix_int("[[1]]"), get_matrix_int("[[1]]"));
    test(get_matrix_int("[[0]]"), get_matrix_int("[[0]]"));
    return 0;
}
