// leetcode_Q1014.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int max_score = 0;
        int top_to_end_best = values[0];
        int end_to_top_best = values[size(values) - 1];
        for (int i = 1; i < size(values); i++) {
            top_to_end_best--;
            max_score = max(max_score, values[i] + top_to_end_best);
            top_to_end_best = max(top_to_end_best, values[i]);

            end_to_top_best--;
            max_score = max(max_score, values[size(values) - i - 1] + end_to_top_best);
            end_to_top_best = max(end_to_top_best, values[size(values) - i - 1]);
        }
        return max_score;
    }
};

void test(vector<int>&& values) {
    cout << Solution().maxScoreSightseeingPair(values) << endl;
}

int main()
{
    test(get_list_int("[8,1,5,2,6]"));
    test(get_list_int("[1,2]"));
    return 0;
}