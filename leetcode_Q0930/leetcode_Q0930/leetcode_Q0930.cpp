// leetcode_Q0930.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {

        vector<int> sums(nums.size() + 1, 0);
        for (int i = 0; i <= nums.size(); i++) {
            sums[i + 1] = sums[i] + nums[i];
        }



        int total = 0;
        for (auto i = 0; i < nums.size(); i++) {
            int sum = 0;
            for (int j = 0; i + j < nums.size(); j++) {
                sum += nums[i + j];
                if (sum == goal) {
                    total++;
                }
            }
        }
        return total;
    }
};

void test(vector<int>&& nums, int goal) {
    cout << Solution().numSubarraysWithSum(nums, goal) << endl;
}

int main()
{
    test({ 1,0,1,0,1 }, 2);
    test({ 0,0,0,0,0 }, 0);
}