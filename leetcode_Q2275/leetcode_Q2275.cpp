// leetcode_Q2275.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        int max_combinations = 0;
        vector<int> max_vals(32);
        for (auto&& num : candidates) {
            for (int i = 0; i < 32; i++) {
                if ((num & (1 << i)) != 0) {
                    max_vals[i]++;
                    max_combinations = max(max_combinations, max_vals[i]);
                }
            }
        }
        return max_combinations;
    }
};
void test(vector<int>&& candidates) {
    cout << Solution().largestCombination(candidates) << endl;
}
int main()
{
    test(get_list_int("[16,17,71,62,12,24,14]"));
    test(get_list_int("[8,8]"));
    return 0;
}