// leetcode_Q0260.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int, int> freq_map;
        for (auto&& value : nums) {
            freq_map[value]++;
            if (freq_map[value] == 2) {
                freq_map.erase(value);
            }
        }
        vector<int> ans;
        for (auto&& [k, _] : freq_map) {
            ans.push_back(k);
        }
        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().singleNumber(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
int main()
{
    test(get_list_int("[1,2,1,3,2,5]"));
    test(get_list_int("[-1,0]"));
    test(get_list_int("[0,1]"));
}