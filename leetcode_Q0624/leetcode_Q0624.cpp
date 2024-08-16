// leetcode_Q0624.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <climits>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int max_value = INT_MIN;
        int second_max_value = INT_MIN;
        int min_value = INT_MAX;
        int second_min_value = INT_MAX;
        
        size_t max_index = static_cast<size_t>(-1);
        size_t min_index = static_cast<size_t>(-1);
        for (size_t index = 0; index < size(arrays); index++) {
            const auto& cur_min = arrays[index].front();
            if (cur_min < min_value) {
                second_min_value = min_value;
                min_value = cur_min;
                min_index = index;
            }
            else if (cur_min < second_min_value) {
                second_min_value = cur_min;
            }

            const auto& cur_max = arrays[index].back();
            if (max_value < cur_max) {
                second_max_value = max_value;
                max_value = cur_max;
                max_index = index;
            }
            else if (second_max_value < cur_max) {
                second_max_value = cur_max;
            }
        }
        if (max_index != min_index) {
            return max_value - min_value;
        }
        return max(max_value - second_min_value, second_max_value - min_value);
    }
};

void test(vector<vector<int>>&& arrays) {
    cout << Solution().maxDistance(arrays) << endl;
}

int main()
{
    test(get_matrix_int("[[1,100],[1,100],[5,6,7]]"));
    test(get_matrix_int("[[1,2,3],[4,5],[1,2,3]]"));
    test(get_matrix_int("[[1],[1]]"));
    return 0;
}