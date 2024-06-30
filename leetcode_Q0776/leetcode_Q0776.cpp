// leetcode_Q0776.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static pair<TreeNode*, TreeNode*> split_inorder(TreeNode* node, int target) {
        if (node == nullptr) {
            return { nullptr,nullptr };
        }

        auto [left1, left2] = split_inorder(node->left, target);
        auto [right1, right2] = split_inorder(node->right, target);
        if (node->val <= target) {
            node->right = right1;
            return { node, right2 };
        }
        else {
            node->left = left2;
            return { left1, node };
        }
    }


    vector<TreeNode*> splitBST(TreeNode* root, int target) {
        auto [root1, root2] = split_inorder(root, target);
        return vector<TreeNode*>{root1, root2,};
    }
};

void test(vector<optional<int>>&& values, int target) {
    TreeNode* root = create_treenode(values);
    const auto ans = Solution().splitBST(root, target);
    for (auto&& node : ans) {
        output_treenode(node);
    }
}

int main()
{
    test(get_list_optional_int("[4,2,6,1,3,5,7]"), 2);
    test(get_list_optional_int("[1]"), 1);
}