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
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        constexpr long long MODULO = 1e9 + 7;
        vector<long long> known_decs(n + 1);
        vector<long long> publisher_incs(n + 1);

        long long cur_known = 0;
        long long cur_publisher = 0;

        cur_known = 1;
        publisher_incs[min(n, delay)] = 1;

        known_decs[min(n, forget)] = 1;
        publisher_incs[min(n, forget)] = -1;
        auto inc = [&](long long a, long long b)->long long {
            const auto c = a + b;
            if (c < 0) {
                return c + MODULO;
            }
            return c % MODULO;
            };
        for (int i = 1; i < n; i++) {
            cur_publisher = inc(cur_publisher, publisher_incs[i]);

            cur_known = inc(cur_known, cur_publisher);
            cur_known = inc(cur_known, -1 * known_decs[i]);

            publisher_incs[min(n, i + delay)] = inc(publisher_incs[min(n, i + delay)], cur_publisher);

            known_decs[min(n, i + forget)] = inc(known_decs[min(n, i + forget)], 1LL * cur_publisher);
            publisher_incs[min(n, i + forget)] = inc(publisher_incs[min(n, i + forget)], -1LL * cur_publisher);
        }
        return static_cast<int>(cur_known);
    }
};
static void test(int n, int delay, int forget) {
    cout << Solution().peopleAwareOfSecret(n, delay, forget) << endl;
}
int main() {
    test(7, 2, 4);
    test(6, 2, 4);
    test(4, 1, 3);
	return 0;
}