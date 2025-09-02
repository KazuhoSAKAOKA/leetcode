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
    int numberOfPairs(vector<vector<int>>& points) {
        constexpr size_t N = 52;
        vector<vector<int>> prefix_sums(N + 1, vector<int>(N + 1, 0));
        for (auto&& point : points) {
            prefix_sums[point[0] + 1][point[1] + 1]++;
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i + 1][j];
            }
        }
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }
        auto f = [&](int sy, int sx, int ey, int ex)-> int {
            return prefix_sums[ey][ex] - prefix_sums[ey][sx] - prefix_sums[sy][ex] + prefix_sums[sy][sx];
            };

        int count = 0;

        for (int i = 0; i < size(points); i++) {
            const auto& p1 = points[i];
            for (int j = i + 1; j < size(points); j++) {
                const auto& p2 = points[j];
                const auto miny = min(p1[0], p2[0]);
                const auto maxy = max(p1[0], p2[0]);
                const auto minx = min(p1[1], p2[1]);
                const auto maxx = max(p1[1], p2[1]);
                if (
                    ((p1[0] == miny && p1[1] == maxx) && (p2[0] == maxy && p2[1] == minx)) ||
                    ((p2[0] == miny && p2[1] == maxx) && (p1[0] == maxy && p1[1] == minx))) {
                    const auto includes = f(miny, minx, maxy + 1, maxx + 1);
                    if (includes == 2) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};

static void test(vector<vector<int>>&& points) {
    cout << Solution().numberOfPairs(points) << endl;
}
int main() {
    test(get_matrix_int("[[0,0],[0,3]]"));
    test(get_matrix_int("[[3,1],[1,3],[1,1]]"));
    test(get_matrix_int("[[1,1],[2,2],[3,3]]"));
    test(get_matrix_int("[[6,2],[4,4],[2,6]]"));
    return 0;
}