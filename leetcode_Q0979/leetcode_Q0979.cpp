// leetcode_Q0979.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <queue>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;
class Solution {
public:
    struct vertex {
        TreeNode* node;
        vector<int> connects;
    };
    using graph_t = map<int, vertex>;

    static vector<int> djikstra(const graph_t& graph, int s) {
        std::vector<int> costs(graph.size(), std::numeric_limits<int>::max());
        struct point {
            int cost;
            int pos;
            bool operator > (const point& other) const {
                return cost > other.cost;
            }
        };
        std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
        p_queue.push(point{ 0, s });
        costs[s] = 0;
        while (!p_queue.empty()) {
            const auto [current_cost, current] = p_queue.top();
            p_queue.pop();
            if (costs[current] < current_cost) { continue; }
            for (auto&& to : graph.at(current).connects) {
                constexpr int cost = 1;
                if (costs[to] > cost + current_cost) {
                    costs[to] = cost + current_cost;
                    p_queue.push(point{ costs[to] , to });
                }
            }
        }
        return costs;
    }

    static optional<int> travers(TreeNode* node, graph_t& graph) {
        if (node == nullptr) {
            return nullopt;
        }

        const auto key = static_cast<int>(graph.size());
        graph[key] = vertex{node, vector<int>()};

        const auto left_key = travers(node->left, graph);
        if (left_key.has_value()) {
            graph[key].connects.emplace_back(left_key.value());
            graph[left_key.value()].connects.emplace_back(key);

        }
        const auto right_key = travers(node->right,graph);
        if (right_key.has_value()) {
            graph[key].connects.emplace_back(right_key.value());
            graph[right_key.value()].connects.emplace_back(key);
        }
        return key;
    }

    static void rec(const vector<pair<int, vector<int>>>& starts, const vector<int>& ends, int start_index, vector<bool>& used_ends, int current, vector<int>& values) {
        if (start_index == starts.size()) {
            values.emplace_back(current);
            return;
        }
        for (int j = 0; j < ends.size(); j++) {
            if (used_ends[j]) { continue; }
            used_ends[j] = true;
            rec(starts, ends, start_index + 1, used_ends, current + starts[start_index].second[ends[j]], values);
            used_ends[j] = false;
        }
    }
    /// <summary>
    /// TreeNodeからグラフを作って、ダイクストラで距離を計算し、一番安い組み合わせを返す
    /// TLE
    /// </summary>
    /// <param name="root"></param>
    /// <returns></returns>
    static int tle(TreeNode* root) {
        graph_t graph;
        travers(root, graph);

        vector<pair<int, vector<int>>> starts;
        vector<int> ends;
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].node->val > 1) {
                const auto costs = djikstra(graph, i);
                for (int j = 0; j < graph[i].node->val - 1; j++) {
                    starts.emplace_back(make_pair(i, costs));
                }
            }
            else if (graph[i].node->val == 0) {
                ends.emplace_back(i);
            }
        }

        vector<bool> used_starts(starts.size(), false);
        vector<bool> used_ends(ends.size(), false);
        vector<int> values;

        rec(starts, ends, 0, used_ends, 0, values);

        return *min_element(cbegin(values), cend(values));
    }

    static int dfs(TreeNode* node, int& moves) {
        if (node == nullptr) {
            return 0;
        }
        const auto left = dfs(node->left, moves);
        const auto right = dfs(node->right, moves);
        moves += abs(left) + abs(right);
        return  left + right + node->val - 1;
    }

    int distributeCoins(TreeNode* root) {
        int moves = 0;
        dfs(root, moves);
        return moves;
    }
};

void test(vector<optional<int>>&& values) {
    TreeNode* root = create_treenode2(values);
    cout << Solution().distributeCoins(root) << endl;
}

int main()
{
    test(get_list_optional_int("[3,13,1,0,0,null,null,0,0,0,0,0,0,null,null,null,0,0,null,0,null,null,null,null,0,0,0,null,null,null,null,null,0,null,3,0]"));
    test(get_list_optional_int("[0,3,0]"));
    test(get_list_optional_int("[3,0,0]"));
}


