// leetcode_Q2864.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:


    string maximumOddBinaryNumber(string s) {
        const int numOf1 = accumulate(cbegin(s), cend(s), 0, [](const auto& b, const auto& v) { return b + (v == '1' ? 1 : 0); });
        if (numOf1 == 0) {
            return s;
        }
        string ans(s.size(), '0');
        ans[s.size() - 1] = '1';
        for (int i = 0; i < numOf1 - 1; i++) {
            ans[i] = '1';
        }

        return ans;
    }
};

void test(string&& s) {
    cout << Solution().maximumOddBinaryNumber(s) << endl;
}

int main()
{
    test("010");
    test("0101");
}