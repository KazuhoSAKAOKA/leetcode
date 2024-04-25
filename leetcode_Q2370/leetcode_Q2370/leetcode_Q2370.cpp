// leetcode_Q2370.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Solution {
public:
    int longestIdealString(string s, int k) {
        vector<int> before(26, 0);
        for (int i = 0; i < s.size(); i++) {
            vector<int> current(before);
            int max_length = 0;
            const auto base = static_cast<int>(s[i] - 'a');
            for (int j = max(0, base - k); j <= min(25, base + k); j++) {
                max_length = max(max_length, before[j]);
            }
            current[base] = max_length + 1;
            before = current;
        }
        
        return *max_element(cbegin(before), cend(before));
    }
};

void test(string&& s, int k) {
    cout << Solution().longestIdealString(s, k) << endl;
}

int main()
{
    test("a", 0);
    test("abcdefghijklmnopqrstuvwxyz", 0);

    test("abcdefghijklmnopqrstuvwxyz", 1);
    test("acfgbd", 2);
    test("abcd", 3);
}