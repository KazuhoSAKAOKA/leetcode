// leetcode_Q1133.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int largestUniqueNumber(vector<int>& nums) {
        map<int, size_t> freq_map;
        for (auto&& num : nums) {
            freq_map[num]++;
        }
        for (auto it = crbegin(freq_map); it != crend(freq_map); ++it) {
            if (it->second == 1) {
                return it->first;
            }
        }
        return -1;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().largestUniqueNumber(nums) << endl;
}
int main()
{
    test(get_list_int("[5,7,3,9,4,9,8,3,1]"));
    test(get_list_int("[9,9,8,8]"));
    return 0;
}