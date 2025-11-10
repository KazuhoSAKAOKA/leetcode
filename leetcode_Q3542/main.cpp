#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <stack>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int count = 0;
        stack<int> st;
        for (int i = 0; i < size(nums); i++) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                count++;
                st.pop();
            }
            if (st.empty() || nums[st.top()] < nums[i]) {
                st.push(i);
            }
        }
        while (!st.empty() && nums[st.top()]) {
            count++;
            st.pop();
        }
        return count;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().minOperations(nums) << endl;
}
int main() {
    test(get_list_int("[0,2]"));
    test(get_list_int("[3,1,2,1]"));
    test(get_list_int("[1,2,1,2,1,2]"));
    return 0;
}