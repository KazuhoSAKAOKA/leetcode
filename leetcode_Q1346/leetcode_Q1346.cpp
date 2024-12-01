// leetcode_Q1346.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        map<int, int> freqs;
        for (auto&& num : arr) { freqs[num]++; }
        return any_of(cbegin(arr), cend(arr), [&](const auto a) {
            const auto m2 = a * 2;
            const auto it = freqs.find(m2);
            if (it == cend(freqs)) { return false; }
            if (a == m2) {
                return it->second > 1;
            }
            return true;
            });
    }
};

void test(vector<int>&& arr) {
    cout << Solution().checkIfExist(arr) << endl;
}
int main()
{
    test(get_list_int("[0,1,3]"));
    test(get_list_int("[0,0,1,3]"));
    test(get_list_int("[10,2,5,3]"));
    test(get_list_int("[3,1,7,11]"));
    return 0;
}