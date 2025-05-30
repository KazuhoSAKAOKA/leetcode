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

    static void dfs(const vector<int>& edges, int current, vector<int>& distances, int cur_distance) {
        if (current < 0) {
            return;
        }
        if (distances[current] != INT_MAX) {
            return;
        }
        distances[current] = cur_distance;
        dfs(edges, edges[current], distances, cur_distance + 1);
    }

    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        const auto n = size(edges);
        vector<int> distances1(n, INT_MAX);
        vector<int> distances2(n, INT_MAX);

        dfs(edges, node1, distances1, 0);
        dfs(edges, node2, distances2, 0);
        int min_dist = INT_MAX;
        int ans_node = -1;

        for (int i = 0; i < n; i++) {
            if (distances1[i] != INT_MAX && distances2[i] != INT_MAX) {
                const auto dist = max(distances1[i], distances2[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    ans_node = i;
                }
            }
        }
        return ans_node;
    }
};
void test(vector<int>&&edges, int node1, int node2) {
    cout << Solution().closestMeetingNode(edges, node1, node2) << endl;
}
int main() {
    test(get_list_int("[1,2,-1]"), 0, 2);
    test(get_list_int("[2,2,3,-1]"), 0, 1);
    return 0;
}