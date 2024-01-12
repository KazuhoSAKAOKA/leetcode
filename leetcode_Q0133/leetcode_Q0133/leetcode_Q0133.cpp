// leetcode_Q0133.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) { return nullptr; }
        Node* cloned_node = new Node(node->val);
        map<Node*, Node*> map{ {node, cloned_node} };
        queue<Node*> node_queue;
        node_queue.push(node);

        while (!node_queue.empty()) {
            Node* original_node = node_queue.front();
            Node* cloned_current_node = map[original_node];

            node_queue.pop();
            for (Node* connected : original_node->neighbors) {
                auto it = map.find(connected);
                if (it == end(map)) {
                    Node* new_node = new Node(connected->val);
                    map.insert({ connected, new_node });
                    node_queue.push(connected);
                    cloned_current_node->neighbors.emplace_back(new_node);
                }
                else {
                    cloned_current_node->neighbors.emplace_back(it->second);
                }
            }
        }

        return cloned_node;
    }
};

int main()
{
}

