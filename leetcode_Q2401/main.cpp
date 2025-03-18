#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"


using namespace std;

class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {

        int max_len = 0;
        int l = 0;
        vector<int> bits(32);
        int dup_count = 0;
        for (int r = 0; r < size(nums); r++) {
            for (int i = 0; i < 32; i++) {
                if ((nums[r] & (1 << i)) != 0) {
                    bits[i]++;
                    if (bits[i] == 2) {
                        dup_count++;
                    }
                }
            }

            while (l < r && dup_count > 0) {
                for (int i = 0; i < 32; i++) {
                    if ((nums[l] & (1 << i)) != 0) {
                        bits[i]--;
                        if (bits[i] == 1) {
                            dup_count--;
                        }
                    }
                }
                l++;
            }
            max_len = max(max_len, r - l + 1);
        }
        return max_len;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().longestNiceSubarray(nums) << endl;
}

int main() {
    test(get_list_int("[1,3,8,48,10]"));
    test(get_list_int("[3,1,5,11,13]"));
    return 0;
}