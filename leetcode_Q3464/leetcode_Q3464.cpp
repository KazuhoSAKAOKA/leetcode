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

    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        const auto n = size(points);
        const long long max_distance = 4LL * side;


        auto convert_distance = [&](const vector<int>& p)-> long long {
            if (p[0] == 0) {
                return 0LL + static_cast<long long>(p[1]);
            }
            else if (p[1] == side) {
                return static_cast<long long>(side) + static_cast<long long>(p[0]);
            }
            else if (p[0] == side) {
                return static_cast<long long>(side) * 2 + static_cast<long long>(side - p[1]);
            }
            return static_cast<long long>(side) * 3 + static_cast<long long>(side - p[0]);
            };

        vector<long long> positions(n);

        for (size_t i = 0; i < n; i++) {
            positions[i] = convert_distance(points[i]);
        }
        sort(begin(positions), end(positions));

        auto get_distance = [&](size_t index0, size_t index1)-> long long {
            if (index0 < index1) {
                return positions[index1] - positions[index0];
            }
            else {
                return ((max_distance - positions[index0]) + positions[index1]);
            }
            };

        auto inner_check = [&](size_t start, int dist)->bool {
            long long current_index = 0;
            for (int i = 0; i < k - 1; i++) {
                if (n <= current_index) { return false; }
                auto check1 = [&](long long index)->bool {
                    const auto index0 = (start + current_index) % n;
                    const auto index1 = (start + current_index + index) % n;
                    return get_distance(index0, index1) >= dist;
                    };
                long long ok = n - current_index - 1;
                if (!check1(ok)) { return false; }
                long long ng = 0;
                const auto v = binary_search_meguru<long long>(ok, ng, check1);
                if (v == ng) {
                    return false;
                }
                current_index += v;
            }
            return get_distance((start + current_index) % n, start) >= dist;
            };


        auto check = [&](int v)->bool {
            for (size_t i = 0; i < n; i++) {
                if (inner_check(i, v)) {
                    return true;
                }
            }
            return false;
            };

        int ok = 1;
        int ng = side + 1;
        const auto ans = binary_search_meguru<int>(ok, ng, check);

        return ans;
    }
};
static void test(int side, vector<vector<int>>&& points, int k) {
	cout << Solution().maxDistance(side, points, k) << endl;
}

int main() {
    test(13, get_matrix_int("[[5,0],[0,3],[9,13],[0,0],[0,13],[10,13]]"), 4);
    test(2, get_matrix_int("[[0,2],[2,0],[2,2],[0,0]]"), 4);
	test(2, get_matrix_int("[[0,0],[1,2],[2,0],[2,2],[2,1]]"), 4);
	test(2, get_matrix_int("[[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]]"), 5);
	return 0;
}
