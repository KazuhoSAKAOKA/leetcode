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

    static int dc(const vector<int>& nums, int start, int len) {
        if (len < 2) { return nums[start]; }
        if (len == 2) { return min(nums[start], nums[start + 1]); }
        if (nums[start] < nums[start + len - 1]) { return nums[start]; }

        if (nums[start] == nums[start + len - 1]) {
            return min(dc(nums, start, len / 2), dc(nums, start + len / 2, len - len / 2));
        }
        else {
            const auto target = binary_search_meguru<int>(start + len - 1, start, [&](int index)->bool {
                return nums[start] > nums[index];
                });
            return nums[target];
        }
    }


    int findMin(vector<int>& nums) {
        const auto n = static_cast<int>(size(nums));
        if (n == 1) { return nums[0]; }
        if (nums[0] < nums[n - 1]) { return nums[0]; }
        return dc(nums, 0, n);
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().findMin(nums) << endl;
}
int main() {
    test(get_list_int("[10,10,1,10,10]"));
    test(get_list_int("[2,2,2,0,1]"));
    test(get_list_int("[4,5,6,7,0,1,2]"));
    test(get_list_int("[3,3,1,3]"));
    test(get_list_int("[10,1,10,10,10]"));

    test(get_list_int("[3,4,5,1,2]"));
    test(get_list_int("[11,13,15,17]"));
    return 0;
}
