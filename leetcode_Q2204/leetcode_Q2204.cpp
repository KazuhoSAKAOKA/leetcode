// leetcode_Q2204.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    
    static void dfs_cycle(const vector<vector<int>>& graph, int v, int p, vector<bool>& seen, vector<bool>& finished, stack<int>& history, int& pos) {
        seen[v] = true;
        history.push(v);
        for (auto nv : graph[v]) {
            if (nv == p) {
                continue; // 逆流を禁止する
            }

            // 完全終了した頂点はスルー
            if (finished[nv]) { continue; }

            // サイクルを検出
            if (seen[nv] && !finished[nv]) {
                pos = nv;
                return;
            }

            // 再帰的に探索
            dfs_cycle(graph, nv, v, seen, finished, history, pos);

            // サイクル検出したならば真っ直ぐに抜けていく
            if (pos != -1) { return; }
        }
        history.pop();
        finished[v] = true;
    }

    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge.front()].emplace_back(edge.back());
            graph[edge.back()].emplace_back(edge.front());
        }
        vector<bool> seen(n);
        vector<bool> finished(n);
        stack<int> history;
        int pos = -1;
        dfs_cycle(graph, 0, -1, seen, finished, history, pos);

        vector<int> temp;
        while (!history.empty()) {
            cout << history.top() << ",";
            history.pop();
        }
        cout << endl;
        return vector<int>{};
    }
};

void test(int n, vector<vector<int>>&& edges) {
    output(Solution().distanceToCycle(n, edges));
}

int main()
{
    test(7, get_matrix_int("[[1,2],[2,4],[4,3],[3,1],[0,1],[5,2],[6,5]]"));
    test(9, get_matrix_int("[[0,1],[1,2],[0,2],[2,6],[6,7],[6,8],[0,3],[3,4],[3,5]]"));
    return 0;
}