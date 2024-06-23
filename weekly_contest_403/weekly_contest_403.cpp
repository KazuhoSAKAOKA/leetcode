// weekly_contest_403.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {

class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        sort(begin(nums), end(nums));

        double min_value = DBL_MAX;

        for (int i = 0; i < nums.size() / 2; i++) {
            const double v = (static_cast<double>(nums[i]) + static_cast<double>(nums[nums.size() - 1 - i])) / 2.0;
            min_value = min(min_value, v);
        }
        return min_value;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().minimumAverage(nums) << endl;
}
void run() {
    test(get_list_int("[7,8,3,4,15,13,4,1]"));
    test(get_list_int("[1,9,8,3,10,5]"));
    test(get_list_int("[1,2,3,7,8,9]"));
}
}
namespace problem2 {
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int min_x = INT_MAX;
        int min_y = INT_MAX;
        int max_x = 0;
        int max_y = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.front().size(); j++) {
                if (grid[i][j] == 1) {
                    min_x = min(min_x, j);
                    min_y = min(min_y, i);
                    max_x = max(max_x, j);
                    max_y = max(max_y, i);
                }
            }
        }
        return (max_x - min_x + 1) * (max_y - min_y + 1);
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().minimumArea(grid) << endl;
}
void run() {
    test(get_matrix_int("[[0,1,0],[1,0,1]]"));
    test(get_matrix_int("[[0,0],[1,0]]"));
}
}
namespace problem3 {
class Solution {
public:
    long long maximumTotalCost(vector<int>& nums) {
        long long before_norm = nums[0];
        long long before_rev = LONG_MIN;
        for (int i = 1; i < nums.size(); i++) {
            long long current_norm = max(before_norm, before_rev) + nums[i];
            long long current_rev = before_norm - nums[i];

            before_norm = current_norm;
            before_rev = current_rev;
        }

        return max(before_norm, before_rev);
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maximumTotalCost(nums) << endl;
}
void run() {
    test(get_list_int("[-1,-2,-3,-4]"));
    test(get_list_int("[1,-2,3,4]"));
    test(get_list_int("[1,-1,1,-1]"));
    test(get_list_int("[0]"));
    test(get_list_int("[1,-1]"));
}
}
namespace problem4 {
class Solution {
public:

    static int get_sum(const vector<vector<int>>& prefix_sums, int y0, int x0, int y1, int x1) {
        return prefix_sums[y1][x1] - prefix_sums[y0][x1] - prefix_sums[y1][x0] + prefix_sums[y0][x0];
    }

    static tuple<bool, int, int> rec(const vector<vector<int>>& prefix_sums, int y_begin, int x_begin, int y_end, int x_end, int remain_split) {

        const int current_target = get_sum(prefix_sums, y_begin, x_begin, y_end, x_end);
        if (current_target == 0) {
            return { false,0,0 };
        }
        bool succeed = false;
        int min_area = INT_MAX;
        for (int y = y_begin; y < y_end; y++) {
            for (int x = x_begin; x < x_end; x++) {
                for (int y1 = y + 1; y1 <= y_end; y1++) {
                    for (int x1 = x + 1; x1 <= x_end; x1++) {
                        const int current_sum = get_sum(prefix_sums, y, x, y1, x1);
                        if (current_sum == 0) { continue; }
                        const int current_size = (y1 - y) * (x1 - x);
                        if (remain_split > 1) {
                            if (remain_split > 2) {
                                {
                                    auto [r, size, a] = rec(prefix_sums, y1, x_begin, y_end, x_end, 1);
                                    if (r) {
                                        auto [r1, size1, a1] = rec(prefix_sums, y_begin, x1, y1, x_end, 1);
                                        if (r1 && (current_sum + a + a1) == current_target) {
                                            succeed = true;
                                            min_area = min(min_area, current_size + size + size1);
                                        }
                                    }
                                }
                                {
                                    auto [r, size, a] = rec(prefix_sums, y_begin, x1, y_end, x_end, 1); 
                                    if (r) {
                                        auto [r1, size1, a1] = rec(prefix_sums, y1, x_begin, y_end, x1, 1);
                                        if (r1 && (current_sum + a + a1) == current_target) {
                                            succeed = true;
                                            min_area = min(min_area, current_size + size + size1);
                                        }
                                    }
                                }
                            }

                            {
                                auto [r, s, a] = rec(prefix_sums, y1, x_begin, y_end, x_end, remain_split - 1);
                                if (r && current_sum + a == current_target) {
                                    succeed = true;
                                    min_area = min(min_area, current_size + s);
                                }
                            }
                            {
                                auto [r, s, a] = rec(prefix_sums, y_begin, x1, y_end, x_end, remain_split - 1);
                                if (r && current_sum + a == current_target) {
                                    succeed = true;
                                    min_area = min(min_area, current_size + s);
                                }
                            }

                        }
                        else if (remain_split == 1) {
                            if (current_sum == current_target) {
                                succeed = true;
                                min_area = min(min_area, current_size);
                            }
                        }
                    }
                }
            }
        }
        if (succeed) {
            return { succeed , min_area, current_target };

        }
        else {
            return { false , 0,0 };
        }
    }


    static int tle(vector<vector<int>>& grid) {
        int min_x = INT_MAX;
        int min_y = INT_MAX;
        int max_x = 0;
        int max_y = 0;

        vector<vector<int>> prefix_sums(grid.size() + 1, vector<int>(grid.front().size() + 1, 0));

        const int H = grid.size();
        const int W = grid.front().size();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + grid[i][j];
                if (grid[i][j] == 1) {
                    min_x = min(min_x, j);
                    min_y = min(min_y, i);
                    max_x = max(max_x, j);
                    max_y = max(max_y, i);
                }
            }
        }

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto [a, b, c] = rec(prefix_sums, min_y, min_x, max_y + 1, max_x + 1, 3);

        return b;
    }

    static int rec2(const vector<vector<int>>& grid, int y_begin, int x_begin, int y_end, int x_end, int remain_split) {
        if (remain_split == 1) {
            int min_x = INT_MAX;
            int min_y = INT_MAX;
            int max_x = 0;
            int max_y = 0;
            int count = 0;
            for (int y = y_begin; y < y_end; y++) {
                for (int x = x_begin; x < x_end; x++) {
                    if (grid[y][x] == 1) {
                        min_x = min(min_x, x);
                        min_y = min(min_y, y);
                        max_x = max(max_x, x);
                        max_y = max(max_y, y);
                        count++;
                    }
                }
            }
            return count > 0 ? (max_y - min_y + 1) * (max_x - min_x + 1) : INT_MAX / 3;
        }
        int min_area = INT_MAX;
        for (int y1 = y_begin + 1; y1 < y_end; y1++) {
            if (remain_split == 3) {
                const auto up1 = rec2(grid, y_begin, x_begin, y1, x_end, 2);
                const auto down1 = rec2(grid, y1, x_begin, y_end, x_end, 1);

                const auto up2 = rec2(grid, y_begin, x_begin, y1, x_end, 1);
                const auto down2 = rec2(grid, y1, x_begin, y_end, x_end, 2);
                const auto temp_min = min(up1 + down1, up2 + down2);
                min_area = min(min_area, temp_min);
            }
            else {
                const auto up = rec2(grid, y_begin, x_begin, y1, x_end, 1);
                const auto down = rec2(grid, y1, x_begin, y_end, x_end, 1);
                min_area = min(min_area, up + down);
            }
        }
        for (int x1 = x_begin + 1; x1 < x_end; x1++) {
            if (remain_split == 3) {
                const auto up1 = rec2(grid, y_begin, x_begin, y_end, x1, 2);
                const auto down1 = rec2(grid, y_begin, x1, y_end, x_end, 1);

                const auto up2 = rec2(grid, y_begin, x_begin, y_end, x1, 1);
                const auto down2 = rec2(grid, y_begin, x1, y_end, x_end, 2);
                const auto temp_min = min(up1 + down1, up2 + down2);
                min_area = min(min_area, temp_min);
            }
            else {
                const auto up = rec2(grid, y_begin, x_begin, y_end, x1, 1);
                const auto down = rec2(grid, y_begin, x1, y_end, x_end, 1);
                min_area = min(min_area, up + down);
            }
        }
        return min_area;
    }

    int minimumSum(vector<vector<int>>& grid) {
        return rec2(grid, 0, 0, grid.size(), grid.front().size(), 3);
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().minimumSum(grid) << endl;
}
void run() {
    test(get_matrix_int("[[1,0,1],[1,1,1]]"));
    test(get_matrix_int("[[1,0,1,0],[0,1,0,1]]"));
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}