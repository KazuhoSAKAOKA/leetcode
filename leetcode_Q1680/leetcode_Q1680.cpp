#include <iostream>
using namespace std;
class Solution {
public:
    int concatenatedBinary(int n) {
        long long ans = 0;

        constexpr long long MODULO = 1e9 + 7;

        for (int i = 1; i <= n; i++) {
            int bit = 31;
            while ((i & (1 << bit)) == 0) {
                bit--;
            }
            for (;bit >= 0; bit--) {
                ans = ans << 1;
                if ((i & (1 << bit))) {
                    ans |= 1;
                }
                ans %= MODULO;
            }
        }
        return static_cast<int>(ans);
    }
};

static void test(int n) {
    cout << Solution().concatenatedBinary(n) << endl;
}

int main()
{
    test(1);
    test(3);
    test(12);
    return 0;
}


