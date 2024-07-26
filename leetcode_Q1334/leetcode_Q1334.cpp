// leetcode_Q1334.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"

using  namespace std;

class Solution {
public:
    struct path {
        int to_;
        int weight_;
    };

    static int reachable_cities(const vector<vector<path>>& graph, int distanceThreshold, int start) {
        vector<int> costs(graph.size(), INT_MAX);

        struct state{
            int pos_;
            int cost_;
        };
        unordered_set<int> destinations;
        destinations.insert(start);
        queue<state> que;
        que.push({ start, 0 });
        costs[start] = 0;

        while (!que.empty()) {
            const state current = que.front();
            que.pop();
            if (costs[current.pos_] < current.cost_) { continue; }
            for (auto&& p : graph[current.pos_]) {
                const int new_cost = p.weight_ + costs[current.pos_];
                if (new_cost <= distanceThreshold && new_cost < costs[p.to_]) {
                    destinations.insert(p.to_);
                    costs[p.to_] = new_cost;
                    que.push({ p.to_, new_cost });
                }
            }

        }
        return destinations.size() - 1;
    }

    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {

        vector<vector<path>> graph(n);

        for (auto&& edge : edges) {
            graph[edge[0]].push_back({ edge[1], edge[2] });
            graph[edge[1]].push_back({ edge[0], edge[2] });
        }

        int min_cities = INT_MAX;
        int ans_city = -1;

        for (int i = 0; i < n; i++) {
            const int reachables = reachable_cities(graph, distanceThreshold, i);
            if (reachables <= min_cities) {
                min_cities = reachables;
                ans_city = i;
            }
        }

        return ans_city;
    }
};

void test(int n, vector<vector<int>>&& edges, int distanceThreshold) {
    cout << Solution().findTheCity(n, edges, distanceThreshold) << endl;
}
int main()
{
    test(4, get_matrix_int("[[0,1,3],[1,2,1],[1,3,4],[2,3,1]]"), 4);
    test(5, get_matrix_int("[[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]]"), 2);
    return 0;
}