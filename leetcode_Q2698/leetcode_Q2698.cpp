// leetcode_Q2698.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:

    static bool check(const string& sq_str, int value, int offset) {
        if (size(sq_str) <= offset) {
            return value == 0;
        }
        for (int len = 1; len <= size(sq_str) - offset; len++) {
            const auto cur_num = sq_str.substr(offset, len);
            const auto cur_value = stoi(cur_num);
            if (cur_value <= value) {
                if (check(sq_str, value - cur_value, offset + len)) {
                    return true;
                }
            }
        }
        return false;
    }
    static bool check(int value) {
        const auto sq = value * value;
        const auto sq_str = to_string(sq);
        return check(sq_str, value, 0);
    }

    int punishmentNumber(int n) {
        int total = 0;
        for (int i = 1; i <= n; i++) {
            if (check(i)) {
                total += i * i;
            }
        }
        return total;
    }
};

void test(int n) {
    cout << Solution().punishmentNumber(n) << endl;
}

int main()
{
    test(10);
    test(37);
    test(1000);
    return 0;
}