// leetcode_Q101.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <memory>
#include <vector>


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

    bool is_mirror(const TreeNode* left, const TreeNode* right) {
        if (left == nullptr && right == nullptr) {
            return true;
        }
        if (left != nullptr && right != nullptr) {
            if(!is_mirror(left->left, right->right)) {
                return false;
            }
            if (!is_mirror(left->right, right->left)) {
                return false;
            }
            return left->val == right->val;
        }
        return false;
    }


    bool isSymmetric(TreeNode* root) {
        return is_mirror(root->left, root->right);
    }
};

constexpr int INVALID_NODE_VALUE = -999999;

static size_t get_left_child_index(size_t index) {
    return index * 2 + 1;
}
static void NodeSetup(std::vector<TreeNode>& node, size_t index)
{
    if (node[index].val == INVALID_NODE_VALUE) { return; }
    const auto left = get_left_child_index(index);
    const auto right = left + 1;
    if (left < node.size() && node[left].val != INVALID_NODE_VALUE) {
        node[index].left = &node[left];
    }
    if (right < node.size() && node[right].val != INVALID_NODE_VALUE) {
        node[index].right = &node[right];
    }
}

static void check(std::vector<TreeNode>& nodes)
{
    for (size_t index = 0; index < nodes.size(); index++) {
        NodeSetup(nodes, index);
    }

    std::cout << Solution().isSymmetric(&nodes[0]) << std::endl;
}

int main()
{
    

    std::vector<TreeNode> nodes1
    {
        {1,nullptr,nullptr},
        {2,nullptr,nullptr},
        {2,nullptr,nullptr},
        {INVALID_NODE_VALUE,nullptr,nullptr},
        {3,nullptr,nullptr},
        {INVALID_NODE_VALUE,nullptr,nullptr},
        {3,nullptr,nullptr},
    };
    check(nodes1);
    std::vector<TreeNode> nodes2
    {
        {1,nullptr,nullptr},
        {2,nullptr,nullptr},
        {2,nullptr,nullptr},
        {3,nullptr,nullptr},
        {4,nullptr,nullptr},
        {4,nullptr,nullptr},
        {3,nullptr,nullptr},
    };
    check(nodes2);
}

