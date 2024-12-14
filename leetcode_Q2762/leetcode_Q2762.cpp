// leetcode_Q2762.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        long long total = 0;
        map<int, int> current_freq;
        size_t l = 0;
        for (size_t r = 0; r < size(nums); r++) {
            current_freq[nums[r]]++;

            while (l < r && (crbegin(current_freq)->first - cbegin(current_freq)->first) > 2) {
                current_freq[nums[l]]--;
                if (current_freq[nums[l]] == 0) {
                    current_freq.erase(nums[l]);
                }
                l++;
            }
            if ((crbegin(current_freq)->first - cbegin(current_freq)->first) <= 2) {
                total += r - l + 1;
            }
        }
        return total;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().continuousSubarrays(nums) << endl;
}

int main()
{
    test(get_list_int("[5,4,2,4]"));
    test(get_list_int("[1,2,3]"));
    return 0;
}