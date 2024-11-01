// leetcode_Q1957.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string makeFancyString(string s) {
        string ans;
        ans.reserve(size(s));
        ans += s[0];
        int streak = 0;
        for (int i = 1; i < size(s); i++) {
            if (s[i] != ans.back()) {
                ans += s[i];
                streak = 0;
            }
            else {
                if (streak < 1) {
                    ans += s[i];
                    streak++;
                }
            }
        }

        return ans;
    }
};

void test(string&& s) {
    cout << Solution().makeFancyString(s) << endl;
}

int main()
{
    test("leeetcode");
    test("aaabaaaa");
    test("aab");
    return 0;
}