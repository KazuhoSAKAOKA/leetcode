// leetcode_Q2743.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfSpecialSubstrings(string s) {
        vector<int> freq_counts('z' - 'a' + 1, 0);
        int count = 0;

        auto conv = [](char c) {return static_cast<int>(c - 'a');};
        int l = 0;
        for (int r = 0; r < s.size(); r++) {
            const int c = conv(s[r]);
            freq_counts[c]++;

            while (l < r && freq_counts[c] > 1) {
                const int c1 = conv(s[l]);
                freq_counts[c1]--;
                l++;
            }
            count += r - l + 1;
        }

        return count;
    }
};

void test(string&& s) {
    cout << Solution().numberOfSpecialSubstrings(s) << endl;
}
int main()
{
    test("a");
    test("abcd");
    test("ooo");
    test("abab");
}