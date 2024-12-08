// leetcode_Q2054.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include <vector>
#include <map>
#include <algorithm>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static int tle(vector<vector<int>>& events) {
        map<pair<int, int>, int> state_map;
        int max_value = 0;
        for (auto&& ev : events) {
            const auto st = ev[0];
            const auto et = ev[1];
            const auto value = ev[2];
            max_value = max(max_value, value);
            const auto key = make_pair(st, et);

            for (auto&& [time, other_value] : state_map) {
                if (!(max(time.first, st) <= min(time.second, et))) {
                    max_value = max(max_value, value + other_value);
                }
            }
            state_map[key] = max(state_map[key], value);
        }
        return max_value;
    }


    int maxTwoEvents(vector<vector<int>>& events) {
        sort(begin(events), end(events), [](const auto& a, const auto& b) {return a.front() < b.front(); });
        struct end_info {
            int end_time;
            int value;
        };
        auto compare = [](const end_info& e1, const end_info& e2) { return e1.end_time > e2.end_time; };
        priority_queue<end_info, vector<end_info>, decltype(compare)> end_time_queue(compare);
        int max_value = 0;
        int completed_max_value = 0;
        for (int i = 0; i < size(events); i++) {
            const auto st = events[i][0];
            const auto et = events[i][1];
            const auto value = events[i][2];
            
            end_time_queue.push({ et, value });

            while (!end_time_queue.empty() && end_time_queue.top().end_time < st) {
                completed_max_value = max(completed_max_value, end_time_queue.top().value);
                end_time_queue.pop();
            }
            max_value = max(max_value, completed_max_value + value);
        }
        return max_value;
    }
};

void test(vector<vector<int>>&& events) {
    cout << Solution().maxTwoEvents(events) << endl;
}
int main()
{
    test(get_matrix_int("[[1,3,2],[4,5,2],[2,4,3]]"));
    test(get_matrix_int("[[1,3,2],[4,5,2],[1,5,5]]"));
    test(get_matrix_int("[[1,5,3],[1,5,1],[6,6,5]]"));
    return 0;
}