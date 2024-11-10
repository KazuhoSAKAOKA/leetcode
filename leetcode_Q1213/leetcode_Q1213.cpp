// leetcode_Q1213.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        vector<int> ans;

        int arr1index = 0;
        int arr2index = 0;
        int arr3index = 0;

        while (arr1index < size(arr1) && arr2index < size(arr2) && arr3index < size(arr3)) {
            const auto v1 = arr1[arr1index];
            const auto v2 = arr2[arr2index];
            const auto v3 = arr3[arr3index];
            if (v1 == v2 && v2 == v3) {
                ans.emplace_back(v1);
                arr1index++;
                arr2index++;
                arr3index++;
                continue;
            }
            if (v1 < v2) {
                if (v1 < v3) {
                    arr1index++;
                }
                else {
                    arr3index++;
                }
            }
            else {
                if (v2 < v3) {
                    arr2index++;
                }
                else {
                    arr3index++;
                }
            }
        }

        return ans;
    }
};

void test(vector<int>&& arr1, vector<int>&& arr2, vector<int>&& arr3) {
    output(Solution().arraysIntersection(arr1, arr2, arr3));
}
int main()
{
    test(get_list_int("[1,2,3,4,5]"), get_list_int("[1,2,5,7,9]"), get_list_int("[1,3,4,5,8]"));
    test(get_list_int("[197,418,523,876,1356]"), get_list_int("[501,880,1593,1710,1870]"), get_list_int("[521,682,1337,1395,1764]"));
    return 0;
}
