// leetcode_Q1122.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> pos_map;
        for (int i = 0; i < arr2.size(); i++) {
            pos_map[arr2[i]] = i;
        }

        sort(begin(arr1), end(arr1), [&](const auto& a, const auto& b) {
            const auto it_a = pos_map.find(a);
            const auto it_b = pos_map.find(b);
            if (it_a == cend(pos_map) && it_b == cend(pos_map)) {
                return a < b;
            }
            if (it_a == cend(pos_map)) {
                return false;
            }
            if (it_b == cend(pos_map)) {
                return true;
            }
            return it_a->second < it_b->second;
            });

        return arr1;
    }
};

void test(vector<int>&& arr1, vector<int>&& arr2) {
    const auto ans = Solution().relativeSortArray(arr1, arr2);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
int main()
{
    test(get_list_int("[2,1,55,44]"), get_list_int("[1,2]"));

    test(get_list_int("[2,3,1,3,2,4,6,7,9,2,19]"), get_list_int("[2,1,4,3,9,6]"));
    test(get_list_int("[28,6,22,8,44,17]"), get_list_int("[22,28,8,6]"));
}