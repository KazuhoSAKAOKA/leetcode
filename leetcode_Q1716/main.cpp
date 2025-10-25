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
    int totalMoney(int n) {
        const auto full_weeks = n / 7;
        const auto base = full_weeks * 28;
        const auto base_appends = full_weeks > 1 ? ((full_weeks - 1) * full_weeks / 2) * 7 : 0;

        const auto m = n % 7;
        const auto cur_week_base = (m + 1) * m / 2;
        const auto cur_week_append = full_weeks * m;
        return base + base_appends + cur_week_base + cur_week_append;
    }
};

static void test(int n) {
    cout << Solution().totalMoney(n) << endl;
}
int main() {
    test(4);
    test(10);
    test(20);
	return 0;
}