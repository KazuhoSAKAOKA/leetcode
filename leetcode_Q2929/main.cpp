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
    long long distributeCandies(int n, int limit) {
        if (limit * 3 < n) {
            return 0;
        }
        long long ans = 0;

        for (int i = 0; i <= min(n, limit); i++) {
            const auto remain = n - i;
            if (remain <= limit * 2) {
                if (remain <= limit) {
                    ans += remain + 1;
                }
                else {
                    ans += limit * 2 - remain + 1;
                }
            }
        }

        return ans;
    }
};
void test(int n, int limit) {
    cout << Solution().distributeCandies(n, limit) << endl;
}
int main() {
    test(5, 2);
    test(3, 3);
    return 0;
}