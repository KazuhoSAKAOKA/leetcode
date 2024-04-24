// leetcode_Q0310.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
#pragma region tle
    static int get_tree_height(const vector<vector<int>>& graph, int node, unordered_set<int>& checked) {
        int max_height = 0;

        for (auto&& destination : graph[node]) {
            if (checked.find(destination) == cend(checked)) {
                checked.insert(destination);
                max_height = max(max_height, get_tree_height(graph, destination, checked) + 1);
            }
        }
        return max_height;
    }
    static vector<int> tle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n, vector<int>());
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        int min_height = INT_MAX;
        unordered_map<int, vector<int>> height_map;
        for (int i = 0; i < n; i++) {
            unordered_set<int> checked{ i };
            const auto height = get_tree_height(graph, i, checked);
            min_height = min(min_height, height);
            height_map[height].emplace_back(i);
        }

        return height_map[min_height];
    }
#pragma endregion


    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return vector<int>{0};
        }
        vector<unordered_set<int>> graph(n, unordered_set<int>());
        for (auto&& edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        unordered_set<int> nodes;
        for (int i = 0; i < n; i++) {
            nodes.insert(i);
        }

        queue<int> node_queue;
        for (int i = 0; i < n; i++) {
            if (graph[i].size() == 1) {
                node_queue.push(i);
            }
            else if (graph[i].size() == 0) {
                nodes.erase(i);
            }
        }
        int cycle = 0;
        while (nodes.size() > 2) {
            queue<int> next_queue;
            while (!node_queue.empty()) {
                const int node = node_queue.front();
                node_queue.pop();
                for (auto&& destination_node : graph[node]) {
                    graph[destination_node].erase(node);
                    if (graph[destination_node].size() == 1) {
                        next_queue.push(destination_node);
                    }
                }
                nodes.erase(node);
            }
            node_queue = next_queue;
        }
        return vector<int>(cbegin(nodes), cend(nodes));
    }
};

void test(int n, vector<vector<int>>&& edges) {
    const auto ans = Solution().findMinHeightTrees(n, edges);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(1, {});
    test(4, { {1,0},{1,2},{1,3}, });
    test(6, { {3,0}, {3,1}, {3,2}, {3,4}, {5,4}, });
}
