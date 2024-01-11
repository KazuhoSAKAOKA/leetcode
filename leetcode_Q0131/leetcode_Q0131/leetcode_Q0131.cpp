// leetcode_Q0131.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:

    static bool is_palindrome(const string& s) {
        if (s.size() == 1) { return true; }
        const auto half = s.size() / 2;
        for (auto i = 0; i < half; i++) {
            if (s[i] != s[s.size() - 1 - i]) { return false; }
        }
        return true;
    }

    static void rec(const string& s, int index, vector<string>& substrings, vector<vector<string>>& ans) {
        if (s.size() == index) {
            if (all_of(cbegin(substrings), cend(substrings), is_palindrome)) {
                ans.emplace_back(substrings);
            }
            return;
        }

        for (int i = 1; (i + index) <= s.size(); i++) {
            substrings.emplace_back(s.substr(index, i));
            rec(s, index + i, substrings, ans);
            substrings.pop_back();
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> substrings;
        rec(s, 0, substrings, ans);
        return ans;
    }
};

void test(string&& s) {
    const auto ans = Solution().partition(s);
    for (auto&& sublist : ans) {
        for (auto&& part : sublist) {
            cout << part << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    test("aab");
    test("a");
    test("abcdefghijklmnop");
}