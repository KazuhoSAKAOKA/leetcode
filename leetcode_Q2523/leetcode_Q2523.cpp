// leetcode_Q2523.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


class Solution {
public:

    static vector<bool> eratosthenes(int n) {
        vector<bool> candidates(n + 1, true);
        candidates[0] = false;
        candidates[1] = false;
        const auto limit = sqrt(n);
        int current = 2;
        while (current <= limit) {
            if (candidates[current]) {
                for (int i = 2; i * current <= n; i++) {
                    candidates[i * current] = false;
                }
            }
            current++;
        }
        return candidates;
    }

    vector<int> closestPrimes(int left, int right) {
        const auto primes = eratosthenes(right);
        int min_diff = INT_MAX;
        int a = -1;
        int b = -1;
        int before_prime = -1;
        for (int i = left; i <= right; i++) {
            if (primes[i]) {
                if (before_prime < 0) {
                    before_prime = i;
                }
                else {
                    const auto diff = i - before_prime;
                    if (diff < min_diff) {
                        a = before_prime;
                        b = i;
                        min_diff = diff;
                    }
                    before_prime = i;
                }
            }
        }
        return { a,b };
    }
};

void test(int left, int right) {
    output(Solution().closestPrimes(left, right));
}
int main()
{
    test(10, 19);
    test(4, 6);
    return 0;
}