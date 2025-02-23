#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {

class Solution {
public:
    inline static char get_digit(char a, char b) {
        const auto c = a - '0' + b - '0';
        return (c % 10) + '0';
    }

    bool hasSameDigits(string s) {
        string current(s);
        while (size(current) > 2) {
            string work;
            for (int i = 0; i < size(current) - 1; i++) {
                work += get_digit(current[i], current[i + 1]);
            }
            current = work;
        }
        return current[0] == current[1];
    }
};

void test(string&& s) {
    cout << Solution().hasSameDigits(s) << endl;
}
static void run() {
    test("3902");
    test("34789");
}

}
namespace problem2 {
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        const size_t n = size(grid);
        const size_t m = size(grid.front());
           
        vector<int> indexes(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                indexes[i * m + j] = i * m + j;
            }
        }
        sort(begin(indexes), end(indexes), [&](const int& a, const int& b) { return grid[a / m][a % m] > grid[b / m][b % m]; });
        long long total = 0LL;
        vector<int> current_uses(n);
        int count = 0;
        int index = 0;
        while (count < k && index < size(indexes)) {
            const int y = indexes[index] / m;
            const int x = indexes[index] % m;
            if (current_uses[y] < limits[y]) {
                total += static_cast<long long>(grid[y][x]);
                count++;
                current_uses[y]++;
            }
            index++;
        }
        return total;
    }
}; 
void test(vector<vector<int>>&& grid, vector<int>&& limits, int k) {
    cout << Solution().maxSum(grid, limits, k) << endl;
}
static void run() {
    test(get_matrix_int("[[5,3,7],[8,2,6]]"), get_list_int("[2,2]"), 3);
    test(get_matrix_int("[[1,2],[3,4]]"), get_list_int("[1,2]"), 2);
}
}
namespace problem3 {
    constexpr long long MOD = 10000000;
class Solution {
public:
    vector<long long> fact, fact_inv, inv;
    void init_nCk(int SIZE) {
        fact.resize(SIZE + 5);
        fact_inv.resize(SIZE + 5);
        inv.resize(SIZE + 5);
        fact[0] = fact[1] = 1;
        fact_inv[0] = fact_inv[1] = 1;
        inv[1] = 1;
        for (int i = 2; i < SIZE + 5; i++) {
            fact[i] = fact[i - 1] * i % MOD;
            inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
            fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
        }
    }

    long long nCk(int n, int k) {
        return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
    }

    long long combination(int n, int k) {

    }


    bool hasSameDigits(string s) {
        const auto n = size(s);
        init_nCk(n*2);
        vector<int> vals(n);
        for (int i = 0; i < n; i++) {
            vals[i] = static_cast<int>(s[i] - '0');
        }
        int cur_left_val = 0;
        for (int i = 0; i < n - 1; i++) {
            const auto temp = min(i, static_cast<int>(n) - i - 2) + 1;
            const auto mul = nCk(n - 1, temp);
            const auto val = vals[i] * mul;
            cur_left_val += val;
            cur_left_val %= 10;
        }
        int cur_right_val = 0;
        for (int i = 1; i < n; i++) {
            const auto temp = min(i, static_cast<int>(n) - i - 2) + 1;
            const auto mul = nCk(n - 1, temp);
            const auto val = vals[i] * mul;
            cur_right_val += val;
            cur_right_val %= 10;
        }
        return cur_left_val == cur_right_val;
    }
};

void test(string&& s) {
    cout << Solution().hasSameDigits(s) << endl;
}
static void run() {
    test("3902");
    test("34789");
}

}
namespace problem4 {
    static void run() {
    }
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}