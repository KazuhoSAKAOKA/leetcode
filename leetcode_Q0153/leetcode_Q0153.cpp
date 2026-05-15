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
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
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

    int findMin(vector<int>& nums) {
        const auto n = static_cast<int>(size(nums));
        if (n == 1) { return nums[0]; }
        if (nums[0] < nums[n - 1]) { return nums[0]; }
        auto target = binary_search_meguru<int>(n - 1, 0, [&](int index)->bool {
            return nums[0] > nums[index];
            });

        return nums[target];
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().findMin(nums) << endl;
}
int main() {
    test(get_list_int("[3,4,5,1,2]"));
    test(get_list_int("[4,5,6,7,0,1,2]"));
    test(get_list_int("[11,13,15,17]"));
    return 0;
}
