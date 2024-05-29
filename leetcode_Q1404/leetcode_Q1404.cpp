// leetcode_Q1404.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int numSteps(string s) {
        int result = 0;

        bool carry = false;
        for (int i = static_cast<int>(s.size()) - 1; i >= 1; i--) {
            if (s[i] == '0') {
                if (!carry) {
                    result++;
                }
                else {
                    carry = true;
                    result += 2;
                }
            }
            else {
                if (!carry) {
                    carry = true;
                    result += 2;
                }
                else {
                    result++;
                }
            }
        }
        if (carry) {
            result++;
        }


        return result;
    }
};

void test(string&& s) {
    cout << Solution().numSteps(s) << endl;
}
int main()
{
    test("1000");
    test("1001");
    test("10101");
    test("1101");
    test("10");
    test("1");
}