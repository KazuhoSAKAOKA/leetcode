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
#include <bits/stdc++.h>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        vector<int> streaks(size(nums));
        int index = 0;
        while(index<size(nums)){
            int cur = index;
            int start = index;
            while (cur < size(nums) - 1 && nums[cur] < nums[cur + 1]) {
                cur++;
            }
            const auto len = cur - start + 1;
            for (int i = 0; i < len; i++) {
                streaks[start + i] = len - i;
            }
            index = cur + 1;
        }

        for (int i = 0; i < size(streaks); i++) {
            if (streaks[i] >= k) {
                if (i + k < size(streaks)) {
                    if (streaks[i + k] >= k) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().hasIncreasingSubarrays(nums, k) << endl;
}

static void run() {
    test(get_list_int("[19,1]"), 1);
    test(get_list_int("[2,5,7,8,9,2,3,4,3,1]"), 3);
    test(get_list_int("[1,2,3,4,4,4,4,5,6,7]"), 5);
}
}
namespace problem2 {
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        vector<int> streaks(size(nums));
        int index = 0;
        while (index < size(nums)) {
            int cur = index;
            int start = index;
            while (cur < size(nums) - 1 && nums[cur] < nums[cur + 1]) {
                cur++;
            }
            const auto len = cur - start + 1;
            for (int i = 0; i < len; i++) {
                streaks[start + i] = len - i;
            }
            index = cur + 1;
        }

        int max_len = 0;

        auto check = [&](int k) {
            for (int i = 0; i < size(streaks); i++) {
                if (streaks[i] >= k) {
                    if (i + k < size(streaks)) {
                        if (streaks[i + k] >= k) {
                            return true;
                        }
                    }
                }
            }
            return false;

            };

        auto binary_search = [&](int ok, int ng) {
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
            };
        
        const auto ans = binary_search(1, size(streaks));

        return ans;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().maxIncreasingSubarrays(nums) << endl;
}
static void run() {
    test(get_list_int("[2,5,7,8,9,2,3,4,3,1]"));
    test(get_list_int("[1,2,3,4,4,4,4,5,6,7]"));
}
}
namespace problem3 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    int sumOfGoodSubsequences(vector<int>& nums) {
        map<int, map<long long, long long>> work_map;
        long long current_sum = 0;
        const vector<int> offsets{ -1,1 };
        for (auto&& num : nums) {
            current_sum += static_cast<long long>(num);
            current_sum %= MODULO;
            work_map[num][num]++;
            for (auto&& offset : offsets) {
                auto it = work_map.find(num - offset);
                if (it != cend(work_map)) {
                    for (auto&& [k, freq] : it->second) {
                        auto sum1 = k + static_cast<long long>(num);
                        sum1 %= MODULO;
                        work_map[num][sum1] += freq;
                        //work_map[num][sum1] %= MODULO;
                        auto sum2 = static_cast<__int128>(sum1) * static_cast<__int128>(freq);
                        sum2 %= MODULO;
                        current_sum += static_cast<long long>(sum2);
                    }
                }
            }
        }
        return static_cast<int>(current_sum);
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().sumOfGoodSubsequences(nums) << endl;
}
static void run() {
    test(get_list_int("[3,3,4,3]"));
    test(get_list_int("[1,2,1]"));
    test(get_list_int("[3,4,5]"));
}
}
namespace problem4 {
    static void test(string&& num) {
    }
    static void run() {
    }
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}