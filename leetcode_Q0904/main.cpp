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
    int totalFruit(vector<int>& fruits) {

        int max_len = 0;
        int l = 0;
        unordered_map<int, int> freq_map;

        for (int r = 0; r < size(fruits); r++) {
            freq_map[fruits[r]]++;

            while (l < r && size(freq_map)>2) {
                auto it = freq_map.find(fruits[l]);
                if (it->second == 1) {
                    freq_map.erase(it);
                }
                else {
                    it->second--;
                }
                l++;
            }
            max_len = max(max_len, r - l + 1);

        }
        return max_len;
    }
};

void test(vector<int>&& fruits) {
    cout << Solution().totalFruit(fruits) << endl;
}
int main() {
    test(get_list_int("[1,2,1]"));
    test(get_list_int("[0,1,2,2]"));
    test(get_list_int("[1,2,3,2,2]"));
    return 0;
}