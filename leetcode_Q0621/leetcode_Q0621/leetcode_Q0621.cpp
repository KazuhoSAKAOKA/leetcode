// leetcode_Q0621.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> task_map;
        for (auto&& c : tasks) {
            task_map[c]++;
        }

        struct time_counts {
            int time;
            int counts;
            char c;
        };

        auto complarer = [](const time_counts& a, const time_counts& b) 
            {
                if (a.time == b.time) {
                    return a.counts < b.counts;
                }
                return a.time > b.time;
            };
        priority_queue<time_counts, vector<time_counts>, decltype(complarer)> p_queue(complarer);
        for (auto&& p : task_map) {
            p_queue.push(time_counts{ 0, p.second, p.first });
        }
        int counter = 0;
        while (!p_queue.empty()) {
            while (p_queue.top().time < counter) {
                auto temp = p_queue.top();
                p_queue.pop();
                p_queue.push(time_counts{ counter, temp.counts, temp.c });
            }
            auto p = p_queue.top();
            p_queue.pop();
            counter = max(counter + 1, p.time + 1);
            cout << "selected " << p.c << "," << counter << endl;
            if (p.counts > 1) {
                p_queue.push(time_counts{ counter + n, p.counts - 1, p.c });
            }
        }
        return counter;
    }
};

void test(vector<char>&& tasks, int n) {
    cout << Solution().leastInterval(tasks, n) << endl;
}

int main()
{
    test({ 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G' }, 1);
    test({ 'A','A','A', 'B' }, 3);

    test({ 'A','B','C','D','E','A','B','C','D','E' }, 4);
    test({ 'A','A','A','B','B','B' }, 2);
    test({ 'A','C','A','B','D','B' }, 1);
    test({ 'A','A','A', 'B','B','B' }, 3);
}