// leetcode_Q0264.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const vector<int> limited_prime_factors{ 2,3,5, };
class Solution {
public:

    static bool check_tle(int n) {
        auto v = n;
        int index = 0;
        while (v != 1 && index < size(limited_prime_factors)) {
            if (v % limited_prime_factors[index] == 0) {
                v /= limited_prime_factors[index];
            }
            else {
                index++;
            }
        }
        return v == 1;
    }

    static int prob_tle(int n) {
        if (n == 1) { return 1; }
        int current_count = 1;
        int current_value = 1;
        while (current_count < n) {
            current_value++;
            if (check_tle(current_value)) {
                current_count++;
            }
        }
        return current_value;
    }

    int nthUglyNumber(int n) {
        set<long long> befores{ 1,};
        long long current_value = 1;
        for (int i = 1; i < n; i++) {
            long long current_min = INT_MAX;
            for (auto it = begin(befores); it != end(befores);) {
                const auto v = *it;
                bool exist = false;
                for (auto&& p: limited_prime_factors) {
                    const auto candidate = p * v;
                    if (current_value < candidate) {
                        current_min = min(current_min, candidate);
                        exist = true;
                    }
                }
                if (exist) {
                    ++it;
                }
                else {
                    it = befores.erase(it);
                }
            }
            current_value = current_min;
            befores.insert(current_min);
        }

        return static_cast<int>(current_value);
    }
};

void test(int n) {
    cout << Solution().nthUglyNumber(n) << endl;
}

int main()
{
    test(2);
    test(10);
    test(1);
    test(1690);
    return 0;
}