// leetcode_Q0075.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        size_t num_counts[3]{ 0,0,0, };
        for (auto&& value : nums) {
            num_counts[value]++;
        }
        const auto num2 = num_counts[0] + num_counts[1];
        for (size_t i = 0; i < nums.size(); i++) {
            nums[i] = i < num_counts[0] ? 0 : i < num2 ? 1 : 2;
        }
    }
};

void test(vector<int>&& nums) {
    Solution().sortColors(nums);
    for (auto&& value : nums) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test({ 2,0,2,1,1,0, });
    test({2,0,1,});

}

