#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <functional>
using namespace std;
class Solution {
public:

    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    int maxBottlesDrunk(int numBottles, int numExchange) {
        int drunked_bottles = 0;
        int cur_bottles = numBottles;
        int cur_exchange = numExchange;
        while (cur_bottles > 0) {
            const auto cur_drunk_count = binary_search_meguru<int>(0, cur_bottles + 1,
                [&](int count)->bool {
                    int inc = count * (count - 1) / 2;
                    return count * cur_exchange + inc <= cur_bottles;
                });

            if (cur_drunk_count == 0) {
                drunked_bottles += cur_bottles;
                break;
            }
            const auto consumed = cur_drunk_count * (cur_drunk_count - 1) / 2 + cur_drunk_count * cur_exchange;
            cur_exchange += cur_drunk_count;
            drunked_bottles += consumed;
            cur_bottles -= consumed;
            cur_bottles += cur_drunk_count;

        }
        return drunked_bottles;
    }
};

static void test(int numBottles, int numExchange) {
    cout << Solution().maxBottlesDrunk(numBottles, numExchange) << endl;
}
int main() {
    test(13, 6);
    test(10, 3);
	return 0;
}