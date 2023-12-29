// leetcode_Q0088.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:

    int get_val(vector<int>& nums1, int& index_1, vector<int>& nums2, int& index_2) {
        if (0 <= index_1 && 0 <= index_2) {
            if (nums1[index_1] < nums2[index_2]) {
                return nums2[index_2--];
            }
            return nums1[index_1--];
        }
        if (0 <= index_1) {
            return nums1[index_1--];
        }
        return nums2[index_2--];
    }


    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index_1 = m - 1;
        int index_2 = n - 1;

        for(int index = m + n -1; index >= 0; index--){
            nums1[index] = get_val(nums1, index_1, nums2, index_2);
        }
    }
};
int main()
{
    std::vector<int> num1{ 1, 2, 3, 0, 0, 0 };
    std::vector<int> num2{ 2, 5, 6 };

    Solution().merge(num1, 3, num2, 3);

    for (auto&& v : num1)
    {
        std::cout << v << ",";
    }
    std::cout << std::endl;

    std::vector<int> num3{ 1 };
    std::vector<int> num4{  };
    Solution().merge(num3, 1, num4, 0);

    std::vector<int> num5{ 0 };
    std::vector<int> num6{ 2 };
    Solution().merge(num5, 0, num6, 1);
}

