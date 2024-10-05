// leetcode_Q2491.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        sort(begin(skill), end(skill));
        long long sum_skill = static_cast<long long>(skill[0]) + static_cast<long long>(skill[size(skill) - 1]);
        long long ans = static_cast<long long>(skill[0]) * static_cast<long long>(skill[size(skill) - 1]);

        for (size_t i = 1; i < size(skill) / 2; i++) {
            if (static_cast<long long>(skill[i]) + static_cast<long long>(skill[size(skill) - i - 1]) != sum_skill) {
                return -1;
            };
            ans += static_cast<long long>(skill[i]) * static_cast<long long>(skill[size(skill) - i - 1]);
        }


        return ans;
    }
};

void test(vector<int>&& skill) {
    cout << Solution().dividePlayers(skill) << endl;
}


int main()
{
    test(get_list_int("[3,2,5,1,3,4]"));
    test(get_list_int("[3,4]"));
    test(get_list_int("[1,1,2,3]"));
    return 0;
}