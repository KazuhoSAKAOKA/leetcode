// leetcode_Q1400.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canConstruct(string s, int k) {
        vector<int> freqs(26);
        for (auto&& c : s) {
            freqs[c - 'a']++;
        }
        int single_count = 0;
        int pair_count = 0;
        for (int i = 0; i < 26; i++) {
            if (freqs[i] % 2 == 1) {
                pair_count += (freqs[i] - 1) / 2;
                single_count++;
            }
            else {
                pair_count += freqs[i] / 2;
            }
        }

        if (single_count > k) {
            return false;
        }

        const auto single_remains = k - single_count;
        if (single_remains > 0) {
            if (single_remains > pair_count) {
                if (single_remains > pair_count * 2) {
                    return false;
                }
            }
        }
        return true;
    }
};

void test(string&& s, int k) {
    cout << Solution().canConstruct(s, k) << endl;
}

int main()
{
    test("annabelle", 2);
    test("leetcode", 3);
    test("true", 4);
    return 0;
}