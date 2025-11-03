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
    int minCost(string colors, vector<int>& neededTime) {
        int total_cost = 0;
        char current_color = colors[0];
        int cur_streak_max_cost = neededTime[0];
        int cur_streak_cost = neededTime[0];
        
        for (int i = 1; i < size(colors); i++) {
            if (current_color == colors[i]) {
                cur_streak_max_cost = max(cur_streak_max_cost, neededTime[i]);
                cur_streak_cost += neededTime[i];
            }
            else {
                total_cost += cur_streak_cost - cur_streak_max_cost;
                current_color = colors[i];
                cur_streak_max_cost = neededTime[i];
                cur_streak_cost = neededTime[i];
            }
        }
        total_cost += cur_streak_cost - cur_streak_max_cost;
        return total_cost;
    }
};

static void test(string&& colors, vector<int>&& neededTime) {
    cout << Solution().minCost(colors, neededTime) << endl;
}
int main() {
    test("abaac", get_list_int("[1,2,3,4,5]"));
    test("abc", get_list_int("[1,2,3]"));
    test("aabaa", get_list_int("[1,2,3,4,1]"));
	return 0;
}