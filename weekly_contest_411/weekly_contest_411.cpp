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
    int countKConstraintSubstrings(string s, int k) {
        int l = 0;
        int count = 0;
        unordered_map<char, int> freq_map;
        for (int r = 0; r < size(s); r++) {
            freq_map[s[r]]++;
            while(l < r && k < freq_map['0'] && k < freq_map['1']){
                freq_map[s[l]]--;
                l++;
            }
            count += r - l + 1;
        }
        return count;
    }
};
void test(string&& s, int k) {
    cout << Solution().countKConstraintSubstrings(s, k) << endl;
}
void run() {
    test("10101", 1);
    test("1010101", 2);
    test("11111", 1);
}
}
namespace problem2 {
class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        const auto n = size(energyDrinkA);
        vector<vector<long long>> dp(n, vector<long long>(3, 0));

        dp[0][0] = energyDrinkA[0];
        dp[0][1] = energyDrinkB[0];
        dp[0][2] = 0;

        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2]) + energyDrinkA[i];
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][2]) + energyDrinkB[i];
            dp[i][2] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][2]));
        }

        return max(dp[n - 1][0], max(dp[n - 1][1], dp[n - 1][2]));
    }
};
void test(vector<int>&& energyDrinkA, vector<int>&& energyDrinkB) {
    cout << Solution().maxEnergyBoost(energyDrinkA, energyDrinkB) << endl;
}
void run() {
    test(get_list_int("[1,3,1]"), get_list_int("[3,1,1]"));
    test(get_list_int("[4,1,1]"), get_list_int("[1,1,3]"));
}
}
namespace problem3 {
class Solution {
public:
    string largestPalindrome(int n, int k) {
        return "";
    }
};
void test(int n, int k) {
    cout << Solution().largestPalindrome(n, k) << endl;
}
void run() {
    test(3, 5);
    test(1, 4);
    test(5, 6);
}

}
namespace problem4 {
class Solution {
public:

    static long long count_range(const string& s, int k, int left, int right) {
        int l = left;
        int count = 0;
        unordered_map<char, int> freq_map;
        for (int r = left; r <= right; r++) {
            freq_map[s[r]]++;
            while (l < r && k < freq_map['0'] && k < freq_map['1']) {
                freq_map[s[l]]--;
                l++;
            }
            count += r - l + 1;
        }
        return count;
    }

    static vector<long long> tle(const string& s, int k, const vector<vector<int>>& queries) {
        vector<long long> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            ans.emplace_back(count_range(s, k, query[0], query[1]));
        }
        return ans;

    }

    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int l = 0;
        long long count = 0;
        vector<long long> prefix_sum(size(s) + 1);
        vector<long long> start_counts(size(s) + 1);
        unordered_map<char, int> freq_map;
        for (int r = 0; r < size(s); r++) {
            freq_map[s[r]]++;
            while (l < r && (k < freq_map['0'] && k < freq_map['1'])) {
                freq_map[s[l]]--;
                start_counts[l + 1] = start_counts[l] + r - l;
                l++;
            }
            count += r - l + 1;
            prefix_sum[r + 1] = count;
        }
        for (; l < size(s); l++) {
            start_counts[l + 1] = start_counts[l] + size(s) - l;
        }
        vector<long long> ans;
        ans.reserve(size(queries));

        for (auto&& query : queries) {
            const auto v = prefix_sum[query[1] + 1] - start_counts[query[0]];
            ans.emplace_back(v);
        }
        return ans;
    }
};
void test(string&& s, int k, vector<vector<int>>&& queries) {
    const auto ans = Solution().countKConstraintSubstrings(s, k, queries);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test("000", 1, get_matrix_int("[[0,0],[0,1],[0,2],[1,1],[1,2],[2,2]]"));
    test("00", 1, get_matrix_int("[[0,0],[0,1],[1,1]]"));
    test("0001111", 2, get_matrix_int("[[0,6]]"));
    test("010101", 1, get_matrix_int("[[0,5],[1,4],[2,3]]"));
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