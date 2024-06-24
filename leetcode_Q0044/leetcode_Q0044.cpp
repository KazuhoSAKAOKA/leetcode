// leetcode_Q0044.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Solution {
public:
    using memo_key_t = pair<int, int>;
    using memo_t = map<memo_key_t, bool>;

    static bool rec(const string& s, const string& p, int s_index, int p_index, memo_t& memo) {
        if (s.size() == s_index && p.size() == p_index) {
            return true;
        }
        if (p.size() == p_index) {
            return false;
        }

        const auto key = memo_key_t(s_index, p_index);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        if (p[p_index] == '*') {
            for (int i = s_index; i <= s.size(); i++) {
                if (rec(s, p, i, p_index + 1, memo)) {
                    memo[key] = true;
                    return true;
                }
            }
            memo[key] = false;
            return false;
        }
        if (p[p_index] != '?') {
            if (s[s_index] != p[p_index]) {
                memo[key] = false;
                return false;
            }
        }
        const auto r = rec(s, p, s_index + 1, p_index + 1, memo);
        memo[key] = r;
        return r;
    }

    bool isMatch(string s, string p) {
        memo_t memo;
        return rec(s, p, 0, 0, memo);
    }
};

void test(string&& s, string&& p) {
    cout << (Solution().isMatch(s, p) ? "true" : "false") << endl;
}

int main()
{
    test("bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", "b*b*ab**ba*b**b***bba");
    test("aa", "*****");
    test("aa", "a");
    test("aa", "*");
    test("cb", "?a");
}