// leetcode_Q0080.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int fast_index = 1;
        int slow_index = 0;
        int completion_count = 0;
        while (fast_index < nums.size()) {
            if (nums[fast_index] == nums[slow_index]) {
                fast_index++;
            }
            else {
                if (fast_index == slow_index + 1) {
                    swap(nums[completion_count], nums[slow_index]);
                    completion_count++;
                    fast_index++;
                    slow_index++;
                }
                else {
                    swap(nums[completion_count], nums[slow_index]);
                    swap(nums[completion_count + 1], nums[slow_index + 1]);
                    completion_count += 2;
                    slow_index = fast_index;
                    fast_index++;
                }
            }
        }
        if (fast_index == slow_index + 1) {
            swap(nums[completion_count], nums[slow_index]);
            completion_count++;
        }
        else {
            swap(nums[completion_count], nums[slow_index]);
            swap(nums[completion_count + 1], nums[slow_index + 1]);
            completion_count += 2;
        }
        return completion_count;
    }
};


void test(vector<int>&& nums) {
    const auto k = Solution().removeDuplicates(nums);
    for (auto i = 0; i < k; i++) {
        cout << nums[i] << ",";
    }
    cout << endl;
}

int main()
{
    test({ 1,1,1,2,2,3 });
    test({ 0,0,1,1,1,1,2,3,3 });
    test({ 9, });
    test({ 9, 10, });
    test({ 9, 9, });
}