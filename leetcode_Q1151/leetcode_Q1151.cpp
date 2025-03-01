// leetcode_Q1151.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <numeric>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& data) {
        const int ones = accumulate(cbegin(data), cend(data), 0);
        int cur_ones = 0;
        for (int i = 0; i < ones; i++) {
            cur_ones += data[i];
        }
        int max_ones = cur_ones;
        for (int i = ones; i < size(data); i++) {
            cur_ones += data[i];
            cur_ones -= data[i - ones];
            max_ones = max(max_ones, cur_ones);
        }
        return ones - max_ones;
    }
};

void test(vector<int>&& data) {
    cout << Solution().minSwaps(data) << endl;
}

int main()
{
    test(get_list_int("[1,0,1,0,1,0,0,1,1,0,1]"));
    test(get_list_int("[1,0,1,0,1]"));
    test(get_list_int("[0,0,0,1,0]"));
    return 0;
}