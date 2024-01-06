// leetcode_Q0117.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>

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
            }
            if ((*it)->right != nullptr) {
                next.emplace_back((*it)->right);
            }
            ++it;
            for (; it != end(current); ++it) {
                auto& node = *it;
                before->next = *it;
                if (node->left != nullptr) {
                    next.emplace_back(node->left);
                }
                if (node->right != nullptr) {
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

void test(vector<optional<int>>&& list) {
    Node* root = nullptr;

    if (!list.empty() && list.front().has_value()) {
        int index = 0;
        root = new Node(list.front().value(), nullptr, nullptr, nullptr);
        index++;
        vector<Node*> current{ root };
        vector<Node*> next;
        bool exist = true;
        while (index < list.size()) {
            for (auto&& node : current) {
                auto left_option_value = list[index++];
                if (left_option_value.has_value()) {
                    node->left = new Node(left_option_value.value(), nullptr, nullptr, nullptr);
                    exist = true;
                }
                next.emplace_back(node->left);
                if (list.size() == index) {
                    break;
                }
                auto right_option_value = list[index++];
                if (right_option_value.has_value()) {
                    node->right = new Node(right_option_value.value(), nullptr, nullptr, nullptr);
                    exist = true;
                }
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
    test({ 1,2,3,4,5,nullopt,7, });
}

