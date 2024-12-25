// leetcode_Q0515.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) { return ans; }
        vector<const TreeNode*> nexts;
        nexts.emplace_back(root);
        while (!nexts.empty()) {
            vector<const TreeNode*> currents;
            int max_value = INT_MIN;
            for (auto&& node : nexts) {
                max_value = max(max_value, node->val);
                if (node->left != nullptr) {
                    currents.emplace_back(node->left);
                }
                if (node->right != nullptr) {
                    currents.emplace_back(node->right);
                }
            }
            ans.emplace_back(max_value);
            swap(nexts, currents);
        }
        return ans;
    }
};

void test(vector<optional<int>>&& values) {
    output(Solution().largestValues(create_treenode2(values)));
}
int main()
{
    test(get_list_optional_int("[1,3,2,5,3,null,9]"));
    test(get_list_optional_int("[1,2,3]"));
    return 0;
}