// leetcode_Q2570.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        vector<vector<int>> ans;
        int index1 = 0;
        int index2 = 0;

        while (index1 < size(nums1) || index2 < size(nums2)) {
            if (index1 < size(nums1) && index2 < size(nums2)) {
                const auto& num1 = nums1[index1];
                const auto& num2 = nums2[index2];
                if (num1.front() == num2.front()) {
                    ans.emplace_back(vector<int>{num1.front(), num1.back() + num2.back()});
                    index1++;
                    index2++;
                }
                else {
                    if (num1.front() < num2.front()) {
                        ans.emplace_back(vector<int>{num1.front(), num1.back()});
                        index1++;
                    }
                    else {
                        ans.emplace_back(vector<int>{num2.front(), num2.back()});
                        index2++;
                    }
                }
            }
            else {
                if (index1 < size(nums1)) {
                    while (index1 < size(nums1)) {
                        const auto& num1 = nums1[index1];
                        ans.emplace_back(vector<int>{num1.front(), num1.back()});
                        index1++;
                    }
                }
                else {
                    while (index2 < size(nums2)) {
                        const auto& num2 = nums2[index2];
                        ans.emplace_back(vector<int>{num2.front(), num2.back()});
                        index2++;
                    }
                }
            }
        }


        return ans;
    }
};

void test(vector<vector<int>>&& nums1, vector<vector<int>>&& nums2) {
    output_matrix(Solution().mergeArrays(nums1, nums2));
}
int main() {
    test(get_matrix_int("[[1,2],[2,3],[4,5]]"), get_matrix_int("[[1,4],[3,2],[4,1]]"));
    test(get_matrix_int("[[2,4],[3,6],[5,5]]"), get_matrix_int("[[1,3],[4,3]]"));
    return 0;
}