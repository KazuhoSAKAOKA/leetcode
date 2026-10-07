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

    static bool check(const string& s, int bitmask) {
        string work;
        for (size_t i = 0; i < size(s); i++) {
            if (bitmask & (1 << i)) {
                if (s[i] == '(') {
                    work.push_back('(');
                }
                else if (s[i] == ')') {
                    if (work.empty()) { return false; }
                    work.pop_back();
                }
            }
        }
        return work.empty();
    }


    static vector<string> tle(string s) {
        const int mask = 1 << size(s);

        int max_len = 0;
        vector<int> vals{ 0 };
        for (size_t bit = 1; bit < mask; bit++) {
            if (check(s, bit)) {
                const auto pc = std::popcount(bit);
                if (max_len < pc) {
                    max_len = pc;
                    vals.clear();
                    vals.push_back(bit);
                }
                else if (max_len == pc) {
                    vals.push_back(bit);
                }
            }
        }
        set<string> strs;
        for (auto&& v : vals) {
            string temp;
            for (size_t i = 0; i < size(s); i++) {
                if (v & (1 << i)) {
                    temp.push_back(s[i]);
                }
            }
            strs.insert(temp);
        }


        return vector<string>(cbegin(strs), cend(strs));
    }
    static void rec(const string& s, size_t index, string& work, size_t open_brackets, size_t& max_len, set<string>& vals) {
        if (index == size(s)) {
            if (open_brackets == 0) {
                if (max_len < size(work)) {
                    vals.clear();
                    vals.insert(work);
                    max_len = size(work);
                }
                else if (max_len == size(work)) {
                    vals.insert(work);
                }
            }
            return;
        }

        if (s[index] == '(') {
            rec(s, index + 1, work, open_brackets, max_len, vals);
            work += '(';
            rec(s, index + 1, work, open_brackets + 1, max_len, vals);
            work.pop_back();
        }
        else if (s[index] == ')') {
            rec(s, index + 1, work, open_brackets, max_len, vals);
            if (open_brackets > 0) {
                work += ')';
                rec(s, index + 1, work, open_brackets - 1, max_len, vals);
                work.pop_back();
            }
        }
        else {
            work += s[index];
            rec(s, index + 1, work, open_brackets, max_len, vals);
            work.pop_back();
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        size_t max_len = 0;
        set<string> vals{ "" };
        size_t cur_len = 0;
        string work;
        rec(s, 0, work, 0, max_len, vals);
        return vector<string>(cbegin(vals), cend(vals));
    }
};

static void test(string&& s) {
    output(Solution().removeInvalidParentheses(s));
}

int main() {
    test("n");
    test("()())()");
    test("(a)())()");
    test(")(");
    return 0;
}
