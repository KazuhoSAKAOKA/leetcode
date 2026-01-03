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
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int numOfWays(int n) {
        constexpr long long MODULO = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(12));
        for (int i = 0; i < 12; i++) {
            dp[0][i] = 1;
        }
        map<int, vector<int>> transits{
            {0,{4,6,7,8,}},
            {1,{5,9,10,11,}},
            {2,{5,6,7,8,10,}},
            {3,{5,6,8,10,11,}},
            {4,{0,8,10,11,}},
            {5,{1,2,3,9,}},
            {6,{0,2,3,9,11,}},
            {7,{0,2,9,10,11,}},
            {8,{0,2,3,4,}},
            {9,{1,5,6,7,}},
            {10,{1,2,3,4,7,}},
            {11,{1,3,4,6,7,}},
        };
        for (int i = 0; i < n - 1; i++) {
            for (auto&& [s, dests] : transits) {
                for (auto&& d : dests) {
                    dp[i + 1][d] += dp[i][s];
                    dp[i + 1][d] %= MODULO;
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < 12; i++) {
            ans += dp[n - 1][i];
            ans %= MODULO;
        }
        return static_cast<int>(ans);
    }
};

static void test(int n) {
    cout << Solution().numOfWays(n) << endl;
}


static map<int, vector<int>> make_transits() {
    using P = tuple<int, int, int>;
    vector<P> ps{
        {0,1,2},
        {0,2,1},
        {0,1,0},
        {0,2,0},
        {1,2,0},
        {1,0,2},
        {1,0,1},
        {1,2,1},
        {2,0,1},
        {2,1,0},
        {2,0,2},
        {2,1,2},
    };

    map<int, vector<int>> mp;
    for (int i = 0; i < 12; i++) {
        vector<int> trans;
        auto [sr, sg, sb] = ps[i];
        for (int j = 0; j < 12; j++) {
            auto [r, g, b] = ps[j];
            if (sr == r || sg == g || sb == b) { continue; }
            trans.emplace_back(j);
        }
        mp.insert({ i, trans });
    }
    return mp;
}

int main()
{
/*    const auto pm = make_transits();
    for (auto&& [s, list] : pm) {
        cout << "{" << s << ".{";
        for (auto&& v : list) {
            cout << v << ",";
        }
        cout << "}}," << endl;
    }
    return 0*/;

    test(3);
    test(5000);
    return 0;
}