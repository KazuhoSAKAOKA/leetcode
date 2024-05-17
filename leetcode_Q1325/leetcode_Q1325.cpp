// leetcode_Q1325.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static TreeNode* rec(TreeNode* node, int target) {
        if (node == nullptr) {
            return nullptr;
        }

        node->left = rec(node->left, target);
        node->right = rec(node->right, target);

        if (node->left == nullptr && node->right == nullptr && node->val == target) {
            return nullptr;
        }
        return node;
    }

    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        return rec(root, target);
    }
};

void test(vector<optional<int>>&& values, int target) {
    TreeNode* root = create_treenode2(values);
    output_treenode(root);
    const TreeNode* ans = Solution().removeLeafNodes(root, target);
    output_treenode(ans);
}

int main()
{
    test(get_list_optional_int("[5]"), 5);
    test(get_list_optional_int("[1,2,3,2,null,2,4]"), 2);
    test(get_list_optional_int("[1,3,3,3,2]"), 3);
    test(get_list_optional_int("[1,2,null,2,null,2]"), 2);
}