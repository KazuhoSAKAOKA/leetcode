#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    //const long long max_comb = numPeople + 1;
//vector<long long> fac(max_comb);
//vector<long long> finv(max_comb);
//vector<long long> inv(max_comb);
//fac[0] = fac[1] = 1;
//finv[0] = finv[1] = 1;
//inv[1] = 1;
//for (long long i = 2; i < max_comb; i++) {
//    fac[i] = fac[i - 1] * i % MODULO;
//    inv[i] = MODULO - inv[MODULO % i] * (MODULO / i) % MODULO;
//    finv[i] = finv[i - 1] * inv[i] % MODULO;
//}
//auto get_comb = [&](int n, int k)-> long long {
//    if (n < k) return 0;
//    if (n < 0 || k < 0) return 0;
//    return fac[n] * (finv[k] * finv[n - k] % MODULO) % MODULO;
//    };

    int numberOfWays(int numPeople) {
        constexpr unsigned long long MODULO = 1e9 + 7;
        vector<unsigned long long> memo(numPeople + 1, 0);
        memo[0] = 1LL;

        auto f = [&](auto f, unsigned long long v)-> unsigned long long {
            if (memo[v] > 0) {
                return memo[v];
            }
            long long total = 0LL;
            for (long long left = 0; left + 2 <= v; left += 2) {
                const auto right = v - left - 2;
                total += (f(f, left) * f(f, right)) % MODULO;
                total %= MODULO;
            }
            memo[v] = total;
            return total;
            };

        auto v = f(f, numPeople);

        return static_cast<int>(v % MODULO);
    }
};

static void test(int numPeople) {
    cout << Solution().numberOfWays(numPeople) << endl;
}
int main() {
    test(4);
    test(6);
    return 0;
}
