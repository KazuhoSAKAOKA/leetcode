// leetcode_Q0010.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*

    bool is_match_prev(char s_char, const string& p, int p_index) {
        if (p_index < 0) { return false; }
        if (p[p_index] == '*') { return is_match_prev(s_char, p, p_index - 1); }
        if (p[p_index] == '.') { return true; }
        return s_char == p[p_index];
    }

    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= p.size(); i++) {
            dp[0][i] = dp[0][i - 1] && (p[i - 1] == '*');
        }

        for (int j = 1; j <= s.size(); j++) {
            for (int i = 1; i <= p.size(); i++) {
                if (s[j - 1] == p[i - 1] || p[i - 1] == '.') {
                    dp[j][i] = dp[j - 1][i - 1];
                }
                else if (p[i - 1] == '*') {
                    dp[j][i] = dp[j][i - 1] || (dp[j - 1][i - 1] && is_match_prev(s[j - 1], p, i - 2));
                }
                else {
                    dp[j][i] = false;
                }
            }
        }
        return dp[s.size()][p.size()];
    }
    */

    pair<int, bool> get_astarisk_block(const string& p, int p_index) {
        bool exist = false;
        int len = 1;
        for (int i = p_index + 1; i < p.size(); i++) {
            if (p[i] != '*') {
                break;
            }
            exist = true;
            len++;
        }
        return make_pair(len, exist);
    }
    
    pair<int, bool> match_astarisk_block(const string& s, const string& p, int s_index, int p_index) {
        const int remain_size = static_cast<int>(s.size()) - s_index;
        const char p_char = p[p_index];
        if (p_char == '.') {
            return make_pair(remain_size, true);
        }
        for (int i = 0; i < remain_size; i++) {
            if(s[s_index+i] != p_char){
                return make_pair(i, i > 0);
            }
        }
        return make_pair(remain_size, true);
    }

    bool is_match_rec(const string& s, const string& p, int s_index, int p_index) {
        if (s.size() == s_index && p.size() == p_index) {
            return true;
        }
        if (s.size() == s_index) {
            const auto [tail_len, tail_astarisk] = get_astarisk_block(p, p_index);
            if (!tail_astarisk) { return false; }
            return is_match_rec(s, p, s_index, p_index + tail_len);
        }
        if (p.size() == p_index) {
            return false;
        }
        const auto [astarisk_group_len, is_astarisk] = get_astarisk_block(p, p_index);

        if (is_astarisk) {
            const auto [max_size, matched] = match_astarisk_block(s, p, s_index, p_index);
            if (matched) {
                for (int i = 1; i <= max_size; i++) {
                    if (is_match_rec(s, p, s_index + i, p_index + astarisk_group_len)) {
                        return true;
                    }
                }
            }
            return is_match_rec(s, p, s_index, p_index + astarisk_group_len);
        }
        if (s[s_index] == p[p_index] || p[p_index] == '.') {
            return is_match_rec(s, p, s_index + 1, p_index + 1);
        }
        return false;
    }

    bool isMatch(string s, string p) {
        return is_match_rec(s, p, 0, 0);
    }

};



void test(const string& s, const string& p) {
    cout << "s:" << s << "/p:" << p<< ":ans:" << Solution().isMatch(s, p) << endl;
}


int main()
{
    test("a", "ab*");
    test("a", "ab*b*b*b*");

    test("aaa", ".*");
    test("aaa", "ab*a*c*a");
    test("aab", "c*a*b");
    test("aa", "a");
    test("aa", "a*");
    test("ab", ".*");
    test("ab", "a*b*");

    //test("ab", "****ab");
    //test("ab", "ab***");
    //test("ab", "a***b");

}