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
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
constexpr long long MODULO = 1e9 + 7;


template<typename T>
vector<vector<T>> mul_mat(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    int n = a.size();
    int m = b[0].size();
    vector<vector<T>> res(n, vector<long long>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < a[0].size(); k++) {
            long long r = a[i][k];
            if (r == 0) {
                continue;
            }
            for (int j = 0; j < m; j++) {
                res[i][j] = (res[i][j] + r * b[k][j]) % MODULO;
            }
        }
    }
    return res;
}

template<typename T>
vector<vector<T>> pow_mat(const vector<vector<T>>& base, long long exp, const vector<vector<T>>& result) {
    auto base1(base);
    auto result1(result);

    while (exp) {
        if (exp & 1) {
            result1 = mul_mat(result1, base1);
        }

        base1 = mul_mat(base1, base1);

        exp >>= 1;
    }

    return result1;
}

class Solution {
public:
    //int l(int n, int l, int r) {
        /*onst long long m = r - l + 1;
        if (n == 1) {
            return m;
        }

        vector<vector<long long>> mat_1(m, vector<long long>(m));
        vector<vector<long long>> mat_2(m, vector<long long>(m));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) {
                mat_1[i][m - j - 1] = 1;
                mat_2[m - i - 1][j] = 1;
            }
        }

        vector<vector<long long>> mat_conv = mul_mat(mat_1, mat_2);

        vector<vector<long long>> mat_p = pow_mat(mat_conv, n / 2);
        if (n % 2 == 1) {
            mat_p = mul_mat(mat_p, mat_1);
        }
        vector<vector<long long>> dp(m, vector<long long>(1, 1));
        auto last = mul_mat(mat_p, dp);
        long long total = 0;
        for (auto&& i = 0; i < m; i++) {
            total += dp[i][0];
            total %= MODULO;
        }
        total *= 2;
        total /= MODULO;

        return static_cast<int>(total);*/
    //}

    int zigZagArrays(int n, int l, int r) {
        const long long m = r - l + 1;
        if (n == 1) {
            return m;
        }
        
        vector<vector<long long>> mat(m * 2, vector<long long>(m * 2));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) {
                mat[i][j + m] = 1;
            }
            for (int j = i + 1; j < m; j++) {
                mat[i + m][j] = 1;
            }
        }
        vector<vector<long long>> dp(1, vector<long long>(m * 2, 1));
        dp = pow_mat(mat, n - 1, dp);
        long long total = 0;
        for (auto&& i = 0; i < m * 2; i++) {
            total += dp[0][i];
            total %= MODULO;
        }
        return static_cast<int>(total);
    }
};

static void test(int n, int l, int r) {
    cout << Solution().zigZagArrays(n, l, r) << endl;
}
int main() {
    //test(3, 4, 5);
    test(3, 1, 3);
    return 0;
}
