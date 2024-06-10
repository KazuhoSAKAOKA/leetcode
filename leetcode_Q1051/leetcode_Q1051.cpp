// leetcode_Q1051.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> correct(heights);
        sort(begin(correct), end(correct));

        int total = 0;
        for (size_t index = 0; index < heights.size(); index++) {
            if (correct[index] != heights[index]) {
                total++;
            }
        }
        return total;
    }
};

void test(vector<int>&& heights) {
    cout << Solution().heightChecker(heights) << endl;
}

int main()
{
    test(get_list_int("[1,1,4,2,1,3]"));
    test(get_list_int("[5,1,2,3,4]"));
    test(get_list_int("[1,2,3,4,5]"));
}