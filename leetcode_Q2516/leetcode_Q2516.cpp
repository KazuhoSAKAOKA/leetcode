// leetcode_Q2516.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int takeCharacters(string s, int k) {
        vector<int> freqs(3, 0);
        for (auto&& c : s) {
            freqs[c - 'a']++;
        }
        const int limita = freqs[0] - k;
        const int limitb = freqs[1] - k;
        const int limitc = freqs[2] - k;
        if (limita < 0 || limitb < 0 || limitc < 0) {
            return -1;
        }
        if (k == 0) {
            return 0;
        }
        int min_takes = size(s);
        vector<int> current_state(3, 0);
        int l = 0;
        for (int r = 0; r < size(s); r++) {
            current_state[s[r] - 'a']++;
            while (l < r && (limita < current_state[0] || limitb < current_state[1] || limitc < current_state[2])) {
                current_state[s[l] - 'a']--;
                l++;
            }
            if (current_state[0] <= limita && current_state[1] <= limitb && current_state[2]<= limitc) {
                min_takes = min(min_takes, static_cast<int>(size(s) - (r - l + 1)));
            }
        }
        return min_takes;
    }
};

void test(string&& s, int k) {
    cout << Solution().takeCharacters(s, k) << endl;
}
int main()
{
    test("aabaaaacaabc", 2);
    test("a", 1);
    return 0;
}