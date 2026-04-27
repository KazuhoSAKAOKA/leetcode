#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {

    }
};

static void test(vector<int>&& nums, int k, int dist) {
    cout << Solution().minimumCost(nums, k, dist) << endl;
}
int main()
{
    test(get_list_int("[1,3,2,6,4,2]"), 3, 3);
    test(get_list_int("[10,1,2,2,2,1]"), 4, 3);
    test(get_list_int("[10,8,18,9]"), 3, 1);
    return 0;
}