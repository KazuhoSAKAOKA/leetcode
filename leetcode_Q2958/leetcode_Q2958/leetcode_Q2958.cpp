// leetcode_Q2958.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> counts_map;
        int forward = 0;
        int backward = 0;
        int max_len = 0;
        while (forward < nums.size()) {
            int current = 0;
            while (forward < nums.size()) {
                current = nums[forward];
                const int freq = ++counts_map[current];
                if (k < freq) {
                    forward++;
                    break;
                }
                max_len = max(max_len, forward - backward + 1);
                forward++;
            }

            while(backward < nums.size()) {
                const int remove_item = nums[backward++];
                counts_map[remove_item]--;
                if (current == remove_item) {
                    break;
                }
            }
        }
        return max_len;
    }
};

void test(vector<int>&& nums, int k) {
    cout << Solution().maxSubarrayLength(nums, k) << endl;
}
int main()
{
    test({ 1,2,3,1,2,3,1,2 }, 2);
    test({ 1,2,1,2,1,2,1,2 }, 1);
    test({ 5,5,5,5,5,5,5 }, 4);
}