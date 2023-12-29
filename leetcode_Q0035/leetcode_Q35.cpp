// leetcode_Q35.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        const auto it = lower_bound(cbegin(nums), cend(nums), target);
        return static_cast<int>(distance(cbegin(nums), it));
    }
};
int main()
{
    //vector<int> nums{ 1, 3, 5, 6 };
    //const int target = 5;

    //vector<int> nums{ 1, 3, 5, 6 };
    //const int target = 2;

    vector<int> nums{ 1, 3, 5, 6 };
    const int target = 7;


    const auto num = Solution().searchInsert(nums, target);
    std::cout << num << std::endl;
}

