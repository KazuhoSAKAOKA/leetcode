
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
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        const long long n = size(nums1);
        vector<long long> indexes(n);
        for (long long i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](auto a, auto b) { return abs(nums1[a] - nums2[a]) > abs(nums1[b] - nums2[b]); });
        long long remain = static_cast<long long>(k1) + static_cast<long long>(k2);
        long long ans = 0;
        for (long long i = 0; i < n; i++) {
            const auto index = indexes[i];
            const auto next_index = (n - 1 == i) ? 0 : indexes[i + 1];

            const long long cur_diff = abs(nums1[index] - nums2 [index]);
            const long long target_diff = (n - 1 == i) ? 0 : abs(nums1[next_index] - nums2[next_index]);
            const long long d0 = static_cast<long long>(cur_diff - target_diff);
            const auto box = d0 * (i + 1);
            if (box <= remain) {
                remain -= box;
            }
            else {
                const auto d1 = remain / (i + 1);
                const auto m = remain % (i + 1);
                const auto d2 = d0 - d1;
                const auto d3 = d2 - 1;
                const auto len3 = m;
                const auto len2 = (i + 1) - m;
                ans += (d3 + target_diff) * (d3 + target_diff) * len3;
                ans += (d2 + target_diff) * (d2 + target_diff) * len2;
                for (long long j = i + 1; j < n; j++) {
                    const auto diff = static_cast<long long>(nums1[indexes[j]] - nums2[indexes[j]]);
                    ans += diff * diff;
                }
                break;
            }
        }
        return ans;
    }
};


static void test(vector<int>&& nums1, vector<int>&& nums2, int k1, int k2) {
    cout << Solution().minSumSquareDiff(nums1, nums2, k1, k2) << endl;
}
int main() {
    test(get_list_int("[1,2,3,4]"), get_list_int("[2,10,20,19]"), 0, 0);
    test(get_list_int("[1,4,10,12]"), get_list_int("[5,8,6,9]"), 1, 1);
    return 0;
}
