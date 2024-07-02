// leetcode_Q0350.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> freq_map;
        for (auto&& value : nums1) {
            freq_map[value]++;
        }
        vector<int> ans;
        for (auto&& value : nums2) {
            const auto it = freq_map.find(value);
            if (it != cend(freq_map) && it->second > 0) {
                it->second--;
                ans.emplace_back(value);
            }
        }
        return ans;
    }
};

void test(vector<int>&& nums1, vector<int>&& nums2) {
    const auto ans = Solution().intersect(nums1, nums2);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test(get_list_int("[1,2,2,1]"), get_list_int("[2,2]"));
    test(get_list_int("[4,9,5]"), get_list_int("[9,4,9,8,4]"));
}