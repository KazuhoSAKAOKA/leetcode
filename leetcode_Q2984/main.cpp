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
    int differenceOfSums(int n, int m) {
        const long long total = n * (n + 1) / 2;
        int l = n / m;
        const long long num2 = m * (l * (l + 1) / 2);
        const long long num1 = total - num2;
        return static_cast<int>(num1 - num2);
    }
};
void test(int n, int m) {
    cout << Solution().differenceOfSums(n, m) << endl;
}
int main() {
    test(10, 3);
	return 0;
}