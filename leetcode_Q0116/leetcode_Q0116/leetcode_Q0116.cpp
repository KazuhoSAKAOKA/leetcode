// leetcode_Q0116.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) { return nullptr; }
        vector<Node*> current{ root };
        vector<Node*> next;
        while (!current.empty()) {
            auto it = begin(current);
            Node* before = *it;
            if ((*it)->left != nullptr) {
                next.emplace_back((*it)->left);
                next.emplace_back((*it)->right);
            }
            ++it;
            for (; it != end(current); ++it) {
                auto& node = *it;
                before->next = *it;
                if (node->left != nullptr) {
                    next.emplace_back(node->left);
                    next.emplace_back(node->right);
                }
                before = node;
            }
            current.clear();
            swap(current, next);
        }
        return root;
    }
};

void test(vector<int>&& list) {
    Node* root = nullptr;

    if (!list.empty()) {
        int index = 0;
        root = new Node(list[0], nullptr, nullptr, nullptr);
        index++;
        vector<Node*> current{ root };
        vector<Node*> next;
        while (index < list.size()) {
            for (auto&& node : current) {
                node->left = new Node(list[index++], nullptr, nullptr, nullptr);
                node->right = new Node(list[index++], nullptr, nullptr, nullptr);
                next.emplace_back(node->left);
                next.emplace_back(node->right);
            }
            current.clear();
            swap(current, next);
        }
    }

    Solution().connect(root);

}

int main()
{
    test({ 1,2,3,4,5,6,7, });
}