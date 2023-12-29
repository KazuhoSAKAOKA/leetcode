// leetcode_Q0033.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:

    int binary_search(const vector<int>& nums, int target, int left, int right) {
        while (left <= right) {
            auto current_index = left + (right - left) / 2;
            if (nums[current_index] == target) {
                return current_index;
            }
            if (nums[current_index] < target) {
                left = current_index + 1;
            }
            else {
                right = current_index - 1;
            }
        }
        return -1;
    }



    int search(vector<int>& nums, int target) {
        if (nums.empty()) { return -1; }
        if (nums.size() == 1) { return nums[0] == target ? 0 : -1; }
        int left = 0;
        int right = nums.size() - 1;

        const int left_val = nums[left];
        const int right_val = nums[right];
        if (left_val == target) { return left; }
        if (right_val == target) { return right; }

        if (left_val < right_val) { return binary_search(nums, target, left, right); }
        if (right_val < target && target < left_val) { return -1; }
        const bool exist_front_section = left_val < target;

        while (left <= right && 0 <= left && right < nums.size()) {
            auto current_index = left + (right - left) / 2;
            if (nums[current_index] == target) {
                return current_index;
            }
            if (nums[current_index] < target) {
                if (exist_front_section) {
                    if (nums[current_index] < left_val) {
                        right = current_index - 1;
                    }
                    else {
                        left = current_index + 1;
                    }
                }
                else {
                    return binary_search(nums, target, current_index + 1, right);
                }
            }
            else {
                if (exist_front_section) {
                    return binary_search(nums, target, left, current_index - 1);
                }
                else {
                    if (right_val < nums[current_index]) {
                        left = current_index + 1;
                    }
                    else {
                        right = current_index - 1;
                    }
                }
            }
        }
        return -1;
    }
};

void test(vector<int>&& nums, int target)
{
    cout << Solution().search(nums, target) << endl;
}

int main()
{
    test({ 3,5,1, }, 0);
    test({ 3,1 }, 0);
    test({ 278,280,281,286,287,290,2,3,4,8,9,14,15,16,21,24,25,31,32,34,36,37,42,45,51,52,54,55,60,63,66,68,69,71,76,81,83,84,85,86,87,94,97,99,106,107,110,113,114,115,118,120,121,125,134,136,137,138,142,143,147,150,152,159,160,161,165,166,174,176,178,186,187,189,190,191,195,196,198,204,212,216,217,220,221,222,225,227,229,232,237,239,242,245,251,263,264,274,275,276,277 }, 286);
    test({ 1,3 }, 0);
    test({ 4,5,6,7,0,1,2 }, 0);
    test({ 4,5,6,7,0,1,2 }, 3);
    test({1}, 0);
}

