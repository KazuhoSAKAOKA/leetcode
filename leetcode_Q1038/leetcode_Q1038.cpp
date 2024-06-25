// leetcode_Q1038.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    int rec(TreeNode* node, int greater_sum) {
        if (node == nullptr) {
            return 0;
        }
        const auto right_value = rec(node->right, greater_sum);
        const auto before_value = node->val;
        node->val += right_value + greater_sum;
        const auto left_value = rec(node->left, right_value + before_value + greater_sum);
        return left_value + right_value + before_value;
    }

    TreeNode* bstToGst(TreeNode* root) {
        rec(root, 0);
        return root;
    }
};

void test(vector<optional<int>>&& values) {
    TreeNode* root = create_treenode2(values);
    TreeNode* ans = Solution().bstToGst(root);
    output_treenode(ans);
}

int main()
{
    test(get_list_optional_int("[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]"));
    test(get_list_optional_int("[0,null,1]"));
}