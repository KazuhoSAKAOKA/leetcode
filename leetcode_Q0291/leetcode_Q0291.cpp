// leetcode_Q0291.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:

    static bool rec(const string& pattern, const string& s, int pattern_index, int s_index, unordered_map<char, string>& pattern_map, unordered_set<string>& exists) {
        if (pattern.size() == pattern_index) {
            if (s.size() == s_index) {
                return true;
            }
            return false;
        }

        const char c = pattern[pattern_index];
        const auto it = pattern_map.find(c);
        if (it == cend(pattern_map)) {
            const auto remain = s.size() - s_index;
            for (int i = 1; i <= remain; i++) {
                const auto current_ptn = s.substr(s_index, i);
                if (exists.count(current_ptn)) { continue; }
                pattern_map[c] = current_ptn;
                exists.insert(current_ptn);
                if (rec(pattern, s, pattern_index + 1, s_index + i, pattern_map, exists)) {
                    return true;
                }
                pattern_map.erase(c);
                exists.erase(current_ptn);
            }
            return false;
        }
        else {
            const auto& pattern_str = it->second;
            if (s.size() < s_index + pattern_str.size()) {
                return false;
            }
            auto check = [&]() {
                for (int i = 0; i < pattern_str.size(); i++) {
                    if (s[s_index + i] != pattern_str[i]) {
                        return false;
                    }
                }
                return true;
                };
            if (!check()) {
                return false;
            }
            return rec(pattern, s, pattern_index + 1, s_index + pattern_str.size(), pattern_map, exists);
        }
    }

    bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, string> pattern_map;
        unordered_set<string> exists;
        return rec(pattern, s, 0, 0, pattern_map, exists);
    }
};

void test(string&& partern, string&& s) {
    cout << Solution().wordPatternMatch(partern, s) << endl;
}
int main()
{
    test("ab", "aa");
    test("d", "e");
    test("abab", "redblueredblue");
    test("aaaa", "asdasdasdasd");
    test("aabb", "xyzabcxzyabc");
}