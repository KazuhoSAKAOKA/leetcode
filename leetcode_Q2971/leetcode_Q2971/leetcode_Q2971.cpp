// leetcode_Q2971.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:

    long long largestPerimeter(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<long long> sums(nums.size() + 1, 0LL);

        for (int i = 0; i < nums.size(); i++) {
            sums[i + 1] = sums[i] + static_cast<long long>(nums[i]);
        }
        int index = nums.size() - 1;
        long long max_value = -1;
        while (1 < index) {
            if (nums[index] < sums[index]) {
                max_value = sums[index + 1];
                break;
            }
            index--;
        }

        return max_value;
    }
};


void test(vector<int>&& nums) {
    cout << Solution().largestPerimeter(nums) << endl;
}

int main()
{
    test({ 5,5,5 });
    test({ 1,12,1,2,5,50,3 });
    test({ 5,5,50 });
}