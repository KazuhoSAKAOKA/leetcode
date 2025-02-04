#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int max_sum = 0;
        int before = 0;
        int cur_sum = 0;
        for (auto&& num : nums) {
            if (before < num) {
                cur_sum += num;
            }
            else {
                cur_sum = num;
            }
            max_sum = max(max_sum, cur_sum);
            before = num;
        }
        return max_sum;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().maxAscendingSum(nums) << endl;
}
int main()
{
    test(get_list_int("[3,6,10,1,8,9,9,8,9]"));
    return 0;
}