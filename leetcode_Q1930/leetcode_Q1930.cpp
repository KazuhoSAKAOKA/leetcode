// leetcode_Q1930.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        const auto N = size(s);
        if (N < 3) {
            return 0;
        }

        vector<vector<bool>> counts(26, vector<bool>(26, false));
        vector<int> right_freqs(26);

        for (auto&& c : s) {
            right_freqs[c - 'a']++;
        }

        vector<int> left_freqs(26);
        left_freqs[s[0] - 'a']++;
        right_freqs[s[0] - 'a']--;

        for (int i = 1; i < N - 1; i++) {
            const auto index = static_cast<int>(s[i] - 'a');
            right_freqs[index]--;

            for (int j = 0; j < 26; j++) {
                if (left_freqs[j] > 0 && right_freqs[j] > 0) {
                    counts[index][j] = true;
                }
            }
            left_freqs[index]++;
        }

        int count = 0;

        for (auto&& list : counts) {
            count += count_if(cbegin(list), cend(list), [](bool b) {return b; });
        }

        return count;
    }
};

void test(string&& s) {
    cout << Solution().countPalindromicSubsequence(s) << endl;
}

int main()
{
    test("aabca");
    test("adc");
    test("bbcbaba");
    return 0;
}