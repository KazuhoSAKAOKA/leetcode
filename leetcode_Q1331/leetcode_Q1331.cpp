// leetcode_Q1331.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        set<int> exist_set(cbegin(arr), cend(arr));
        unordered_map<int, int> rev_map;
        int rank = 1;
        for (auto&& value : exist_set) {
            rev_map[value] = rank;
            rank++;
        }
        vector<int> ans;
        ans.reserve(size(arr));
        for (auto&& value : arr) {
            ans.emplace_back(rev_map[value]);
        }
        return ans;
    }
};

void test(vector<int>&& arr) {
    output(Solution().arrayRankTransform(arr));
}
int main()
{
    test(get_list_int("[40,10,20,30]"));
    test(get_list_int("[100,100,100]"));
    test(get_list_int("[37,12,28,9,100,56,80,5,12]"));
    return 0;
}