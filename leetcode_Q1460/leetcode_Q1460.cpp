// leetcode_Q1460.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> target_freq;
        for (auto&& value : target) {
            target_freq[value]++;
        }
        for (auto&& value : arr) {
            target_freq[value]--;
        }
        return all_of(cbegin(target_freq), cend(target_freq), [](const auto& p) { return p.second == 0; });
    }
};

void test(vector<int>&& target, vector<int>&& arr) {
    cout << Solution().canBeEqual(target, arr) << endl;
}


int main()
{
    test(get_list_int("[1,2,3,4]"), get_list_int("[2,4,1,3]"));
    test(get_list_int("[7]"), get_list_int("[7]"));
    test(get_list_int("[3,7,9]"), get_list_int("[3,7,11]"));
    return 0;
}