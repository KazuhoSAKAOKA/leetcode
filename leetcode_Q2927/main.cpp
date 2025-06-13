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
    static long long distributeCandies(int n, int limit) {
        long long ans = 0;
        for (int i = 0; i <= min(n, limit); i++) {
            const auto remain = n - i;
            if (remain <= limit * 2) {
                if (remain <= limit) {
                    ans += static_cast<long long>(remain + 1);
                }
                else {
                    ans += static_cast<long long>(2 * limit - remain + 1);
                }
            }
        }

        return ans;
    }

    std::vector<std::vector<long long>> comb(int n, int r) {
        std::vector<std::vector<long long>> v(n + 1, std::vector<long long>(n + 1, 0));
        for (int i = 0; i < v.size(); i++) {
            v[i][0] = 1;
            v[i][i] = 1;
        }
        for (int j = 1; j < v.size(); j++) {
            for (int k = 1; k < j; k++) {
                v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
            }
        }
        return v;
    }


    long long distributeCandies(int n, int limit) {
        const auto m = n + limit + 1;
        const auto C = comb();
        vector<long long> memo(m);
        long long ans=factorial()
        return ans;
    }
};
int main() {
	return 0;
}