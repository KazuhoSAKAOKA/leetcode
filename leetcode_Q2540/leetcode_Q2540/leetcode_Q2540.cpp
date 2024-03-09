// leetcode_Q2540.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() || nums2.empty()) {
            return -1;
        }
        sort(begin(nums1), end(nums1));
        sort(begin(nums2), end(nums2));

        int index1 = 0;
        int index2 = 0;
        while (nums1[index1] != nums2[index2]) {
            if (nums1[index1] < nums2[index2]) {
                index1++;
                if (nums1.size() == index1) {
                    return - 1;
                }
            }
            else {
                index2++;
                if (nums2.size() == index2) {
                    return -1;
                }
            }
        }
        return nums1[index1];
    }
};

void test(vector<int>&& num1, vector<int>&& num2) {
    cout << Solution().getCommon(num1, num2) << endl;
}


int main()
{
    test({1,2,3}, {2,4});
    test({1,2,3,6}, {2,3,4,5});
}