// leetcode_Q0787.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    using to_and_cost = pair<int, int>;
    using connects = vector<to_and_cost>;
    using graph_type = vector<connects>;
    static int bellman_ford_step(const graph_type& graph, int start, int end, int k) {
        vector<int> current_costs(graph.size(), INT_MAX);
        vector<int> next_costs(graph.size(), INT_MAX);
        current_costs[start] = 0;
        unordered_set<int> current_set;
        unordered_set<int> next_set;
        current_set.insert(start);
        for (int i = 0;i <= k;i++) {
            next_costs = current_costs;
            for(auto&& from : current_set) {
                const auto base_cost = current_costs[from];
                if (base_cost != INT_MAX) {
                    for (auto&& [to, cost] : graph[from]) {
                        const auto new_cost = base_cost + cost;
                        next_costs[to] = min(next_costs[to], new_cost);
                        next_set.insert(to);
                    }
                }
            }
            swap(current_set, next_set);
            swap(current_costs, next_costs);
            next_set.clear();
        }
        return current_costs[end] == INT_MAX ? -1 : current_costs[end];
    }



    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        graph_type graph(n, connects());
        for (auto&& flight : flights) {
            graph[flight[0]].emplace_back(to_and_cost{ flight[1],flight[2] });
        }
        return bellman_ford_step(graph, src, dst, k);
    }
};


void test(int n, vector<vector<int>>&& flights, int src, int dst, int k) {
    cout << Solution().findCheapestPrice(n, flights, src, dst, k) << endl;
}


int main(){
    test(5, { {0, 1, 5},{1, 2, 5},{0, 3, 2},{3, 1, 2},{1, 4, 1},{4, 2, 1} }, 0, 2, 2);
    test(4, { {0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200} }, 0, 3, 1);
    test(3, { {0,1,100},{1,2,100},{0,2,500} }, 0, 2, 1);
    test(3, { {0,1,100},{1,2,100},{0,2,500} }, 0, 2, 0);
}