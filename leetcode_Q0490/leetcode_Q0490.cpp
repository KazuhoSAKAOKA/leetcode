#include <iostream>
#include <vector>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        const auto n = size(maze);
        const auto m = size(maze[0]);
        vector<vector<bool>> visited(n, vector<bool>(m));
        queue<pair<int, int>> q;
        q.push({ start[0], start[1] });
        visited[start[0]][start[1]] = true;
        const pair<int, int> goal{ destination[0], destination[1] };
        vector<pair<int, int>> dirs{
            {-1,0},{1,0}, {0,-1},{0,1},
        };

        auto get_next_pos = [&](const pair<int, int>& pos, const pair<int, int>& dir) {
            pair<int, int> current(pos);
            for(;;) {
                const auto next = make_pair(current.first + dir.first, current.second + dir.second);
                if (next.first < 0 || n <= next.first || next.second < 0 || m <= next.second || maze[next.first][next.second]) {
                    break;
                }
                current = next;
            }
            return current;
            };

        while (!q.empty()) {
            const pair<int, int> current = q.front();
            q.pop();

            for (auto&& dir : dirs) {
                auto next = get_next_pos(current, dir);
                if (!visited[next.first][next.second]) {
                    if (goal == next) { return true; }
                    q.push(next);
                    visited[next.first][next.second] = true;
                }
            }
        }
        return false;
    }
};
static void test(vector<vector<int>>&& maze, vector<int>&& start, vector<int>&& destination) {
    cout << Solution().hasPath(maze, start, destination) << endl;
}
int main()
{
    test(get_matrix_int("[[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]]"), get_list_int("[0,4]"), get_list_int("[4,4]"));
    test(get_matrix_int("[[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]]"), get_list_int("[0,4]"), get_list_int("[3,2]"));
    test(get_matrix_int("[[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]]"), get_list_int("[4,3]"), get_list_int("[0,1]"));
    return 0;
}

