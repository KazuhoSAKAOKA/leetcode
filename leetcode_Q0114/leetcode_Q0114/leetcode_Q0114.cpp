// leetcode_Q0114.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    TreeNode* rec(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        TreeNode* left = node->left;
        TreeNode* right = node->right;

        if (left != nullptr) {
            node->left = nullptr;
            node->right = left;
            TreeNode* temp = rec(left);
            if (right == nullptr) {
                return temp;
            }
            temp->right = right;
            return rec(right);
        }
        else {
            if (right == nullptr) {
                // leaf
                return node;
            }
            return rec(node->right);
        }
    }

    void flatten(TreeNode* root) {
        rec(root);
    }
};

void test(vector<optional<int>>&& list) {
    TreeNode* root = create_treenode(list);
    Solution().flatten(root);
    output_treenode(root);
}

int main()
{
    test({ 1,2, nullopt,3, });
    test({ 1,2,5,3,4,nullopt, 6 });
    test({});
    test({0});
}

