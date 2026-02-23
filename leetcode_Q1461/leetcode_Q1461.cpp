// leetcode_Q1461.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        const int n = size(s);
        const int m = 1 << k;
        const int mask = m - 1;
        int count = 0;
        vector<bool> exists(m);
        int cur_value = 0;
        for (int i = 0; i < min(n, k - 1); i++) {
            cur_value = cur_value << 1;
            if (s[i] == '1') {
                cur_value |= 1;
            }
        }
        for (int i = k - 1; i < n; i++) {
            cur_value = cur_value << 1;
            if (s[i] == '1') {
                cur_value |= 1;
            }
            cur_value &= mask;
            if (!exists[cur_value]) {
                count++;
                exists[cur_value] = true;
            }
        }
        return count == m;
    }
};

static void test(string&& s, int k) {
    cout << Solution().hasAllCodes(s, k) << endl;
}

int main()
{
    test("00110110", 2);
    test("0110", 1);
    test("0110", 2);
    return 0;
}