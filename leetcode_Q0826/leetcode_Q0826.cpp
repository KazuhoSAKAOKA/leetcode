// leetcode_Q0826.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        sort(begin(worker), end(worker));
        using P = pair<int, int>;
        vector<P> difficulty_profits(difficulty.size());
        for (int i = 0; i < difficulty.size(); i++) {
            difficulty_profits[i] = { difficulty[i], profit[i] };
        }
        sort(begin(difficulty_profits), end(difficulty_profits));


        int index = 0;
        int total_profit = 0;
        int current_difficulty = difficulty_profits[index].first;
        int current_profit = difficulty_profits[index].second;

        for (auto&& ability: worker) {
            if (ability < current_difficulty) {
                continue;
            }
            while (index < difficulty_profits.size() && difficulty_profits[index].first <= ability) {
                current_profit = max(current_profit, difficulty_profits[index].second);
                current_difficulty = difficulty_profits[index].first;
                index++;
            }
            total_profit += current_profit;
        }

        return total_profit;
    }
};
void test(vector<int>&& difficulty, vector<int>&& profit, vector<int>&& worker) {
    cout << Solution().maxProfitAssignment(difficulty, profit, worker) << endl;
}
int main()
{
    test(get_list_int("[5,50,92,21,24,70,17,63,30,53]"), get_list_int("[68,100,3,99,56,43,26,93,55,25]"), get_list_int("[96,3,55,30,11,58,68,36,26,1]"));
    test(get_list_int("[2,4,6,8,10]"), get_list_int("[10,20,30,40,50]"), get_list_int("[4,5,6,100]"));
    test(get_list_int("[2,4,6,8,10]"), get_list_int("[10,20,30,40,50]"), get_list_int("[4,5,6,7]"));
    test(get_list_int("[85,47,57]"), get_list_int("[24,66,99]"), get_list_int("[40,25,25]"));
}