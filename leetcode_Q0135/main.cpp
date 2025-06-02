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
    int candy(vector<int>& ratings) {
        const auto n = size(ratings);
        vector<int> indexes(n);
        for (int i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](int a, int b) { return ratings[a] < ratings[b]; });

        int total_count = 0;
        vector<int> candies(n);
        for (auto&& index : indexes) {
            int cur_candy = 1;
            if (index > 0 && ratings[index-1] < ratings[index]) {
                cur_candy = max(cur_candy, candies[index - 1] + 1);
            }
            if (index < n - 1 && ratings[index + 1] < ratings[index]) {
                cur_candy = max(cur_candy, candies[index + 1] + 1);
            }
            candies[index] = cur_candy;
            total_count += cur_candy;
        }
        return total_count;
    }
};

void test(vector<int>&& ratings) {
    cout << Solution().candy(ratings) << endl;
}
int main() {
    test(get_list_int("[1,0,2]"));
    test(get_list_int("[1,2,2]"));
    return 0;
}