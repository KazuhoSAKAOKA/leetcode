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

    vector<int> get_digits(int n) {
        if (n == 0) { return { 0 }; }
        int cur(n);
        vector<int> digits;
        while (cur > 0) {
            digits.emplace_back(cur % 10);
            cur /= 10;
        }
        return digits;
    }
    int maxProduct(int n) {
        auto digits = get_digits(n);
        sort(begin(digits), end(digits), greater<int>());
        return digits[0] * digits[1];
    }
};
void test(int n) {
    cout << Solution().maxProduct(n) << endl;
}

static void run() {
    test(124);
    test(31);
    test(22);
}

}
namespace problem2 {
class Solution {
public:
    static bool check_pair(int n, const vector<vector<int>>& grid, int ley, int lex, int gry, int grx) {
        if (gry < 0 || n <= gry || grx < 0 || n <= grx || ley < 0 || n <= ley || lex < 0 || n <= lex) { return true; }
        if (grid[gry][grx] < 0 || grid[ley][lex] < 0) { return true; }
        return grid[gry][grx] > grid[ley][lex];
    }

    static bool check_cell1(int n, const vector<vector<int>>& grid, int y, int x) {
        const auto cond1 = check_pair(n, grid, y - 1, x + 1, y + 1, x + 1);
        if (!cond1) { return false; }
        const auto cond2 = check_pair(n, grid, y + 1, x + 1, y + 1, x - 1);
        if (!cond2) { return false; }
        const auto cond3 = check_pair(n, grid, y + 1, x - 1, y - 1, x - 1);
        return cond3;
    }

    static bool check_cell(int n, const vector<vector<int>>& grid, int y, int x) {
        if (!check_cell1(n, grid, y - 1, x - 1)) { return false; }
        if (!check_cell1(n, grid, y - 1, x + 1)) { return false; }
        if (!check_cell1(n, grid, y + 1, x + 1)) { return false; }
        if (!check_cell1(n, grid, y + 1, x - 1)) { return false; }
        return true;
    }


    static bool rec(int n, vector<vector<int>>& grid, set<int>& values) {
        if (values.empty()) {
            return true;
        }
        auto it = begin(values);
        const auto value = *it;
        values.erase(it);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] < 0) {
                    grid[i][j] = value;
                    if (check_cell(n, grid, i, j)) {
                        if (rec(n, grid, values)) {
                            return true;
                        }
                    }
                    grid[i][j] = -1;
                }
            }
        }
        values.insert(value);
        return false;
    }

    static vector<vector<int>> tle(int N) {
        const auto n = 1 << N;
        vector<vector<int>> ans(n, vector<int>(n, -1));
        set<int> values;
        for (int i = 0; i < n * n; i++) {
            values.insert(i);
        }
        rec(n, ans, values);
        return ans;
    }

    static void update(int max_depth, int cur_depth, vector<vector<int>>& grid, int y, int x, int& cur_value) {
        if (cur_depth == max_depth) {
            grid[y][x + 1] = cur_value++;
            grid[y + 1][x + 1] = cur_value++;
            grid[y + 1][x] = cur_value++;
            grid[y][x] = cur_value++;
            return;
        }
        update(max_depth, cur_depth + 1, grid, (y + 0) * 2, (x + 1) * 2, cur_value);
        update(max_depth, cur_depth + 1, grid, (y + 1) * 2, (x + 1) * 2, cur_value);
        update(max_depth, cur_depth + 1, grid, (y + 1) * 2, (x + 0) * 2, cur_value);
        update(max_depth, cur_depth + 1, grid, (y + 0) * 2, (x + 0) * 2, cur_value);
    }


    vector<vector<int>> specialGrid(int N) {
        const auto n = 1 << N;
        const auto nh = n / 2;
        vector<vector<int>> grid(n, vector<int>(n, -1));
        if (N == 0) {
            grid[0][0] = 0;
            return grid;
        }
        int cur_value = 0;
        update(N - 1, 0, grid, 0, 0, cur_value);
        return grid;
    }
};
void test(int N) {
    output_matrix(Solution().specialGrid(N));
}
static void run() {
    test(3);
    //test(2);
    //test(1);
    //test(0);
}

}
namespace problem3 {
    class Solution {
    public:

        static int rec(int l, int n, int k, const vector<int>& position, const vector<int>& time, int index, int cur_operated,int cur_time, map<tuple<int, int, int>, int>& memo) {
            if (index >= n - 1) {
                if (cur_operated == k) {
                    return 0;
                }
                return INT_MAX / 2;
            }
            const auto key = make_tuple(index, cur_operated, cur_time);
            auto it = memo.find(key);
            if (it != cend(memo)) {
                return it->second;
            }

            int min_time = INT_MAX;
            min_time = min(min_time, rec(l, n, k, position, time, index + 1, cur_operated, time[index+1], memo) + cur_time * (position[index + 1] - position[index]));
            if (cur_operated < k) {
                const auto max_merges = min(k - cur_operated, n - (index + 1) - 1);
                int next_time = time[index + 1];
                for (int i = 1; i <= max_merges; i++) {
                    next_time += time[index + 1 + i];
                    const auto dist = position[index + i + 1] - position[index];
                    min_time = min(min_time, rec(l, n, k, position, time, index + i + 1, cur_operated + i, next_time, memo) + cur_time * dist);
                }
            }
            memo.insert({ key, min_time });
            return min_time;
        }


        int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
            map<tuple<int, int, int>, int> memo;
            return rec(l,n,k,position, time, 0, 0, time[0], memo);
        }

        static int dodp(int l, int n, int k, vector<int>& position, vector<int>& time) {
            vector<vector<int>> dp(n, vector<int>(k + 1));
            dp[0][0] = 0;
            for (int i = 1; i < n; i++) {
                dp[i][0] = dp[i - 1][0] + (position[i] - position[i - 1]) * time[i - 1];
            }
            for (int j = 1; j <= k; j++) {
                dp[0][j] = 0;
                for (int i = 1; i < n; i++) {

                }
            }

            return dp[n - 1][k];
        }

    };
    void test(int l, int n, int k, vector<int>&& position, vector<int>&& time) {
        cout << Solution().minTravelTime(l, n, k, position, time) << endl;
    }
static void run() {
    test(10, 4, 1, get_list_int("[0,3,8,10]"), get_list_int("[5,8,3,6]"));
    test(5, 5, 1, get_list_int("[0,1,2,3,5]"), get_list_int("[8,3,9,3,3]"));
}

}
namespace problem4 {
class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {

    }
};

void test(int m, int k, vector<int>&& nums) {
    cout << Solution().magicalSum(m, k, nums) << endl;
}

static void run() {
    test(5, 5, get_list_int("[1,10,100,10000,1000000]"));
    test(2, 2, get_list_int("[5,4,3,2,1]"));
    test(1, 1, get_list_int("[28]"));
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