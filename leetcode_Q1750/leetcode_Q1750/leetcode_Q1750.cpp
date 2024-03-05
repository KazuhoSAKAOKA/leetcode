// leetcode_Q1750.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    int minimumLength(string s) {
        int l = 0;
        int r = s.size() - 1;

        while (l < r) {
            if (s[l] == s[r]) {
                int linc = 1;
                while (l + linc < s.size() && s[l] == s[l + linc]) {
                    linc++;
                }
                int rdec = -1;
                while (r + rdec >= 0 && s[r] == s[r + rdec]) {
                    rdec--;
                }
                l += linc;
                r += rdec;
            }
            else {
                return r - l + 1;
            }
        }
        if (r == l) { return 1; }
        return 0;
    }
};


void test(string&& s) {
    cout << Solution().minimumLength(s) << endl;
}

int main()
{
    test("aaaba");
    test("ca");
    test("cabaabac");
    test("aabccabba");
}