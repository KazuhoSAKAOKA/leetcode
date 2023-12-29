// leetcode_Q0112.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

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

    bool exist(TreeNode* node, int remain) {
        if (node == nullptr) { return false; }
        if (node->left == nullptr && node->right == nullptr) {
            return node->val == remain;
        }
        auto current_remain = remain - node->val;
        if (current_remain < 0) { return false; }
        return exist(node->left, current_remain) || exist(node->right, current_remain);
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return exist(root, targetSum);
    }
};
int main()
{
    std::cout << "Hello World!\n";
}

