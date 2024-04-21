// leetcode_Q1971.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    static bool dfs(const vector<vector<int>>& graph, int current, int destination, vector<bool>& visited) {
        if (current == destination) {
            return true;
        }
        for (auto&& d : graph[current]) {
            if (!visited[d]) {
                visited[d] = true;
                if (dfs(graph, d, destination, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> graph(n, vector<int>());
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        vector<bool> visited(n, false);
        return dfs(graph, source, destination, visited);
    }
};

void test(int n, vector<vector<int>>&& edges, int source, int destination) {
    cout << Solution().validPath(n, edges, source, destination) << endl;
}

int main()
{
    test(3, { {0,1}, {1,2}, {2,0}, }, 0, 2);
    test(6, { {0,1}, {0,2}, {3,5},{5,4},{4,3} }, 0, 5);
}
