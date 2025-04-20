#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> groups_map;
        for (auto&& ans : answers) {
            groups_map[ans]++;
        }
        int total_rabbits = 0;
        for (auto&& [ans, count] : groups_map) {
            const auto min_groups = (count + ans) / (ans + 1);
            total_rabbits += min_groups * (ans + 1);
        }
        return total_rabbits;
    }
};

void test(vector<int>&& answers) {
    cout << Solution().numRabbits(answers) << endl;
}
int main() {
    test(get_list_int("[1,1,2]"));
    test(get_list_int("[10,10,10]"));
    return 0;
}