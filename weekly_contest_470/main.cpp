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
    int alternatingSum(vector<int>& nums) {
        int total = 0;
        for (int i = 0; i < size(nums); i++) {
            if (i % 2 == 0) {
                total += nums[i];
            }
            else {
                total -= nums[i];
            }
        }
        return total;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().alternatingSum(nums) << endl;
}
static void run() {
    test(get_list_int("[1,3,5,7]"));
    test(get_list_int("[100]"));
}
}
namespace problem2 {
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int bitwisexor = accumulate(cbegin(nums), cend(nums), 0, [](int a, int b) { return a ^ b; });
        if (bitwisexor != 0) {
            return static_cast<int>(size(nums));
        }
        if (any_of(cbegin(nums), cend(nums), [](int a) { return a != 0; })) {
            return static_cast<int>(size(nums)) - 1;
        }
        return 0;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().longestSubsequence(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"));
    test(get_list_int("[2,3,4]"));
}
}
namespace problem3 {
class Solution {
public:
    /*        vector<char> stst;
        string ans;
        stack<string> ans_st;
        for (int i = 0; i < size(s); i++) {
            if (s[i] == '(') {
                stst.push_back('(');
            }
            else {
                if (stst.empty()) {
                    ans += ')';
                }
                else {
                    ans_st.push("()");
                    stst.pop_back();
                    if (size(ans_st) == k) {
                        stack<string> du;
                        swap(ans_st, du);
                    }
                }
            }
        }
        for(int i=0; i< size(stst);i++) {
            ans += stst[i];
        }
        return ans;*/
    /*struct retitem {
        char pair_char;
        int pair_count;
        stack<retitem> after;
    };
    static retitem rec(const string& s, int k, int index) {
        if (size(s) == index) {
            return retitem{ 0, 0,{} };
        }
        auto aft = rec(s, k, index + 1);
        if (s[index] == '(') {
            if (aft.pair_char == ')') {
                auto next = aft.after.top();
                if (next.pair_count + 1 == k) {
                    aft.after.pop();
                    return retitem{
                        next.pair_char,
                        0,
                        aft.after,
                    };
                }
                else {
                    aft.after.pop();
                    return retitem{
                        next.pair_char,
                        next.pair_count + 1,
                        aft.after,
                    };
                }
            }
            else {

            }
            if (aft.after.empty() || aft.after[0] !=')') {
                string work;
                work.append(aft.pair_count, '(');
                work.append(aft.pair_count, ')');
                return retitem{
                    "(" + work + aft.after,
                    0,
                };
            }
            else {
                const auto pcount = aft.pair_count + 1;
                if (pcount < k) {
                    return retitem{
                        aft.after.substr(1),
                        aft.pair_count + 1,
                    };
                }
                else {
                    return retitem{
                        aft.after.substr(1),
                        0,
                    };
                }
            }
        }
        else {
            return retitem{
                ')',
                aft.pair_count,
                aft.after,
            };
        }
    }*/
    string removeSubstring(string s, int k) {
        struct info {
            char c;
            int streak;
        };
        vector<info> st;
        info cur_info{
            s[0], 1
        };
        for (int i = 1; i < size(s); i++) {
            if (cur_info.c != s[i]) {
                if (cur_info.streak > 0) {
                    st.push_back(cur_info);
                }
                cur_info.c = s[i];
                cur_info.streak = 1;
                while (!st.empty() && st.back().c == cur_info.c) {
                    cur_info.streak += st.back().streak;
                    st.pop_back();
                }
            }
            else {
                cur_info.streak++;
            }
            if (cur_info.c == ')' && !st.empty() && st.back().c == '(' && cur_info.streak >= k && st.back().streak >= k) {
                cur_info.streak -= k;
                st.back().streak -= k;
                if (st.back().streak == 0) {
                    st.pop_back();

                    while (!st.empty() && st.back().c == cur_info.c) {
                        cur_info.streak += st.back().streak;
                        st.pop_back();
                    }
                }
            }
        }
        string ans;
        for (int i = 0; i < size(st); i++) {
            ans.append(st[i].streak, st[i].c);
        }
        ans.append(cur_info.streak, cur_info.c);
        return ans;
    }
};
static void test(string&& s, int k) {
    cout << Solution().removeSubstring(s, k) << endl;
}
static void run() {
    test("(((())())(", 2);
    test("))(()()))", 1);
    test("((()))()()()", 3);
    test("(())", 1);
    test("(()(", 1);
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