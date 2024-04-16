// leetcode_Q0623.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    static TreeNode* add_row(TreeNode* node, int val, int depth, bool left) {
        if (node == nullptr) {
            if (depth == 0) {
                return new TreeNode(val);
            }
            else {
                return nullptr;
            }
        }
        if (depth == 0) {
            auto* new_node = new TreeNode(val);
            if (left) {
                new_node->left = node;
            }
            else {
                new_node->right = node;
            }
            return new_node;
        }
        node->left = add_row(node->left, val, depth - 1, true);
        node->right = add_row(node->right, val, depth - 1, false);
        return node;
    }

    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        return add_row(root, val, depth - 1, true);
    }
};

void test(vector<optional<int>>&& values, int val, int depth) {
    auto* root = create_treenode(values);
    auto* ans = Solution().addOneRow(root, val, depth);
    output_treenode(ans);
}

int main()
{
    test({ 4,2,6,3,1,5, }, 1, 1);
    test({ 4,2,6,3,1,5, }, 1, 2);
    test({ 4,2,nullopt, 3,1, }, 1, 3);
}