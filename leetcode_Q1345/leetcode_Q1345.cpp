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
#include <numbers>
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
    int minJumps(vector<int>& arr) {
        const int n = size(arr);
        if (n == 1) { return 0; }
        constexpr int INF = INT_MAX / 2;
        vector<int> costs(n, INF);
        
        unordered_map<int, vector<int>> jumps;
        unordered_set<int> jumpeds;
        for (int i = 0; i < n; i++) {
            jumps[arr[i]].push_back(i);
        }
        queue<int> q;
        q.push(0);
        costs[0] = 0;

        while (!q.empty()) {
            const auto cur = q.front();
            q.pop();
            const auto next_cost = costs[cur] + 1;
            if (cur > 0 && next_cost < costs[cur - 1]) {
                q.push(cur - 1);
                costs[cur - 1] = next_cost;
            }
            if (cur < n - 1 && next_cost < costs[cur + 1]) {
                if (cur == n - 2) { return next_cost; }
                q.push(cur + 1);
                costs[cur + 1] = next_cost;
            }
            auto it = jumpeds.find(arr[cur]);
            if (it == cend(jumpeds)) {
                jumpeds.insert(arr[cur]);
                for (auto&& np : jumps[arr[cur]]) {
                    if (np == cur) { continue; }
                    if (np == n - 1) { return next_cost; }
                    if (next_cost < costs[np]) {
                        q.push(np);
                        costs[np] = next_cost;
                    }
                }
            }
        }
        return n - 1;
    }
};

static void test(vector<int>&& arr) {
    cout << Solution().minJumps(arr) << endl;
}

int main() {
    test(get_list_int("[7,7,7,7,11]"));
    test(get_list_int("[100,-23,-23,404,100,23,23,23,3,404]"));
    test(get_list_int("[7]"));
    test(get_list_int("[7,6,9,6,9,6,9,7]"));
    return 0;
}
