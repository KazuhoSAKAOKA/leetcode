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
    int maxEvents(vector<vector<int>>& events) {
        map<int, map<int, int>> event_map;
        for (auto&& event : events) {
            event_map[event.front()][event.back()]++;
        }
        int current_day = 0;
        priority_queue<int, vector<int>, greater<int>> cur_queue;
        auto it = cbegin(event_map);
        int count = 0;
        while (it != cend(event_map)) {
            const auto& beginday = it->first;
            const auto& enddays = it->second;

            for (auto&& [endday, count] : enddays) {
                for (int i = 0; i < count; i++) {
                    cur_queue.push(endday);
                }
            }
            current_day = max(current_day, beginday);
            const auto it_next = next(it);
            int next_begin_day = it_next == cend(event_map) ? INT_MAX : it_next->first;
            while (!cur_queue.empty() && current_day < next_begin_day) {
                if (current_day <= cur_queue.top()) {
                    count++;
                    current_day++;
                }
                cur_queue.pop();
            }
            it = it_next;
        }

        return count;
    }
};
void test(vector<vector<int>>&& events) {
    cout << Solution().maxEvents(events) << endl;
}

int main() {
    test(get_matrix_int("[[1,2],[1,2],[3,3],[1,5],[1,5]]"));
    test(get_matrix_int("[[1,2],[2,3],[3,4]]"));
    test(get_matrix_int("[[1,2],[2,3],[3,4],[1,2]]"));
    return 0;
}