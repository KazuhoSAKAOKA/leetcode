// leetcode_Q0026.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    static void front_joint(vector<int>& nums, size_t index, size_t size)
    {
        for (size_t i = index; i < size - 1; i++)
        {
            nums[i] = nums[i + 1];
        }
    }


    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) { return 0; }
        size_t size = nums.size();
        int before = nums[0];

        size_t last_index = size - 1;
        for (size_t i = 1; i < size;)
        {
            if (before == nums[i])
            {
                front_joint(nums, i, size);
                size--;
            }
            else
            {
                before = nums[i];
                i++;
            }
        }

        return static_cast <int>(size);
    }

};


int main()
{
    vector<int> a1{ 1,1,2, };
    //vector<int> a1{ 0,0,1,1,1,2,2,3,3,4,};
    const auto num = Solution().removeDuplicates(a1);
    for (auto i = 0; i < num; i++)
    {
        std::cout << a1[i] << std::endl;
    }
}

