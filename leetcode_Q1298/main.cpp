#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        const auto n = size(status);
        vector<bool> opened(n);
        vector<bool> having_boxes(n);
        vector<bool> having_keys(n);

        queue<int> q;
        for (auto&& init_box : initialBoxes) {
            q.push(init_box);
            having_boxes[init_box] = true;
        }

        int collected = 0;

        while (!q.empty()) {
            const auto current = q.front();
            q.pop();
            if (opened[current]) { continue; }
            if (having_boxes[current] && (status[current] != 0 || having_keys[current])) {
                opened[current] = true;
                for (auto&& box : containedBoxes[current]) {
                    if (!opened[box]) {
                        having_boxes[box] = true;
                        q.push(box);
                    }
                }
                for (auto&& key : keys[current]) {
                    if (!opened[key]) {
                        having_keys[key] = true;
                        q.push(key);
                    }
                }
                collected += candies[current];
            }
        }

        return collected;
    }
};
void test(vector<int>&& status, vector<int>&& candies, vector<vector<int>>&& keys, vector<vector<int>>&& containedBoxes, vector<int>&& initialBoxes) {
    cout << Solution().maxCandies(status, candies, keys, containedBoxes, initialBoxes) << endl;
}

int main() {
    test(get_list_int("[1,0,0,0,0,0]"), get_list_int("[1,1,1,1,1,1]"), get_matrix_int("[[1,2,3,4,5],[],[],[],[],[]]"), get_matrix_int("[[1,2,3,4,5],[],[],[],[],[]]"), get_list_int("[0]"));
    test(get_list_int("[1,0,1,0]"), get_list_int("[7,5,4,100]"), get_matrix_int("[[],[],[1],[]]"), get_matrix_int("[[1,2],[3],[],[]]"), get_list_int("[0]"));
    return 0;
}