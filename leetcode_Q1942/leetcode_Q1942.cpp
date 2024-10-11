// leetcode_Q1942.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        vector<size_t> indexes(size(times));
        for (size_t i = 0; i < size(times); i++) {
            indexes[i] = i;
        }
        sort(begin(indexes), end(indexes), [&](const auto& a, const auto& b) { return times[a].front() < times[b].front();  });

        int ans = 0;
        struct stay_friend {
            int leave;
            size_t chair;
        };
        auto compare = [](const stay_friend& a, const stay_friend& b) { return a.leave > b.leave; };
        priority_queue<stay_friend, vector<stay_friend>, decltype(compare)> party_queue(compare);

        priority_queue < size_t, vector<size_t>, std::greater<size_t >> chair_queue;
        size_t current_max_chair = 0;
        for (auto&& index : indexes) {
            const auto current_time = times[index].front();
            const auto leave_time = times[index].back();
            while (!party_queue.empty() && party_queue.top().leave <= current_time) {
                const auto chair = party_queue.top().chair;
                chair_queue.push(chair);
                party_queue.pop();
            }
            size_t chair;
            if (chair_queue.empty()) {
                chair = current_max_chair;
                current_max_chair++;
            }
            else {
                chair = chair_queue.top();
                chair_queue.pop();
            }
            if (targetFriend == index) {
                ans = chair;
                break;
            }
            party_queue.push(stay_friend{ leave_time, chair });
        }
        return ans;
    }
};

void test(vector<vector<int>>&& times, int targetFriend) {
    cout << Solution().smallestChair(times, targetFriend) << endl;
}
int main()
{
    test(get_matrix_int("[[1,4],[2,3],[4,6]]"), 1);
    test(get_matrix_int("[[3,10],[1,5],[2,6]]"), 0);
    return 0;
}