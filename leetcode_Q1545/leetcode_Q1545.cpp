// leetcode_Q1545.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:

    static string rev_invert(const string& s) {
        string ret;
        ret.reserve(size(s));
        for (auto it = crbegin(s); it != crend(s); ++it) {
            ret += *it == '0' ? '1' : '0';
        }
        return ret;
    }

    char findKthBit(int n, int k) {
        string s = "0";
        for (int i = 0; i < n; i++) {
            s = s + "1" + rev_invert(s);
        }

        return s[k - 1];
    }
};

void test(int n, int k) {
    cout << Solution().findKthBit(n, k) << endl;
}


int main()
{
    test(3, 1);
    test(4, 11);
    return 0;
}