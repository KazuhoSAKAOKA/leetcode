// leetcode_Q2467.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
constexpr int INF = INT_MAX;
class Solution {
public:

    static vector<int> bob_bfs(const vector<vector<int>>& graph, int bob) {
        vector<int> from(size(graph), INF);
        queue<int> q;
        q.push(bob);
        from[bob] = -1;

        while (!q.empty()) {
            const auto current = q.front();
            q.pop();
            for (auto&& next : graph[current]) {
                if (next == 0) {
                    from[next] = current;
                    break;
                }
                if (from[next] == INF) {
                    from[next] = current;
                    q.push(next);
                }
            }
        }
        vector<int> routes;
        int current = 0;
        while (current != bob) {
            routes.emplace_back(current);
            current = from[current];
        }
        return vector<int>(crbegin(routes), crend(routes));
    }


    static void dfs(int n, const std::vector<vector<int>>& graph, size_t current, size_t from, vector<int>& route) {
        //for(auto)
    }

    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        const size_t n = size(edges) + 1;
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            const auto u = edge.front();
            const auto v = edge.back();
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }

        const auto bobs = bob_bfs(graph, bob);
        output(bobs);
        return 0;
    }
};

void test(vector<vector<int>>&& edges, int bob, vector<int>&& amount) {
    cout << Solution().mostProfitablePath(edges, bob, amount) << endl;
}
int main()
{
    test(get_matrix_int("[[0,1],[1,2],[1,3],[3,4]]"), 3, get_list_int("[-2,4,2,-4,6]"));
    test(get_matrix_int("[[0,1]]"), 1, get_list_int("[-7280,2350]"));
    return 0;
}