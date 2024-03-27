// leetcode_Q0713.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class Solution {
public:
    using memo_key_t = int;
    using memo_t = unordered_map<memo_key_t, int>;

    static int rec(const vector<int>& nums, int k, int index, memo_t& memo){
        if (nums.size() == index) {
            return 0;
        }

        const auto key = index;
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int count = 0;

        if(nums[index] < k){
            count++;
            int64_t product_val = nums[index];
            for (int i = 1; i < nums.size() - index; i++) {
                product_val *= nums[index + i];
                if (product_val < k) {
                    count++;
                }
                else {
                    break;
                }
            }
        }

        count += rec(nums, k, index + 1, memo);

        memo[key] = count;
        return count;
    }

    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        memo_t memo;
        return rec(nums, k, 0, memo);
    }
};


void test(vector<int>&& nums, int k) {
    cout << Solution().numSubarrayProductLessThanK(nums, k) << endl;
}

int main()
{
    test({ 10,5,2,6 }, 100);
    test({ 1,2,3 }, 0);
}