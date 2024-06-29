// leetcode_Q2192.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static void get_descendants(const vector<vector<int>>& graph, int start, vector<set<int>>& ancestors) {
        vector<bool> visited(graph.size(), false);
        queue<int> visit_queue;
        visit_queue.push(start);
        visited[start] = true;

        while (!visit_queue.empty()) {
            const auto current = visit_queue.front();
            visit_queue.pop();
            for (auto&& next : graph[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    visit_queue.push(next);
                    ancestors[next].insert(current);
                    ancestors[next].insert(cbegin(ancestors[current]), cend(ancestors[current]));
                }
            }
        }
    }
    static vector<vector<int>> tle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
        }
        vector<set<int>> ancestors(n);
        for (int i = 0; i < n; i++) {
            get_descendants(graph, i, ancestors);
        }

        vector<vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = vector<int>(cbegin(ancestors[i]), cend(ancestors[i]));
        }

        return ans;
    }

    static set<int> get_descendants(const vector<vector<int>>& graph, int start) {
        set<int> visited;
        queue<int> visit_queue;
        visit_queue.push(start);

        while (!visit_queue.empty()) {
            const auto current = visit_queue.front();
            visit_queue.pop();
            for (auto&& next : graph[current]) {
                if (visited.count(next) == 0 && next != start) {
                    visited.insert(next);
                    visit_queue.push(next);
                }
            }
        }
        return visited;
    }
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge[1]].emplace_back(edge[0]);
        }
        vector<vector<int>> ans;
        ans.reserve(n);
        for (int i = 0; i < n; i++) {
            const auto visited = get_descendants(graph, i);
            ans.emplace_back(vector<int>(cbegin(visited), cend(visited)));
        }
        return ans;
    }
};

void test(int n, vector<vector<int>>&& edges) {
    const auto ans = Solution().getAncestors(n, edges);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    test(8, get_matrix_int("[[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]"));
    test(5, get_matrix_int("[[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]"));
}