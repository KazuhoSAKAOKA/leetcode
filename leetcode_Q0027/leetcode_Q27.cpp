// leetcode_Q27.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        size_t size = nums.size();

        for (size_t i = 0; i < size;)
        {
            if (nums[i] == val)
            {
                swap(nums[i], nums[size - 1]);
                size--;
            }
            else
            {
                i++;
            }
        }

        return static_cast<size_t>(size);
    }
};


int main()
{
    //vector<int> nums{ 3,2,2,3, };
    vector<int> nums{ 0,1,2,2,3,0,4,2 };
    const auto n = Solution().removeElement(nums, 3);
    for (size_t i = 0; i < n; i++)
    {
        std::cout << nums[i] << std::endl;
    }
}

