// leetcode_Q0802.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        const auto N = size(graph);
        vector<vector<int>> reverse_graph(N);
        vector<int> inbounds(N);
        vector<bool> safe_nodes(N);
        queue<int> candidate_queue;
        for (int i = 0; i < N; i++) {
            if (graph[i].empty()) {
                candidate_queue.push(i);
            }
            else {
                for (auto&& dest : graph[i]) {
                    reverse_graph[dest].emplace_back(i);
                }
            }
        }

        while (!candidate_queue.empty()) {
            const auto node = candidate_queue.front();
            candidate_queue.pop();
            if (!safe_nodes[node] && size(graph[node]) == inbounds[node]) {
                safe_nodes[node] = true;
                for (auto&& from : reverse_graph[node]) {
                    inbounds[from]++;
                    candidate_queue.push(from);
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < N; i++) {
            if (safe_nodes[i]) {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};
void test(vector<vector<int>>&& graph) {
    output(Solution().eventualSafeNodes(graph));
}
int main()
{
    test(get_matrix_int("[[1,3,4,5,7,9],[1,3,8,9],[3,4,5,8],[1,8],[5,7,8],[8,9],[7,8,9],[3],[],[]]"));
    test(get_matrix_int("[[1,2],[2,3],[5],[0],[5],[],[]]"));
    test(get_matrix_int("[[1,2,3,4],[1,2],[3,4],[0,4],[]]"));
    return 0;
}