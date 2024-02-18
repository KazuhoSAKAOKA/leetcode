// leetcode_Q2402.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(begin(meetings), end(meetings), [](const auto& a, const auto& b) { return a[0] < b[0]; });

        using TIME_AND_INDEX = pair<int64_t, int>;
        auto pair_comparer_greater = [](const auto& a, const auto& b)
            {
                if (a.first != b.first) {
                    return a.first > b.first;
                }
                return a.second > b.second;
            };
        priority_queue<TIME_AND_INDEX, vector<TIME_AND_INDEX>, decltype(pair_comparer_greater)> start_queue(pair_comparer_greater);
        priority_queue<TIME_AND_INDEX, vector<TIME_AND_INDEX>, decltype(pair_comparer_greater)> using_room_queue(pair_comparer_greater);
        priority_queue<int, vector<int>, greater<int>> free_room;
        for (int i = 0; i < meetings.size(); i++) {
            start_queue.emplace(TIME_AND_INDEX(meetings[i][0], i));
        }
        for (int i = 0; i < n; i++) {
            free_room.push(i);
        }
        unordered_map<int, int> helds_map;
        while(!start_queue.empty()) {
            const auto [time, index] = start_queue.top();
            const auto len = static_cast<int64_t>(meetings[index][1] - meetings[index][0]);
            start_queue.pop();
            while (!using_room_queue.empty() && using_room_queue.top().first <= time) {
                free_room.push(using_room_queue.top().second);
                using_room_queue.pop();
            }

            if (!free_room.empty()) {
                const auto room_index = free_room.top();
                free_room.pop();
                helds_map[room_index]++;
                using_room_queue.push(TIME_AND_INDEX(time + len, room_index));
            }
            else {
                const auto [room_end_time, room_index] = using_room_queue.top();
                using_room_queue.pop();
                helds_map[room_index]++;
                using_room_queue.push(TIME_AND_INDEX(room_end_time + len, room_index));
            }
        }
        int max_value = 0;
        int max_room = -1;
        for (auto& [k, v] : helds_map) {
            if (max_value < v) {
                max_room = k;
                max_value = v;
            }
            else if (max_value == v && max_room > k) {
                max_room = k;
            }
        }
        return max_room;
    }
};

void test(int n, vector<vector<int>>&& meetings) {
    cout << Solution().mostBooked(n, meetings) << endl;
}

int main()
{
    test(4, { {18,19},{3,12},{17,19},{2,13},{7,10} });
    test(3, { {0,10},{1,9},{2,8},{3,7},{4,6} });
    test(2, { {0,10},{1,5},{2,7},{3,4} });
    test(3, { {1,20},{2,10},{3,5},{4,9},{6,8} });
}