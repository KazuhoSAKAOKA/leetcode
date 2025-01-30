// leetcode_Q2493.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include <vector>

#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    static pair<bool, vector<vector<int>>> isBipartite(const vector<vector<int>>& graph) {
        const auto N = size(graph);
        vector<int> status(N, 0);
        queue<int> q;
        vector<vector<int>> groups;
        for (int i = 0; i < N; i++) {
            if (status[i] == 0) {
                status[i] = 1;
                q.push(i);
                vector<int> group;
                group.emplace_back(i);
                while (!q.empty()) {
                    const auto node = q.front();
                    q.pop();
                    const auto current_status = status[node];
                    const auto next_status = current_status == 1 ? 2 : 1;
                    for (auto&& next : graph[node]) {
                        if (status[next] == 0) {
                            group.emplace_back(next);
                            status[next] = next_status;
                            q.push(next);
                        }
                        else {
                            if (status[next] != next_status) {
                                return { false, vector<vector<int>>() };
                            }
                        }
                    }
                }

                groups.emplace_back(group);
            }
        }
        return { true,groups };
    }

    static int divide(const vector<vector<int>>& graph, const vector<int>& nodes) {
        int max_count = 0;
        for (auto&& begin_node : nodes) {
            vector<bool> visited(size(graph));
            visited[begin_node] = true;
            int count = 0;
            vector<int> befores;
            befores.emplace_back(begin_node);

            while (!befores.empty()) {
                vector<int> currents;
                for (auto&& node : befores) {
                    for (auto&& next : graph[node]) {
                        if (!visited[next]) {
                            currents.emplace_back(next);
                            visited[next] = true;
                        }
                    }
                }
                count++;
                swap(befores, currents);
            }
            max_count = max(max_count, count);
        }
        return max_count;
    }


    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            const auto u = edge.front() - 1;
            const auto v = edge.back() - 1;
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }
        const auto [is_bipartite, groups] = isBipartite(graph);
        if (!is_bipartite) {
            return -1;
        }

        int total = 0;

        for (auto&& group : groups) {
            total += divide(graph, group);
        }
        return total;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
