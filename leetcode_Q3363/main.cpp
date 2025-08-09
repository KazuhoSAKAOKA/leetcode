#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static int rec(const vector<vector<int>>& fruits, vector<vector<bool>>& used, int index, const pair<int, int>& p1, const pair<int, int>& p2, const pair<int, int>& p3) {
        const auto n = size(fruits);
        if (index == n - 1) {
            if (p1.first == n - 1 && p1.second == n - 1 && p2.first == n - 1 && p2.second == n - 1 && p3.first == n - 1 && p3.second == n - 1) {
                return 0;
            }
            return INT_MIN;
        }
        auto check = [&](const pair<int, int>& p)->bool {
            return 0 <= p.first && p.first < n && 0 <= p.second && p.second < n;
            };

        static const vector<pair<int, int>> d1s{ { 1,1 },{ 1,0 },{ 0,1 }, };
        static const vector<pair<int, int>> d2s{ { 1,-1 },{ 1,0 },{ 1,1 }, };
        static const vector<pair<int, int>> d3s{ { -1,1 },{ 0,1 },{ 1,1 }, };
        bool queried = false;
        int max_fruits = 0;
        for (auto&& d1 : d1s) {
            const auto next1 = make_pair(p1.first + d1.first, p1.second + d1.second);
            if (check(next1)) {
                const bool flg1 = used[next1.first][next1.second];
                const int cur_score1 = (flg1 ? 0 : fruits[next1.first][next1.second]);
                if (!flg1) {
                    used[next1.first][next1.second] = true;
                }
                for (auto&& d2 : d2s) {
                    const auto next2 = make_pair(p2.first + d2.first, p2.second + d2.second);
                    if (check(next2)) {
                        const bool flg2 = used[next2.first][next2.second];
                        const int cur_score2 = cur_score1 + (flg2 ? 0 : fruits[next2.first][next2.second]);
                        if (!flg2) {
                            used[next2.first][next2.second] = true;
                        }
                        for (auto&& d3 : d3s) {
                            const auto next3 = make_pair(p3.first + d3.first, p3.second + d3.second);
                            if (check(next3)) {
                                const bool flg3 = used[next3.first][next3.second];
                                const int cur_score3 = cur_score2 + (flg3 ? 0 : fruits[next3.first][next3.second]);
                                if (!flg3) {
                                    used[next3.first][next3.second] = true;
                                }
                                const int v = rec(fruits, used, index + 1, next1, next2, next3);

                                max_fruits = max(max_fruits, v + cur_score3);
                                queried = true;
                                if (!flg3) {
                                    used[next3.first][next3.second] = false;
                                }
                            }
                        }
                        if (!flg2) {
                            used[next2.first][next2.second] = false;
                        }
                    }
                }
                if (!flg1) {
                    used[next1.first][next1.second] = false;
                }
            }
        }
        if (queried) {
            return max_fruits;
        }
        return 0;
    }

    static int rec2(const vector<vector<int>>& fruits, vector<vector<bool>>& used, int index, const pair<int, int>& p1, const pair<int, int>& p2, const pair<int, int>& p3, int total) {
        const auto n = size(fruits);
        if (index == n - 1) {
            if (p1.first == n - 1 && p1.second == n - 1 && p2.first == n - 1 && p2.second == n - 1 && p3.first == n - 1 && p3.second == n - 1) {
                return total;
            }
            return 0;
        }
        auto check = [&](const pair<int, int>& p)->bool {
            return 0 <= p.first && p.first < n && 0 <= p.second && p.second < n;
            };

        static const vector<pair<int, int>> d1s{ { 1,1 },{ 1,0 },{ 0,1 }, };
        static const vector<pair<int, int>> d2s{ { 1,-1 },{ 1,0 },{ 1,1 }, };
        static const vector<pair<int, int>> d3s{ { -1,1 },{ 0,1 },{ 1,1 }, };
        int max_fruits = 0;
        for (auto&& d1 : d1s) {
            const auto next1 = make_pair(p1.first + d1.first, p1.second + d1.second);
            if (check(next1)) {
                const bool flg1 = used[next1.first][next1.second];
                const int cur_score1 = (flg1 ? 0 : fruits[next1.first][next1.second]);
                if (!flg1) {
                    used[next1.first][next1.second] = true;
                }
                for (auto&& d2 : d2s) {
                    const auto next2 = make_pair(p2.first + d2.first, p2.second + d2.second);
                    if (check(next2)) {
                        const bool flg2 = used[next2.first][next2.second];
                        const int cur_score2 = cur_score1 + (flg2 ? 0 : fruits[next2.first][next2.second]);
                        if (!flg2) {
                            used[next2.first][next2.second] = true;
                        }
                        for (auto&& d3 : d3s) {
                            const auto next3 = make_pair(p3.first + d3.first, p3.second + d3.second);
                            if (check(next3)) {
                                const bool flg3 = used[next3.first][next3.second];
                                const int cur_score3 = cur_score2 + (flg3 ? 0 : fruits[next3.first][next3.second]);
                                if (!flg3) {
                                    used[next3.first][next3.second] = true;
                                }
                                const int v = rec2(fruits, used, index + 1, next1, next2, next3, total + cur_score3);
                                max_fruits = max(max_fruits, v);
                                if (!flg3) {
                                    used[next3.first][next3.second] = false;
                                }
                            }
                        }
                        if (!flg2) {
                            used[next2.first][next2.second] = false;
                        }
                    }
                }
                if (!flg1) {
                    used[next1.first][next1.second] = false;
                }
            }
        }
        return max_fruits;
    }

    int maxCollectedFruits(vector<vector<int>>& fruits) {
        const int n = static_cast<int>(size(fruits));

        int total = 0;
        vector<map<int, int>> dp1(n - 1);
        vector<map<int, int>> dp2(n - 1);

        for (int i = 0; i < n; i++) {
            total += fruits[i][i];
        }

        dp1[0][0] = fruits[0][n - 1];
        dp2[0][0] = fruits[n - 1][0];
        const auto half = n % 2 == 0 ? n / 2 : n / 2 + 1;

        for (int i = 1; i < n - 1; i++) {
            for (auto&& [k, v] : dp1[i - 1]) {
                const int s = max(0, k - 1);
                const int l = min(k + 1, n - 2 - i);
                for (int j = s; j <= l; j++) {
                    dp1[i][j] = max(dp1[i][j], v + fruits[i][n - j - 1]);
                }
            }
            for (auto&& [k, v] : dp2[i - 1]) {
                const int s = max(0, k - 1);
                const int l = min(k + 1, n - 2 - i);
                for (int j = s; j <= l; j++) {
                    dp2[i][j] = max(dp2[i][j], v + fruits[n - j - 1][i]);
                }
            }
        }

        return total + dp1.back()[0]+ dp2.back()[0];
    }
};

static void test(vector<vector<int>>&& fruits) {
    cout << Solution().maxCollectedFruits(fruits) << endl;
}
int main() {
    test(get_matrix_int("[[4,18,19,9,20,14],[16,4,4,16,15,16],[2,11,15,6,8,9],[6,7,11,17,7,6],[17,17,2,13,2,14],[16,9,6,14,7,16]]"));
    test(get_matrix_int("[[8,5,0,17,15],[6,0,15,6,0],[7,19,16,8,18],[11,3,2,12,13],[17,15,15,4,6]]"));
    test(get_matrix_int("[[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]"));
    test(get_matrix_int("[[1,1],[1,1]]"));
    return 0;
}