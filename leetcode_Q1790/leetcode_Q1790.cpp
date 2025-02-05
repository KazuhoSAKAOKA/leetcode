// leetcode_Q1790.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        bool modified = false;
        int candidate_index = -1;
        for (int i = 0; i < size(s1); i++) {
            if (s1[i] != s2[i]) {
                if (modified) {
                    return false;
                }
                if (candidate_index < 0) {
                    candidate_index = i;
                }
                else {
                    if (s1[i] == s2[candidate_index] && s1[candidate_index] == s2[i]) {
                        modified = true;
                    }
                    else {
                        return false;
                    }
                }
            }
        }
        return candidate_index < 0 || modified;
    }
};

void test(string&& s1, string&& s2) {
    cout << Solution().areAlmostEqual(s1, s2) << endl;
}
int main()
{
    test("aa", "ac");
    return 0;
}