// leetcode_Q1358.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        int l = 0;
        vector<int> freqs(3);
        int count = 0;
        for (int r = 0; r < size(s); r++) {
            freqs[s[r] - 'a']++;

            while (l < r && freqs[s[l] - 'a'] > 1) {
                freqs[s[l] - 'a']--;
                l++;
            }
            if (freqs[0] > 0 && freqs[1] > 0 && freqs[2] > 0) {
                count += l + 1;
            }
        }
        return count;
    }
};

void test(string&& s) {
    cout << Solution().numberOfSubstrings(s) << endl;
}
int main()
{
    test("abcabc");
    test("aaacb");
    test("abc");
    return 0;
}