// leetcode_Q3223.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        vector<int> freqs(26);
        for (auto&& c : s) {
            freqs[c - 'a']++;
        }

        int count = 0;
        for (auto&& freq : freqs) {
            if (freq <= 2) {
                count += freq;
            }
            else {
                if (freq % 2 == 1) {
                    count += 1;
                }
                else {
                    count += 2;
                }
            }
        }
        return count;
    }
};

void test(string&& s) {
    cout << Solution().minimumLength(s) << endl;
}



int main()
{
    test("abaacbcbb");
    test("aa");
    return 0;
}