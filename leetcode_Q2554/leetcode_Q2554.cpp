// leetcode_Q2554.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include <vector>
#include <set>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        long long cur_sum = 0;
        set<int> banned_set;
        for (auto&& value : banned) {
            banned_set.insert(value);
        }
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (banned_set.count(i) == 0) {
                cur_sum += i;
                if (maxSum < cur_sum) {
                    break;
                }
                count++;
            }
        }
        return count;
    }
};

void test(vector<int>&& banned, int n, int maxSum) {
    cout << Solution().maxCount(banned, n, maxSum) << endl;
}

int main()
{
    test(get_list_int("[1,6,5]"), 5, 6);
    test(get_list_int("[1, 2, 3, 4, 5, 6, 7]"), 8, 1);
    test(get_list_int("[11]"), 7, 50);
    return 0;
}