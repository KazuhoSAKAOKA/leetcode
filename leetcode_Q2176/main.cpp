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
    int countPairs(vector<int>& nums, int k) {
        vector<vector<int>> exists(101);
        int count = 0;
        for (int i = 0; i < size(nums); i++) {
            if (!exists[nums[i]].empty()) {
                if (i % k == 0) {
                    count += size(exists[nums[i]]);
                }
                else {
                    for (auto&& bef : exists[nums[i]]) {
                        if ((bef * i) % k == 0) {
                            count++;
                        }
                    }
                }
            }
            exists[nums[i]].emplace_back(i);
        }
        return count;
    }
};
void test(vector<int>&& nums, int k) {
    cout << Solution().countPairs(nums, k) << endl;
}

int main() {
    test(get_list_int("[5,4,5,7,6,5,5,8,4,6,6,4,7,8,8,4,6,8,8]"), 7);
    test(get_list_int("[3,1,2,2,2,1,3]"), 2);
    test(get_list_int("[1,2,3,4]"), 2);
    return 0;
}