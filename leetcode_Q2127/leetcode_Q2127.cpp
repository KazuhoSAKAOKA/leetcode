#include <iostream>
#include <vector>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    using DIST_NODES = size_t;
    using NODE = size_t;
    static pair<DIST_NODES, NODE> dfs_far(const vector<vector<NODE>>& graph, NODE node, vector<bool>& visited) {
        pair<DIST_NODES, NODE> max_pair = { static_cast<DIST_NODES>(1), node };
        visited[node] = true;
        for (auto&& dest : graph[node]) {
            if (!visited[dest]) {
                const auto [d, far_node] = dfs_far(graph, dest, visited);
                if (max_pair.first < d + 1) {
                    max_pair = { d + 1,far_node };
                }
            }
        }
        visited[node] = false;
        return max_pair;
    }

    static DIST_NODES get_distance(const vector<NODE>& route, NODE node) {
        DIST_NODES dist = 1;
        for (auto it = crbegin(route); it != crend(route); ++it) {
            if (*it == node) {
                return dist;
            }
            dist++;
        }
        throw std::exception();
    }


    optional<NODE> dfs_cycle(const vector<vector<NODE>>& graph, int v, vector<NODE>& history, vector<bool>& seen, vector<bool>& finished) {
        seen[v] = true;
        history.emplace_back(v);
        for (auto& next : graph[v]) {
            if (!finished[next]) {
                if (seen[next] && !finished[next]) {
                    return next;
                }
                const auto result = dfs_cycle(graph, next, history, seen, finished);
                if (result) { return  result; }
            }
        }
        finished[v] = true;
        history.pop_back();
        return false;
    }

    vector<NODE> reconstruct(NODE pos, vector<NODE>& history) {
        vector<NODE> res;
        while (!history.empty()) {
            int v = history.back();
            res.push_back(v);
            history.pop_back();
            if (v == pos) { break; }
        }
        reverse(begin(res), end(res));
        return res;
    }
    /*
    static void dfs_cycle(const vector<vector<NODE>>& graph, NODE node, vector<NODE>& route, vector<bool>& visited, DIST_NODES& max_cycle) {
        if (visited[node]) {
            const auto dist = get_distance(route, node);
            max_cycle = max(max_cycle, dist);
            return;
        }

        visited[node] = true;
        route.emplace_back(node);
        for (auto&& dest : graph[node]) {
            dfs_cycle(graph, node, route, visited, max_cycle);
        }
        route.pop_back();
        visited[node] = false;
    }*/
    /*
    static pair<DIST_NODES, NODE> bfs(const vector<vector<NODE>>& graph, NODE node) {
        pair<DIST_NODES, NODE> max_pair = { static_cast<DIST_NODES>(1), node };
        vector<bool> used(size(graph));
        used[node] = true;
        queue<NODE> q;
        q.push(node);
        vector<DIST_NODES> dists(size(graph), INT_MAX);
        dists[node] = 0;
        while (!q.empty()) {
            const auto cur_node = q.front();
            q.pop();
            for (auto&& dest : graph[cur_node]) {
                if (!used[dest]) {
                    used[dest] = true;
                    dists[dest] = dists[cur_node] + 1;
                    q.push(dest);
                    if (max_pair.first < dists[dest]) {
                        max_pair = { dists[dest], dest };
                    }
                }
            }
        }
        return max_pair;
    }
    */

    int maximumInvitations(vector<int>& favorite) {
        const auto N = size(favorite);
        vector<vector<NODE>> graph(N);
        for (int i = 0; i < N; i++) {
            graph[i].emplace_back(favorite[i]);
        }
        int max_cycle = 0;
        for (size_t i = 0; i < N; i++) {
            vector<NODE> history;
            vector<bool> seen(N);
            vector<bool> finished(N);
            const auto cycle_node = dfs_cycle(graph, i, history, seen, finished);
            if (cycle_node) {
                const auto cycle_nodes = reconstruct(cycle_node.value(), history);
                max_cycle = size(cycle_nodes);
                break;
            }
        }
        int diameter = 0;
        for (size_t i = 0; i < N; i++) {
            vector<bool> visited(N);
            const auto [dist, far_node] = dfs_far(graph, i, visited);
            diameter = max(diameter, static_cast<int>(dist));
        }

        if (max_cycle > diameter) {
            max_cycle;
        }
        else {
            return diameter;
        }
    }
};

void test(vector<int>&& favorite) {
    cout << Solution().maximumInvitations(favorite) << endl;
}
int main()
{
    test(get_list_int("[3,0,1,4,1]"));
    test(get_list_int("[2,2,1,2]"));
    test(get_list_int("[1,2,0]"));
    return 0;
}