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

    int numSubseq(vector<int>& nums, int target) {
        const auto n = size(nums);
        constexpr long long MODULO = 1e9 + 7;
        sort(begin(nums), end(nums));

        vector<int> pow2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % MODULO;
        }
        long long count = 0;
        for (auto it = cbegin(nums); it != cend(nums); ++it) {
            const auto current = *it;
            if (target < current) {
                break;
            }
            const auto remain = target - current;
            if (remain < current) {
                break;
            }
            const auto limit_it = upper_bound(next(it), cend(nums), remain);
            const auto dist = distance(it, limit_it) - 1;
            count += pow2[dist];
            count %= MODULO;
        }
        return static_cast<int>(count % MODULO);
    }
};
void test(vector<int>&& nums, int target) {
    cout << Solution().numSubseq(nums, target) << endl;
}
int main() {
    test(get_list_int("[3,5,6,7]"), 9);
    test(get_list_int("[3,3,6,8]"), 10);
    test(get_list_int("[2,3,3,4,6,7]"), 12);
    return 0;
}