// leetcode_Q1382.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static void inorder(const TreeNode* node, vector<int>& values) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, values);
        values.push_back(node->val);
        inorder(node->right, values);
    }

    static TreeNode* build(const vector<int>& values, int start, int end) {
        if (end - start <= 0) {
            return nullptr;
        }
        const int mid = (start + end) / 2;
        TreeNode* left = build(values, start, mid);
        TreeNode* right = build(values, mid + 1, end);
        TreeNode* node = new TreeNode(values[mid], left, right);
        return node;
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<int> values;
        inorder(root, values);
        return build(values, 0, static_cast<int>(values.size()));
    }
};

void test(vector<optional<int>>&& values) {
    TreeNode* root = create_treenode2(values);
    TreeNode* ans = Solution().balanceBST(root);
    output_treenode(ans);
}

int main()
{
    test(get_list_optional_int("[1,null,2,null,3,null,4,null,null]"));
    test(get_list_optional_int("[2,1,3]"));
}