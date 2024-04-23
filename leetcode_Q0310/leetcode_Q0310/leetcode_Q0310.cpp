// leetcode_Q0310.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:

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

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
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
    test(4, { {1,0},{1,2},{1,3}, });
    test(6, { {3,0}, {3,1}, {3,2}, {3,4}, {5,4}, });
}
