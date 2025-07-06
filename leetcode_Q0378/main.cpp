#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>
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

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        const auto n = size(matrix);
        auto check = [&](int cur_val)->bool {
            int total = 0;
            for (int i = 0; i < n; i++) {
                const auto it = upper_bound(cbegin(matrix[i]), cend(matrix[i]), cur_val);
                total += distance(cbegin(matrix[i]), it);
            }
            return total <= k;
            };
        const auto val = binary_search_meguru<int>(matrix[0][0], matrix[n - 1][n - 1] + 1, check);
        return val;
    }
};
void test(vector<vector<int>>&& matrix, int k) {
    cout << Solution().kthSmallest(matrix, k) << endl;
}

int main() {
    test(get_matrix_int("[[1,2],[1,3]]"), 3);
    test(get_matrix_int("[[1,1],[1,1]]"), 1);
    test(get_matrix_int("[[1,5,9],[10,11,13],[12,13,15]]"), 8);
	return 0;
}