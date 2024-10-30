// leetcode_0265.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int most_min_cost = 0;
        int min_cost_index = -1;
        int second_min_cost = 0;
        for (int i = 0; i < size(costs); i++) {
            int current_min = INT_MAX;
            int current_min_index = -1;
            int second_min = INT_MAX;
            for (int j = 0; j < size(costs[i]); j++) {
                int cost;
                if (min_cost_index != j) {
                    cost = most_min_cost + costs[i][j];
                }
                else {
                    cost = second_min_cost + costs[i][j];
                }
                if (cost < current_min) {
                    second_min = current_min;
                    current_min = cost;
                    current_min_index = j;
                }
                else if(cost < second_min){
                    second_min = cost;
                }
            }
            most_min_cost = current_min;
            min_cost_index = current_min_index;
            second_min_cost = second_min;
        }
        return most_min_cost;
    }
};

void test(vector<vector<int>>&& costs) {
    cout << Solution().minCostII(costs) << endl;
}
int main()
{
    test(get_matrix_int("[[1,5,3],[2,9,4]]"));
    test(get_matrix_int("[[1,3],[2,4]]"));
    return 0;
}

