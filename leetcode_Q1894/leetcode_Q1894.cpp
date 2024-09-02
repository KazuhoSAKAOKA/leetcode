// leetcode_Q1894.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        const auto total = accumulate(cbegin(chalk), cend(chalk), 0LL);
        auto current = k % total;
        for (int i = 0; i < size(chalk); i++) {
            if (current < chalk[i]) {
                return i;
            }
            current -= chalk[i];
        }
        return size(chalk);
    }
};

void test(vector<int>&& chalk, int k) {
    cout << Solution().chalkReplacer(chalk, k) << endl;
}

int main()
{
    test(get_list_int("[5,1,5]"), 22);
    test(get_list_int("[3,4,1,2]"), 25);
    return 0;
}