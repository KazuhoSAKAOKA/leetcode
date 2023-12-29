// leetcode_Q0099.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <stack>

using namespace std;



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    bool isValidBST_bt(const TreeNode* node, optional<int> floor, optional<int> ceiling) {
        if (node == nullptr) {
            return true;
        }
        if (floor.has_value() && node->val <= floor.value()) {
            return false;
        }
        if (ceiling.has_value() && ceiling.value() <= node->val) {
            return false;
        }

        if (node->left != nullptr) {
            if (!isValidBST_bt(node->left, floor, node->val)) {
                return false;
            }
        }
        if (node->right != nullptr) {
            if (!isValidBST_bt(node->right, node->val, ceiling)) {
                return false;
            }
        }
        return true;
    }

    bool isValidBST(TreeNode* root) {
        return isValidBST_bt(root, nullopt, nullopt);
    }

    void detect_invalid_node(TreeNode* node, optional<TreeNode*> floor, optional<TreeNode*> ceiling, vector<TreeNode*>& invalid_nodes) {
        if (node == nullptr) {
            return;
        }
        if (floor.has_value() && node->val <= floor.value()->val) {
            invalid_nodes.emplace_back(node);
            invalid_nodes.emplace_back(floor.value());
            return;
        }
        if (ceiling.has_value() && ceiling.value()->val <= node->val) {
            invalid_nodes.emplace_back(node);
            invalid_nodes.emplace_back(ceiling.value());
            return;
        }

        if (node->left != nullptr) {
            detect_invalid_node(node->left, floor, node, invalid_nodes);
        }
        if (node->right != nullptr) {
            detect_invalid_node(node->right, node, ceiling, invalid_nodes);
        }
    }
    void swap_node(TreeNode* left, TreeNode* right) {
        const auto temp = left->val;
        left->val = right->val;
        right->val = temp;
    }
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> invalid_nodes;

        detect_invalid_node(root, nullopt, nullopt, invalid_nodes);

        if (invalid_nodes.empty()) { return; }

        if (invalid_nodes.size() == 2) {
            swap_node(invalid_nodes[0], invalid_nodes[1]);
            if (isValidBST(root)) {
                return;
            }
            swap_node(invalid_nodes[0], invalid_nodes[1]);
        }
        for (int i = 0; i < invalid_nodes.size(); i++) {
            stack<pair<TreeNode*, bool>> node_stack;
            node_stack.push(make_pair(root, false));
            TreeNode* current_node = invalid_nodes[i];

            while (!node_stack.empty()) {
                auto& pair = node_stack.top();
                TreeNode* current = pair.first;
                node_stack.pop();
                if (!pair.second) {
                    node_stack.push(make_pair(current, true));
                    if (current->left != nullptr) {
                        node_stack.push(make_pair(current->left, false));
                    }
                }
                else {
                    if (current_node != current) {
                        swap_node(current_node, current);
                        if (isValidBST(root)) {
                            return;
                        }
                        swap_node(current_node, current);
                    }
                    if (current->right != nullptr) {
                        node_stack.push(make_pair(current->right, false));
                    }
                }
            }
        }
    }
};

TreeNode* init(const vector<optional<int>>& values) {
    TreeNode* root = nullptr;

    if (!values.empty() && values[0].has_value()) {
        root = new TreeNode(values[0].value());
        int index = 1;
        vector<TreeNode*> before{ root, };
        vector<TreeNode*> current;
        while (index < values.size()) {
            for (int i = 0; i < before.size(); i++) {
                if (values.size() <= index) { break; }
                if (values[index].has_value()) {
                    current.emplace_back(new TreeNode(values[index].value()));
                    before[i]->left = current.back();
                }
                else {
                    current.emplace_back(nullptr);
                }
                index++;
                if (values.size() <= index) { break; }
                if (values[index].has_value()) {
                    current.emplace_back(new TreeNode(values[index].value()));
                    before[i]->right = current.back();
                }
                else {
                    current.emplace_back(nullptr);
                }
                index++;
            }
            swap(current, before);
            current.clear();
        }
    }

    return root;
}

void test(vector<optional<int>>&& values) {
    TreeNode* node = init(values);
    Solution().recoverTree(node);

    //cout <<  << endl;
}

int main()
{
    test({ 3,nullopt, 2, nullopt,nullopt, nullopt,1, });
    test({ 1,3,nullopt, nullopt,2, });
    test({ 3,1,4,nullopt, nullopt, 2 });
}