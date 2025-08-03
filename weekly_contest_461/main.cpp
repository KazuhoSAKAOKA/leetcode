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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {

class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        const auto n = size(nums);

        auto check = [&](int p, int q)->bool {
            if (p == 0 || (q - p) == 0 || q == n - 1) {
                return false;
            }
            for (int k = 0; k < p; k++) {
                if (nums[k] >= nums[k + 1]) {
                    return false;
                }
            }
            for (int k = p; k < q; k++) {
                if (nums[k] <= nums[k + 1]) {
                    return false;
                }
            }
            for (int k = q; k < n - 1; k++) {
                if (nums[k] >= nums[k + 1]) {
                    return false;
                }
            }
            return true;
            };


        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (check(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
}; 
static void test(vector<int>&& nums) {
    cout << Solution().isTrionic(nums) << endl;
}
static void run() {
    test(get_list_int("[1,3,5,4,2,6]"));
    test(get_list_int("[2,1,3]"));
    test(get_list_int("[5,9,1,7]"));
}
}
namespace problem2 {
class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int count = 0;
        const auto n = size(weight);
        int cur_max = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (cur_max > weight[i]) {
                count++;
                cur_max = INT_MIN;
            }
            else {
                cur_max = max(cur_max, weight[i]);
            }
        }
        return count;
    }
}; 
static void test(vector<int>&& weight) {
    cout << Solution().maxBalancedShipments(weight) << endl;
}
static void run() {
    test(get_list_int("[2,5,1,4,3]"));
    test(get_list_int("[4,4]"));
}
}
namespace problem3 {
class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        const long long n = static_cast<long long>(size(s));
        const long long total = n * (n + 1) / 2;
        if (total < k) { return -1; }
        auto get_calc = [](long long leftlen, long long rightlen)->long long {
            return (leftlen + 1) * (rightlen + 1);
            };

        long long current_count = 0;
        set<int> asts;
        for (int i = 0; i < n; i++) {
            const auto target = order[i];
            long long leftlen;
            long long rightlen;

            auto upp_it = asts.upper_bound(target);
            if (upp_it == cend(asts)) {
                rightlen = n - target - 1;
            }
            else {
                rightlen = *upp_it - target - 1;
            }
            if (upp_it == cbegin(asts)) {
                leftlen = target;
            }
            else {
                auto prev_it = prev(upp_it);
                leftlen = target - *prev_it - 1;
            }

            current_count += get_calc(leftlen, rightlen);
            if (k <= current_count) {
                return i;
            }
            asts.insert(target);
        }
        return -1;
    }
};
void test(string&& s, vector<int>&& order, int k) {
    cout << Solution().minTime(s, order, k) << endl;
}
static void run() {
    test("cat", get_list_int("[0,2,1]"), 6);
    test("abc", get_list_int("[1,0,2]"), 2);
    test("xy", get_list_int("[0,1]"), 4);
}
}
namespace problem4 {
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        enum class state_e {
            none,
            increase1,
            decrease,
            increase2,
        };

        long long max_sum = LLONG_MIN;
        const auto n = size(nums);
        state_e cur_state = state_e::none;
        int next_begin = -1;
        long long cur_sum = 0LL;
        long long cur_climb = 0LL;

        for (int i = 0; i < n - 1; i++) {
            if (cur_state == state_e::none) {
                if (nums[i] < nums[i + 1]) {
                    cur_state = state_e::increase1;
                    cur_sum = nums[i];
                }
            }
            else if(cur_state == state_e::increase1){
                if (nums[i] < nums[i + 1]) {
                    cur_sum += nums[i];
                    if (nums[i - 1] < 0) {
                        cur_sum -= nums[i - 1];
                    }
                }
                else if (nums[i] > nums[i + 1]) {
                    cur_state = state_e::decrease;
                    cur_sum += nums[i];
                }
                else {
                    cur_state = state_e::none;
                    cur_sum = 0LL;
                }
            }
            else if (cur_state == state_e::decrease) {
                if (nums[i] > nums[i + 1]) {
                    cur_sum += nums[i];
                }
                else if (nums[i] < nums[i + 1]) {
                    cur_state = state_e::increase2;
                    cur_sum += nums[i];
                    max_sum = max(max_sum, cur_sum + nums[i + 1]);
                    cur_climb = nums[i];
                }
                else {
                    cur_state = state_e::none;
                    cur_sum = 0LL;
                }
            }
            else if (cur_state == state_e::increase2) {
                if (nums[i] < nums[i + 1]) {
                    cur_sum += nums[i];
                    max_sum = max(max_sum, cur_sum);
                    cur_climb += nums[i];
                    if (nums[i - 1] < 0) {
                        cur_climb -= nums[i - 1];
                    }
                }
                else if (nums[i] > nums[i + 1]) {
                    cur_sum += nums[i];
                    cur_climb += nums[i];
                    max_sum = max(max_sum, cur_sum);
                    cur_sum = cur_climb;
                    cur_state = state_e::decrease;
                }
                else {
                    max_sum = max(max_sum, cur_sum);
                    cur_state = state_e::none;
                    cur_sum = 0;
                }
            }
        }

        if (cur_state == state_e::increase2) {
            cur_sum += nums[n - 1];
            max_sum = max(max_sum, cur_sum);
        }

        return max_sum;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().maxSumTrionic(nums) << endl;
}
static void run() {
    test(get_list_int("[-754,167,-172,202,735,-941,992]"));
    test(get_list_int("[467,941,-696,-288]"));
    test(get_list_int("[2,993,-791,-635,-569]"));
    test(get_list_int("[1,4,2,7]"));
    test(get_list_int("[0,-2,-1,-3,0,2,-1]"));
}
}
int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}