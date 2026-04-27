
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
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        const auto n = size(heights);
        vector<int> water_levels(heights);
        auto cur_vol(volume);
        int left = k;
        int right = k;
        while (cur_vol > 0) {
            auto cur_level = water_levels[k];

        }



        return water_levels;
    }
};

static void test(vector<int>&& heights, int volume, int k) {
    output(Solution().pourWater(heights, volume, k));
}
int main() {
    test(get_list_int(""),,);
    test(get_list_int(""));
    test(get_list_int(""));
    return 0;
}