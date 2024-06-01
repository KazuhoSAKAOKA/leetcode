// leetcode_Q3110.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Solution {
public:
    int scoreOfString(string s) {
        int result = 0;
        for (int i = 1; i < s.size(); i++) {
            result += abs(static_cast<int>(s[i - 1]) - static_cast<int>(s[i]));
        }
        return result;
    }
};

void test(string&& s) {
    cout << Solution().scoreOfString(s) << endl;
}
int main()
{
    test("hello");
    test("zaz");
}