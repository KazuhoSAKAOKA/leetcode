// leetcode_Q0104.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <utility>

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

    size_t get_max_depth(TreeNode* root, size_t depth) {
        if (root == nullptr) { return depth; }
        return std::max(get_max_depth(root->left, depth + 1), get_max_depth(root->right, depth + 1));
    }


    int maxDepth(TreeNode* root) {
        return static_cast<int>(get_max_depth(root, 0));
    }
};

int main()
{
}

