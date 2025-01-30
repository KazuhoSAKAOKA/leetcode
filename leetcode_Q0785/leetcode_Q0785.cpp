// leetcode_Q0785.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        const auto N = size(graph);
        vector<int> status(N, 0);
        queue<int> q;

        for (int i = 0; i < N; i++) {
            if (status[i] == 0) {
                status[i] = 1;
                q.push(i);

                while (!q.empty()) {
                    const auto node = q.front();
                    q.pop();
                    const auto current_status = status[node];
                    const auto next_status = current_status == 1 ? 2 : 1;
                    for (auto&& next : graph[node]) {
                        if (status[next] == 0) {
                            status[next] = next_status;
                            q.push(next);
                        }
                        else {
                            if (status[next] != next_status) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
};

void test(vector<vector<int>>&& graph) {
    cout << Solution().isBipartite(graph) << endl;
}
int main()
{
    test(get_matrix_int("[[1,2,3],[0,2],[0,1,3],[0,2]]"));
    test(get_matrix_int("[[1,3],[0,2],[1,3],[0,2]]"));
    return 0;
}