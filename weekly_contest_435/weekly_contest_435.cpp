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
    int maxDifference(string s) {
        vector<int> freqs(26);
        for (auto&& c : s) {
            freqs[c - 'a']++;
        }
        int max_even = 0;
        int min_even = INT_MAX;
        int max_odd = 0;
        int min_odd = INT_MAX;
        for (auto&& freq : freqs) {
            if (freq != 0) {
                if (freq % 2 == 0) {
                    max_even = max(max_even, freq);
                    min_even = min(min_even, freq);
                }
                else {
                    max_odd = max(max_odd, freq);
                    min_odd = min(min_odd, freq);
                }
            }
        }

        const auto d1 = max_odd - min_even;
        const auto d2 = min_odd - max_even;
        if (d1 < d2) {
            return d2;
        }
        else {
            return d1;
        }
    }
}; 

void test(string&& s) {
    cout << Solution().maxDifference(s) << endl;
}
static void run() {
    test("mmsmsym");
    test("aaaaabbc");
    test("abcabcab");
}
}
namespace problem2 {
class Solution {
public:
    static inline int get_manhattan(const pair<int, int>& p) {
        return abs(p.first) + abs(p.second);
    }

    int maxDistance(string s, int k) {
        map<char, pair<int, int>> dirmap{
            {'N', {1,0}},
            {'S', {-1,0}},
            {'E', {0,1}},
            {'W', {0,-1}},
        };

        int max_dist = 0;
        pair<int, int> current{ 0,0 };
        int y_plus_count = 0;
        int y_minus_count = 0;
        int x_plus_count = 0;
        int x_minus_count = 0;
        for (auto&& c : s) {
            const auto& [dy, dx] = dirmap[c];
            if (dy != 0) {
                if (dy > 0) {
                    y_plus_count++;
                }
                else {
                    y_minus_count++;
                }
            }
            if (dx != 0) {
                if (dx > 0) {
                    x_plus_count++;
                }
                else {
                    x_minus_count++;
                }

            }

            const pair<int, int> next{ current.first + dy, current.second + dx };
            const auto cur_dist = get_manhattan(next);
            max_dist = max(max_dist, cur_dist);
            const auto allow_diff = min(k, min(y_plus_count, y_minus_count) + min(x_plus_count, x_minus_count));
            max_dist = max(max_dist, cur_dist + allow_diff * 2);
            current = next;
        }

        return max_dist;
    }
};
void test(string&& s, int k) {
    cout << Solution().maxDistance(s, k) << endl;
}


static void run() {
    test("NWSE", 1);
    test("SE", 0);
    test("NSWWEW", 3);
}
}
namespace problem3 {
class Solution {
public:

    template <typename T>
    static T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

    template <typename T>
    static T lcm(const T& a, const T& b) {
        return a / gcd(a, b) * b;
    }

    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        vector<vector<int>> ops(size(nums), vector<int>(size(target)));
        vector<pair<int, int>> min_ops_target(size(target), { INT_MAX, -1 });
        for (int i = 0; i < size(nums); i++) {
            for (int j = 0; j < size(target); j++) {
                const auto m = nums[i] % target[j];
                ops[i][j] = (target[j] - m) % target[j];
                if (ops[i][j] < min_ops_target[j].first) {
                    min_ops_target[j] = { ops[i][j], i };
                }
            }
        }
        int pts = 0;
        for (auto&& [o, _] : min_ops_target) {
            pts += o;
        }
        return pts;
    }
};
void test(vector<int>&& nums, vector<int>&& target) {
    cout << Solution().minimumIncrements(nums, target) << endl;
}

static void run() {
    test(get_list_int("[4,2,8,10]"), get_list_int("[8,8,10,8]"));
    test(get_list_int("[8,4]"), get_list_int("[10,5]"));
    test(get_list_int("[1,2,3]"), get_list_int("[4]"));
    test(get_list_int("[7,9,10]"), get_list_int("[7]"));
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