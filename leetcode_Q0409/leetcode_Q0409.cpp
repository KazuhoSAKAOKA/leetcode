// leetcode_Q0409.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:

    int longestPalindrome(string s) {
        map<char, int> freq_map;
        for (auto&& c : s) {
            freq_map[c]++;
        }
        int result = 0;
        bool exist_one = false;
        for (auto&& [k, v] : freq_map) {
            if (v % 2 == 1) {
                exist_one = true;
            }
            result += (v / 2) * 2;
        }
        if (exist_one) {
            result++;
        }
        return result;
    }
};

void test(string&& s) {
    cout << Solution().longestPalindrome(s) << endl;
}
int main()
{
    test("aacd");
    test("abccccdd");
    test("a");
}