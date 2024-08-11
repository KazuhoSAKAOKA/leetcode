// leetcode_Q1568.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static inline bool is_island(int v) {
        return v != 0;
    }


    int minDays(vector<vector<int>>& grid) {
        const auto M = size(grid);
        const auto N = size(grid.front());
        const size_t S = M * N;
        vector<vector<size_t>> graph(S);

        auto get_index = [&](size_t y, size_t x) {
            return y * N + x;
            };
        vector<size_t> lands;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                if (is_island(grid[i][j])) {
                    const auto index = get_index(i, j);
                    lands.push_back(index);
                    if (i < M - 1) {
                        if (is_island(grid[i + 1][j])) {
                            const auto bottom = get_index(i + 1, j);
                            graph[index].push_back(bottom);
                            graph[bottom].push_back(index);
                        }
                    }
                    if (j < N - 1) {
                        if (is_island(grid[i][j + 1])) {
                            const auto right = get_index(i, j + 1);
                            graph[index].push_back(right);
                            graph[right].push_back(index);
                        }
                    }
                }
            }
        }

        // no lands.
        if (lands.empty()) {
            return 0;
        }
        // only one land.
        if (size(lands) == 1) {
            return 1;
        }

        auto get_size_of_island = [&](size_t index, size_t ignore_island)->size_t {
            vector<bool> visited(S);
            queue<size_t> que;
            que.push(index);
            visited[index] = true;
            size_t count = 1;
            while (!que.empty()) {
                const auto current = que.front();
                que.pop();
                for (auto&& next : graph[current]) {
                    if (ignore_island != next && !visited[next]) {
                        count++;
                        que.push(next);
                        visited[next] = true;
                    }
                }
            }
            return count;
            };

        // already disconnected
        const auto first_island_count = get_size_of_island(lands.front(), static_cast<size_t>(-1));
        if (first_island_count < size(lands)) {
            return 0;
        }
        // check all land
        for (auto&& remove_target : lands) {
            const auto island_count = get_size_of_island(lands.front() != remove_target ? lands.front() : lands.back(), remove_target);
            if (island_count < size(lands) - 1) {
                return 1;
            }
        }
        return 2;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().minDays(grid) << endl;
}
int main()
{
    test(get_matrix_int("[[1,1,0,1,1],[1,1,1,1,1],[1,1,0,1,1],[1,1,0,1,1]]"));
    test(get_matrix_int("[[0,1,1,0],[0,1,1,0],[0,0,0,0]]"));
    test(get_matrix_int("[[1,1]]"));
    return 0;
}