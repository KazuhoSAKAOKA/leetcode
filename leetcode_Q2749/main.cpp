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

    static int naive(int num1, int num2) {
        vector<long long> vals(61);
        vals[0] = 1;
        for (int i = 0; i < 60; i++) {
            vals[i + 1] = vals[i] * 2;
        }
        int count = 1;
        set<long long> befores{ num1 };
        while (!befores.empty()) {
            set<long long> nexts;
            for (auto&& val : befores) {
                for (int i = 0; i < 60; i++) {
                    const auto v = val - (vals[i] + num2);
                    if (v == 0) {
                        return count;
                    }
                    if (0 < v) {
                        nexts.insert(v);
                    }
                }
            }
            swap(befores, nexts);
            count++;
            if (count > 60) { break; }
        }
        return -1;
    }
    template <typename T>
    static int popcount_kernighan(T x) {
        int count = 0;
        while (x) {
            x &= (x - 1);
            count++;
        }
        return count;
    }
    int makeTheIntegerZero(int num1, int num2) {
        if (num1 == 0) { return 0; }
        long long current(num1);
        for (int i = 0; i <= 60; i++) {
            current -= num2;
            if (current < 0) { return -1; }
            const auto pc = popcount_kernighan(current);
            if (pc <= i + 1 && i + 1 <= current) {
                return i + 1;
            }
        }
        return -1;
    }
};
static void test(int num1, int num2) {
    cout << Solution().makeTheIntegerZero(num1, num2) << endl;
}
int main() {
    test(3, -2);
    test(5, 7);
	return 0;
}