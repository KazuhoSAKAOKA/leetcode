// leetcode_Q1100.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        vector<int> freqs(26);
        int repeat_count = 0;
        int count = 0;
        for (int i = 0; i < k - 1; i++) {
            freqs[s[i] - 'a']++;
            if (freqs[s[i] - 'a'] == 2) {
                repeat_count++;
            }
        }

        for (int i = k - 1; i < size(s); i++) {
            freqs[s[i] - 'a']++;
            if (freqs[s[i] - 'a'] == 2) {
                repeat_count++;
            }
            if (repeat_count == 0) {
                count++;
            }
            const int j = i - k + 1;
            freqs[s[j] - 'a']--;
            if (freqs[s[j] - 'a'] == 1) {
                repeat_count--;
            }
        }

        return count;
    }
};

void test(string&& s, int k) {
    cout << Solution().numKLenSubstrNoRepeats(s, k) << endl;
}

int main()
{
    test("havefunonleetcode", 5);
    test("home", 5);
    return 0;
}