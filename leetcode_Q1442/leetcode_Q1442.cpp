// leetcode_Q1442.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <numeric>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:

    int countTriplets(vector<int>& arr) {
        vector<vector<int>> before;
        before.push_back({ arr[0] });
        int result = 0;
        for (int i = 1; i < arr.size(); i++) {
            vector<vector<int>> current;
            for (auto&& ss: before) {
                ss.emplace_back(arr[i]);
                if (accumulate(cbegin(ss), cend(ss), 0, [](const auto& a, const auto& b) { return a ^ b; }) == 0) {
                    int a = 0;
                    for (int i1 = 0; i1 < ss.size() - 1; i1++) {
                        a = a ^ ss[i1];
                        int b = 0;
                        for (int j1 = i1 + 1; j1 < ss.size(); j1++) {
                            b = b ^ ss[j1];
                        }
                        if (a == b) {
                            result++;
                        }
                    }
                }
                current.emplace_back(ss);
            }
            current.push_back({ arr[i] });
            before = current;
        }

        return result;
    }
};

void test(vector<int>&& arr) {
    cout << Solution().countTriplets(arr) << endl;
}

int main()
{
    test(get_list_int("[2,3,1,6,7]"));
    test(get_list_int("[1,1,1,1,1]"));
}