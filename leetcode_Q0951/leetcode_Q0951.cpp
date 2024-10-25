// leetcode_Q0951.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static bool dfs(const TreeNode* node1, const TreeNode* node2) {
        if (node1 == nullptr || node2 == nullptr) {
            return node1 == node2;
        }
        if (node1->val != node2->val) {
            return false;
        }
        if (dfs(node1->left, node2->right) && dfs(node1->right, node2->left)) {
            return true;
        }
        if (dfs(node1->left, node2->left) && dfs(node1->right, node2->right)) {
            return true;
        }
        return false;
    }
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        return dfs(root1, root2);
    }
};

void test(vector<optional<int>>&& values1, vector<optional<int>>&& values2) {
    cout << Solution().flipEquiv(create_treenode2(values1), create_treenode2(values2)) << endl;
}
int main()
{
    test(get_list_optional_int("[1,2,3,4,5,6,null,null,null,7,8]"), get_list_optional_int("[1,3,2,null,6,4,5,null,null,null,null,8,7]"));
    test(get_list_optional_int("[]"), get_list_optional_int("[]"));
    test(get_list_optional_int("[]"), get_list_optional_int("[1]"));
    return 0;
}