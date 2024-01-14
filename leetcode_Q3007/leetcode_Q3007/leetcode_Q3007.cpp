// leetcode_Q3007.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class Solution {
public:

    static unsigned long long sum_bits(long long value, int bit) {
        const unsigned long long bitflg = (1LL) << bit;
        const unsigned long long full = (1LL) << (bit + 1);

        const unsigned long long p = value / full;
        const unsigned long long remain = value - p * full;
        if (remain < (full / 2)) {
            return p * full / 2;
        }

        return p * full / 2 + remain - (full / 2) + 1;
    }

    static bool judge(long long k, int x, long long value) {
        unsigned long long total = 0;
        int i = 0;
        long long loop_flgs = value;
        while(loop_flgs != 0) {
            if ((i + 1) % x == 0) {
                total += sum_bits(value, i);
            }
            loop_flgs &= ~(1LL << i);
            i++;
        }
        return total <= k;
    }


    long long findMaximumNumber(long long k, int x) {

        long long l = 1;
        long long r = LLONG_MAX / 10;

        while (r - l > 1) {
            const auto value = (r - l) / 2 + l;
            const auto result = judge(k, x, value);

            if (result) {
                l = value;
            }
            else {
                r = value;
            }
        }
        return l;
    }
};

void test(long long k, int x) {
    cout << Solution().findMaximumNumber(k, x) << endl;
}

string pp(int value) {
    string s;
    for (int i = 7; i >= 0; i--) {
        if ((value & (1 << i)) != 0) {
            s += '1';
        }
        else {
            s += '0';
        }
    }
    return s;
}


int main()
{
    test(83, 7);
    test(19, 6);
    test(7, 2);
    test(3278539330613, 5);
    test(9, 1);
}
