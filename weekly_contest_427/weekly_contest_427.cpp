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
    vector<int> constructTransformedArray(vector<int>& nums) {
        const auto N = size(nums);
        vector<int> ans(N);

        for (int i = 0; i < N; i++) {
            if (nums[i] > 0) {
                ans[i] = nums[(i + nums[i]) % N];
            }
            else if (nums[i] < 0) {
                const auto n = -1 * static_cast<int>((abs(nums[i]) % N));
                ans[i] = nums[(N + i + n) % N];
            }
            else {
                ans[i] = nums[i];
            }
        }
        return ans;
    }
};
static void test(vector<int>&& nums) {
    output(Solution().constructTransformedArray(nums));
}
static void run() {
    test(get_list_int("[-1,4,-1]"));
    test(get_list_int("[-10,-10,-4]"));
    test(get_list_int("[3,-2,1,1]"));
    test(get_list_int("[-1,4,-1]"));
}
}


namespace problem2 {
class Solution {
public:
/*
    static         int maxRectangleArea1(vector<vector<int>>&points) {
            map<int, map<int, size_t>> x_ref_map;
            for (size_t index = 0; index < size(points); index++) {
                const auto point = points[index];
                const auto x = point.front();
                const auto y = point.back();
                x_ref_map[x][y] = index;
            }
            int max_area = -1;

            for (size_t index = 0; index < size(points); index++) {
                const auto point = points[index];
                const auto x = point.front();
                const auto y = point.back();

                auto next_x_it = x_ref_map.upper_bound(x);
                while (next_x_it != cend(x_ref_map)) {
                    if () { continue; }
                    auto& x_ref_map_target = x_ref_map[x];
                    const auto next_y_it = x_ref_map_target.upper_bound(y);
                    if (next_y_it == cend(x_ref_map_target)) { continue; }
                    const auto right = next_x_it->first;
                    const auto bottom = next_y_it->first;

                    const auto right_x_it = x_ref_map.find(right);
                    if (right_x_it == cend(x_ref_map)) { continue; }
                    const auto& right_bottom_map = right_x_it->second;
                    const auto bottom_y_it = right_bottom_map.find(bottom);
                    if (bottom_y_it == cend(right_bottom_map)) { continue; }
                    max_area = max(max_area, (right - x) * (bottom - y));


                    ++next_x_it;
                }
            }
    }
    */
    int maxRectangleArea(vector<vector<int>>& points) {
        map<int, set<size_t>> x_ref_map;
        map<int, set<size_t>> y_ref_map;
        for (size_t index = 0; index < size(points); index++) {
            const auto point = points[index];
            const auto x = point.front();
            const auto y = point.back();
            x_ref_map[x].insert(index);
            y_ref_map[y].insert(index);
        }
        int max_area = -1;
        for (int i = 0; i < size(points); i++) {
            const auto point = points[i];
            const auto x = point.front();
            const auto y = point.back();
            for (auto&& index_x : x_ref_map[x]) {
                if (index_x == i) { continue; }
                const auto other_y = points[index_x].back();
     
                const auto& y_ref_map_cur = y_ref_map[y];
                const auto& y_ref_map_other = y_ref_map[other_y];
                if (size(y_ref_map_cur) > 1 && size(y_ref_map_other) > 1) {
                    for (auto&& y_index1 : y_ref_map_cur) {
                        if (y_index1 == i) { continue; }
                        for (auto&& y_index2 : y_ref_map_other) {
                            if (y_index2 == index_x) { continue; }
                            if (points[y_index2].front() == points[y_index1].front()) {
                                const auto other_x = points[y_index2].front();
                                const int left = min(x, other_x);
                                const int right = max(x, other_x);
                                const int bottom = min(y, other_y);
                                const int top = max(y, other_y);
                                bool contains = false;
                                for (int check_index = 0; check_index < size(points); check_index++) {
                                    if (check_index == i || check_index == index_x || check_index == y_index1 || check_index == y_index2) {
                                        continue;
                                    }
                                    const auto check_x = points[check_index].front();
                                    const auto check_y = points[check_index].back();
                                    if (
                                        (left <= check_x && check_x <= right) && (bottom <= check_y && check_y <= top)
                                        ) {
                                        contains = true;
                                        break;
                                    }
                                }
                                if (!contains) {
                                    max_area = max(max_area, (right - left) * (top - bottom));
                                }
                            }
                        }
                    }
                }
            }
        }

        return max_area;
    }
};
void test(vector<vector<int>>&& points) {
    cout << Solution().maxRectangleArea(points) << endl;
}
static void run() {
    test(get_matrix_int("[[96,44],[23,72],[96,72],[23,44],[65,44]]"));
    test(get_matrix_int("[[1,1],[1,3],[3,1],[3,3]]"));
    test(get_matrix_int("[[100,80],[67,79],[100,79],[67,80],[80,47]]"));
    test(get_matrix_int("[[1,1],[1,3],[3,1],[3,3],[2,2]]"));
    test(get_matrix_int("[[1,1],[1,3],[3,1],[3,3],[1,2],[3,2]]"));
}
}
namespace problem3 {
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        vector<long long> prefix_sums(size(nums) + 1);
        for (int i = 0; i < size(nums); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + static_cast<long long>(nums[i]);
        }
        long long max_sum = LLONG_MIN;
        for (int i = 0; i < size(nums); i++) {
            for (int j = i + k; j <= size(nums); j += k) {
                max_sum = max(max_sum, prefix_sums[j] - prefix_sums[i]);
            }
        }
        return max_sum;
    }
}; 
static void test(vector<int>&& nums, int k) {
    cout << Solution().maxSubarraySum(nums, k) << endl;
}
static void run() {
    test(get_list_int("[8]"), 1);
    test(get_list_int("[1,2]"), 1);
    test(get_list_int("[-1,-2,-3,-4,-5]"), 4);
    test(get_list_int("[-5,1,2,-3,4]"), 2);
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