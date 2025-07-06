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
constexpr size_t MODULO = 1e9 + 7;
class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        vector<size_t> prev(k + 1, 0);
        prev[0] = m;
        for (int i = 1; i < n; i++) {
            vector<size_t> current(k + 1, 0);
            current[0] = prev[0] * (m - 1) % MODULO;
            for (int j = 1; j <= k; j++) {
                current[j] = (prev[j - 1] + prev[j] * (m - 1))% MODULO;
            }
            swap(prev, current);
        }
        return static_cast<int>(prev[k]);
    }
};

void test(int n, int m, int k) {
    cout << Solution().countGoodArrays(n, m, k) << endl;
}
int main() {
    test(3, 2, 1);
    test(4, 2, 2);
    test(5, 2, 0);
    return 0;
}