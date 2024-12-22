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
    int minimumOperations(vector<int>& nums) {
        map<int, int> freq_map;
        int dup_count = 0;
        for (auto&& num : nums) {
            freq_map[num]++;
            if (freq_map[num] == 2) {
                dup_count++;
            }
        }
        size_t index = 0;
        int op_count = 0;
        while (index < size(nums) && dup_count>0) {
            const auto limit = min(index + 3, size(nums));
            for (; index < limit; index++) {
                freq_map[nums[index]]--;
                if (freq_map[nums[index]] == 1) {
                    dup_count--;
                }
            }
            op_count++;
        }

        return op_count;
    }
}; 
static void test(vector<int>&& nums) {
    cout << Solution().minimumOperations(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4,2,3,3,5,7]"));
    test(get_list_int("[4,5,6,4,4]"));
    test(get_list_int("[6,7,8,9]"));
}
}
namespace problem2 {
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        map<int, int> freq_map;
        for (auto&& num : nums) {
            freq_map[num]++;
        }
        map<int, int> after_map;
        int before_value = INT_MIN;
        for (auto&& [num, count] : freq_map) {
            for (int i = 0; i < count; i++) {
                const int limit = min(max(before_value + 1, num - k), num + k);
                after_map[limit]++;
                before_value = limit;
            }
        }
        return static_cast<int>(size(after_map));
    }
}; 
static void test(vector<int>&& nums, int k) {
    cout << Solution().maxDistinctElements(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,2,2,3,3,4]"), 2);
    test(get_list_int("[4,4,4,4]"), 1);
}
}
namespace problem3 {
class Solution {
public:
    inline static void inc_to_map(map<int, int>& m, int key) {
        if (key > 1) {
            m[key]++;
        }
    }
    inline static void dec_to_map(map<int, int>& m, int key) {
        if (key > 1) {
            if (m[key] == 1) { m.erase(key); }
            else { m[key]--; }
        }
    }


    static int rec(map<int, int>& identical_length_map, int opcount) {
        if (identical_length_map.empty()) {
            return 1;
        }
        if (opcount == 0) {
            return crbegin(identical_length_map)->first;
        }
        auto it = begin(identical_length_map);
        const auto target_length = it->first;
        if (target_length == 1) {
            return 1;
        }
        int min_length = target_length;
        dec_to_map(identical_length_map, target_length);

        for (int i = 0; i < opcount; i++) {
            const auto div = target_length / (i + 2);
            inc_to_map(identical_length_map, div);
            inc_to_map(identical_length_map, target_length - div - 1);
            min_length = min(min_length, rec(identical_length_map, opcount - 1));
            dec_to_map(identical_length_map, div);
            dec_to_map(identical_length_map, target_length - div - 1);


            if (div == 1) {
                break;
            }
        }
        inc_to_map(identical_length_map, target_length);
        return min_length;
    }

    static int wa(string s, int numOps) {
        map<int, int> identical_length_map;
        char current = ' ';
        int current_streak = 0;
        for (auto&& c : s) {
            if (c == current) {
                current_streak++;
            }
            else {
                inc_to_map(identical_length_map, current_streak);
                current_streak = 1;
                current = c;
            }
        }
        inc_to_map(identical_length_map, current_streak);
        const int min_length = rec(identical_length_map, numOps);

        return min_length;
    }


    static pair<int, int> opeq(const pair<int, int>& before) {
        const auto streak = before.first + 1;
        return { streak, max(streak, before.second) };
    }
    static pair<int, int> opne(const pair<int, int>& before) {
        return { 1, before.second };
    }

    static pair<int, int> op(bool sw, const pair<int, int>& before) {
        return sw ? opeq(before) : opne(before);
    }


    int minLength(string s, int numOps) {
        const auto N = size(s);
        vector<vector<vector<pair<int, int>>>> dp(N, vector<vector<pair<int, int>>>(numOps + 1, vector<pair<int,int>>(2)));
        if (s[0] == '0') {
            dp[0][numOps][0] = { 1,1 };
            dp[0][numOps - 1][1] = { 1,1 };
        }
        else {
            dp[0][numOps][1] = { 1,1 };
            dp[0][numOps - 1][0] = { 1,1 };
        }
        for (int i = 1; i < N; i++) {
            const auto zero = s[i] == '0';
            const auto my = zero ? 0 : 1;
            if (s[i] == s[i - 1]) {
                dp[i][numOps][my] = opeq(dp[i][numOps][my]);
            }
            else {
                dp[i][numOps][my] = opne(dp[i][numOps][my == 0 ? 1 : 0]);
            }
        }


        for (int i = 1; i < N; i++) {
            const auto zero = s[i] == '0';
            if (zero) {
                dp[i][numOps][0] = op(zero, dp[i - 1][numOps][0]);
            }
            else {
                dp[i][numOps][1] = op(!zero, dp[i - 1][numOps][1]);
            }
            for (int j = 0; j < numOps; j++) {

            }
        }


    }
}; 
static void test(string&& s, int numOps) {
    cout << Solution().minLength(s, numOps) << endl;
}
static void run() {
    test("1001", 1);
    test("000001", 1);
    test("0000", 2);
    test("0101", 0);
}
}
namespace problem4 {
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