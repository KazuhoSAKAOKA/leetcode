#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    static long long power(long long base, long long exponent, long long modulo) {
        long long res = 1;
        while (exponent > 0) {
            if (exponent % 2 == 1) {
                res = ((res * base) % modulo);
            }
            base = (base * base) % modulo;
            exponent /= 2;
        }
        return res;
    }


    int countGoodNumbers(long long n) {
        constexpr long long PRIMES = 4;
        constexpr long long EVENS = 5;
        long long count_of_prime = n / 2;
        long long count_of_even = n / 2 + (n % 2 == 0 ? 0 : 1);
        return (power(PRIMES, count_of_prime, MODULO) * power(EVENS, count_of_even, MODULO)) % MODULO;
    }
};

void test(long long n) {
    cout << Solution().countGoodNumbers(n) << endl;
}
int main() {
    test(1);
    test(4);
    test(50);
    test(806166225460393);
    return 0;
}