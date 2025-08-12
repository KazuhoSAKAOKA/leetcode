#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
using namespace std;
class Solution {
public:

    static long long powx(long long base, int e) {
        if (e == 0) { return 1LL; }
        if (e % 2 == 1) {
            return powx(base * base, e / 2) * base;
        }
        else {
            return powx(base * base, e / 2);
        }
    }

    int numberOfWays(int n, int x) {
        constexpr long long MODULO = 1e9 + 7;
        unordered_map<long long, long long> before;
        long long value = 1;
        
        for (;;) {
            const long long v = powx(value, x);
            if (n < v) {
                break;
            }
            unordered_map<long long, long long> current;
            current[v]++;
            current[v] %= MODULO;
            for (auto&& [k, count] : before) {
                current[k] += count;
                current[k] %= MODULO;
                if (k + v <= n) {
                    current[k + v] += count;
                    current[k + v] %= MODULO;
                }
            }
            value++;
            swap(current, before);
        }

        return static_cast<int>(before[n]);
    }
};

static void test(int n, int x) {
    cout << Solution().numberOfWays(n, x) << endl;
}
int main() {
    test(10, 2);
    test(4, 1);
	return 0;
}