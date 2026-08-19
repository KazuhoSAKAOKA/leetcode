

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

class Solution {
public:

    static int mle(int n, vector<vector<int>>& reservedSeats) {
        vector<unsigned char> seats(n);
        for (auto&& reserved : reservedSeats) {
            const auto row = reserved[0] - 1;
            const auto seat = reserved[1];
            if (2 <= seat && seat <= 9) {
                const unsigned char val = 1 << (seat - 2);
                seats[row] |= val;
            }
        }

        int ans = 0;
        constexpr unsigned char grp2 = 0b11111111;
        constexpr unsigned char grp1_0 = 0b11110000;
        constexpr unsigned char grp1_1 = 0b00111100;
        constexpr unsigned char grp1_2 = 0b00001111;

        for (auto&& seat : seats) {
            if ((seat & grp2) == 0) {
                ans += 2;
            }
            else {
                if (
                    (seat & grp1_0) == 0 ||
                    (seat & grp1_1) == 0 ||
                    (seat & grp1_2) == 0
                    ) {
                    ans++;
                }
            }
        }
        return ans;
    }

    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        sort(begin(reservedSeats), end(reservedSeats), [](const auto& a, const auto& b) { return a[0] < b[0]; });

        auto get_count = [](short seat) {
            constexpr short grp2  =  0b0111111110;
            constexpr short grp1_0 = 0b0111100000;
            constexpr short grp1_1 = 0b0001111000;
            constexpr short grp1_2 = 0b0000011110;
            if ((seat & grp2) == 0) {
                return 2;
            }
            else {
                if (
                    (seat & grp1_0) == 0 ||
                    (seat & grp1_1) == 0 ||
                    (seat & grp1_2) == 0
                    ) {
                    return 1;
                }
            }
            return 0;
            };

        int ans = 0;
        int before_row = 1;
        short cur_seat = 0;
        for (auto&& reserved : reservedSeats) {
            const auto row = reserved[0];
            if (row != before_row) {
                const auto free_count = row - before_row - 1;
                ans += free_count * 2;
                ans += get_count(cur_seat);

                before_row = row;
                cur_seat = 0;
            }
            cur_seat |= 1 << (reserved[1] - 1);
        }
        const auto free_count = n - before_row;
        ans += free_count * 2;
        ans += get_count(cur_seat);

        return ans;
    }
};
static void test(int n, vector<vector<int>>&& reservedSeats) {
    cout << Solution().maxNumberOfFamilies(n, reservedSeats) << endl;
}

int main() {
    test(3, get_matrix_int("[[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]"));
    test(2, get_matrix_int("[[2,1],[1,8],[2,6]]"));
    test(4, get_matrix_int("[[4,3],[1,4],[4,6],[1,7]]"));
    return 0;
}
