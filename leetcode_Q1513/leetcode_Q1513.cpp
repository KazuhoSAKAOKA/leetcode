#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <optional>
#include <functional>

using namespace std;

class Solution {
public:
    int numSub(string s) {
        const long long n = size(s);
        constexpr  long long MODULO = 1e9 + 7;
        long long total = 0LL;
        long long l = 0LL;
        long long cur_count = 0LL;
        for (long long r = 0; r < n; r++) {
            cur_count += s[r] == '1' ? 1LL : 0LL;
            while (l < r && cur_count < (r - l + 1)) {
                cur_count -= s[l] == '1' ? 1LL : 0LL;
                l++;
            }
            if ((r - l + 1) == cur_count) {
                total += (r - l + 1);
                total %= MODULO;
            }
        }
        return static_cast<int>(total);
    }
};

static void test(string&& s) {
    cout << Solution().numSub(s) << endl;
}


int main(){
    test("0110111");
    test("101");
    test("111111");

	return 0;
}