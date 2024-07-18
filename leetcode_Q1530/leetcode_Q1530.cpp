// leetcode_Q1530.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    static int get_distance(const vector<bool>& routes1, const vector<bool>& routes2) {
        int index1 = 0;
        int index2 = 0;
        while (index1 < routes1.size() && index2 < routes2.size() && routes1[index1] == routes2[index2]) {
            index1++;
            index2++;
        }
        return static_cast<int>(routes1.size()) - index1 + static_cast<int>(routes2.size()) - index2;
    }

    static void dfs(TreeNode* node, int distance, vector<bool>& route, vector<vector<bool>>& leaves, int& ans) {
        assert(node != nullptr);

        if (node->left == nullptr && node->right == nullptr) {
            for (auto&& leaf : leaves) {
                if (get_distance(route, leaf) <= distance) {
                    ans++;
                }
            }
            leaves.push_back(route);
            return;
        }
        if (node->left != nullptr) {
            route.push_back(false);
            dfs(node->left, distance, route, leaves, ans);
            route.pop_back();
        }
        if (node->right != nullptr) {
            route.push_back(true);
            dfs(node->right, distance, route, leaves, ans);
            route.pop_back();
        }
    }
    int countPairs(TreeNode* root, int distance) {
        if (root == nullptr) {
            return 0;
        }
        vector<bool> route;
        vector<vector<bool>> leaves;
        int ans = 0;
        dfs(root, distance, route, leaves, ans);
        return ans;
    }

    /*
    static int get_distance_bfs(const unordered_map<int, vector<int>>& graph, int start, int destination) {
        
        queue<int> qu;
        unordered_map<int, int> visited;
        visited.insert({ start,0 });
        qu.push(start);

        while (!qu.empty()) {
            const auto current = qu.front();
            qu.pop();
            const auto current_distance = visited[current];
            const auto it = graph.find(current);
            if (it != cend(graph)) {
                for (auto&& next : it->second) {
                    if (next == destination) {
                        return current_distance + 1;
                    }
                    if (visited.count(next) == 0) {
                        visited[next] = current_distance + 1;
                        qu.push(next);
                    }
                }
            }
        }

        return INT_MAX;
    }

    static int naive(const TreeNode* root, int distance) {
        unordered_map<int, vector<int>> graph;
        queue<const TreeNode*> queue_node;
        queue_node.push(root);
        vector<int> leaves;
        while (!queue_node.empty()) {
            const TreeNode* current = queue_node.front();
            queue_node.pop();
            if (current->left == nullptr && current->right == nullptr) {
                leaves.push_back(current->val);
                continue;
            }
            if (current->left != nullptr) {
                graph[current->val].push_back(current->left->val);
                graph[current->left->val].push_back(current->val);
                queue_node.push(current->left);
            }
            if (current->right != nullptr) {
                graph[current->val].push_back(current->right->val);
                graph[current->right->val].push_back(current->val);
                queue_node.push(current->right);
            }
        }
        int ans = 0;
        for (int i = 0; i < leaves.size() - 1; i++) {
            for (int j = i + 1; j < leaves.size(); j++) {
                if (get_distance_bfs(graph, leaves[i], leaves[j]) <= distance){
                    ans++;
                }
            }
        }

        return ans;
    }
    */

};

void test(vector<optional<int>>&& values, int distance) {
    TreeNode* root = create_treenode2(values);
    cout << Solution().countPairs(root, distance) << endl;
}

int main()
{
    test(get_list_optional_int("[1,2,3,null,4]"), 3);
    test(get_list_optional_int("[45,74,16,4,67,72,36,11,50,58,73,59,59,81,null,78,26,43,83,29,17,24,null,100,59,28,null,4,null,69,26,42,58,69,76,null,22,83,54,68,null,42,null,56,1,47,null,65,null,null,null,53,33,16,11,54,70,76,null,2,66,89,null,null,null,89,null,null,81,63,18,null,null,12,14,36,null,48,null,null,94,89,33,48,61,64,20,84,null,98,57,19,null,19,null,90,64,80,null,null,null,37,75,null,null,21,null,null,null,11,null,47,null,null,null,33,null,null,null,7,83,63,32,89,66,43,null,88,27,null,32,null,null,13,69,null,null,1,null,33,null,6,76,null,null,68,22,20,91,80,null,94,null,47,null,null,null,null,null,18,54,79,null,74,11,5,null,38,46,null,null,34,null,97,94,null,null,null,null,9,35,48,22,null,null,null,null,56,null,40,null,null,null,null,null,51,34,92,null,null,null,null,null,100,33,63,7,37,69,51,77,100,22,57,null,null,null,82,29,57,null,37,null,59,null,null,null,74,null,5,null,35,null,null,null,68,null,91,null,22,36,null,null,null,null,55,20,64,null,72,63,4,3,75,56,41,null,77,46,null,null,29,null,22,null,null,null,66,null,null,null,null,null,16,null,52,74,16,37,null,null,31,null,95,14,null,null,null,null,null,null,30,89,null,null,null,null,92,31,89,null,53,73,null,null,74,95,30,null,null,null,92,3,36,null,39,5,null,null,20,64,8,null,40,26,null,null,82,99,5,null,16,null,71,null,76,null,91,null,null,null,93,82,61,83,34,69,23,37,49,null,20,null,null,null,74,59,65,88,null,null,21,null,17,89,null,null,85,95,null,null,null,null,93,2,84,null,60,20,null,null,86,null,null,null,96,null,null,null,55,null,100,15,4,42,62,null,28,null,25,null,null,null,8,3,null,null,45,null,35,64,null,null,null,null,29,null,null,null,null,null,11,39,null,null,78,null,null,null,7,27,null,null,49,null,83,null,null,null,null,null,60,null,63,63,57,85,68,null,71,null,null,null,null,8,null,null,65,null,33,null,22,null,90,null,100,null,83,null,45,null,92,57,null,null,27,39,60,null,24,null,43,null,46,null,50,null,null,null,68,null,83,23,5,null,30,31,37,84,null,null,14,null,20,null,null,null,null,null,72,null,null,null,18,null,18,45,null,null,null,null,null,null,46,31,null,null,null,null,90,null,28,null,null,null,65,57,14,72,34,null,35,36,42,null,34,null,null,33,25,null,59,64,54,66,76,null,null,null,null,null,null,null,null,null,39,null,4,1,94,62,36,39,56,null,null,null,71,null,27,40,null,null,null,null,null,null,null,null,90,null,72,null,null,null,98,53,null,null,null,null,24,null,22,null,null,null,1,63,56,null,85,null,null,null,86,45,71,1,34,null,null,null,92,null,3,null,62,null,null,null,null,null,null,null,96,15,69,null,57,17,76,null,51,null,99,null,82,null,null,null,100,null,null,null,83,null,null,null,92,36,33,null,35,null,78,null,null,null,null,null,18,null,null,null,89,null,76,null,null,null,97,9,3,null,16,null,null,null,37,null,74,null,56,40,35,null,21,85,89,23,29,null,80,null,null,null,28,null,42,null,null,null,null,null,28,1,null,null,100,null,null,null,93,null,39,null,null,null,75,null,90,37,2,null,50,null,48,null,null,null,null,92,33,24,null,null,86,null,86,null,13,71,null,null,2,54,null,null,null,null,null,null,34,null,null,null,89,51,null,null,null,null,97,84,21,null,45,77,74,null,null,null,34,22,76,null,84,null,62,88,null,null,null,null,null,null,97,76,null,null,17,30,36,null,26,null,null,null,null,null,28,59,56,null,23]"), 8);
    test(get_list_optional_int("[15,66,55,97,60,12,56,null,54,null,49,null,9,null,null,null,null,null,90]"), 5);
    test(get_list_optional_int("[1,2,3,4,5,6,7]"), 3);
    test(get_list_optional_int("[7,1,4,6,null,5,3,null,null,null,null,null,2]"), 3);
}