// leetcode_Q1644.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:


    static pair<bool, bool> rec(TreeNode* node, int p, int q, TreeNode*& ans) {
        if (node == nullptr) {
            return { false,false };
        }
        if (ans != nullptr) {
            return { true,true };
        }
        bool pok = false;
        bool qok = false;
        if (p == node->val) {
            pok = true;
        }
        else if (q == node->val) {
            qok = true;
        }
        const auto [left_p, left_q] = rec(node->left, p, q, ans);
        const auto [right_p, right_q] = rec(node->right, p, q, ans);

        if (ans == nullptr && ((pok || left_p || right_p) && (qok || left_q || right_q))) {
            ans = node;
        }
        return { (pok || left_p || right_p), (qok || left_q || right_q) };
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ans = nullptr;

        rec(root, p->val, q->val, ans);

        return ans;
    }
};

void test(vector<optional<int>>&& values, int pval, int qval) {
    TreeNode p(pval);
    TreeNode q(qval);

    output_treenode(Solution().lowestCommonAncestor(create_treenode2(values, &p, &q)));
}
int main()
{
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 5, 1);
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 5, 1);
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 5, 1);
    return 0;
}