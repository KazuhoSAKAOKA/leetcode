// leetcode_Q1110.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static TreeNode* rec(TreeNode* node, const unordered_set<int>& to_delete, vector<TreeNode*>& ans) {
        if (node == nullptr) {
            return nullptr;
        }
        if (to_delete.count(node->val) > 0) {
            TreeNode* left = rec(node->left, to_delete, ans);
            if (left != nullptr) {
                ans.push_back(left);
            }
            TreeNode* right = rec(node->right, to_delete, ans);
            if (right != nullptr) {
                ans.push_back(right);
            }
            node->left = nullptr;
            node->right = nullptr;
            return nullptr;
        }
        node->left = rec(node->left, to_delete, ans);
        node->right = rec(node->right, to_delete, ans);
        return node;
    }

    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> to_delete_set(cbegin(to_delete), cend(to_delete));
        vector<TreeNode*> ans;
        TreeNode* node = rec(root, to_delete_set, ans);
        if (node != nullptr) {
            ans.push_back(node);
        }
        return ans;
    }
};

void test(vector<optional<int>>&& values, vector<int>&& to_delete) {
    TreeNode* root = create_treenode2(values);
    const auto ans = Solution().delNodes(root, to_delete);
    cout << ">>>" << endl;

    for (auto&& node : ans) {
        output_treenode(node);
    }
    cout << "<<<" << endl;
}
int main()
{
    test(get_list_optional_int("[1,2,3,4,5,6,7]"), get_list_int("[3,5]"));
    test(get_list_optional_int("[1,2,4,null,3]"), get_list_int("[3]"));
    return 0;
}