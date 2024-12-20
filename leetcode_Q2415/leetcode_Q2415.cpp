// leetcode_Q2415.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        vector<TreeNode*> before;
        before.emplace_back(root);
        int depth = 0;
        while (!before.empty()) {
            vector<TreeNode*> current;
            for (auto&& node : before) {
                if (node->left != nullptr) {
                    current.emplace_back(node->left);
                }
                if (node->right != nullptr) {
                    current.emplace_back(node->right);
                }
            }

            if (depth % 2 == 0) {
                for (int i = 0; i < size(current) / 2; i++) {
                    swap(current[i]->val, current[size(current) - 1 - i]->val);
                }
            }
            depth++;
            before = current;
        }
        return root;
    }
};

void test(vector<optional<int>>&& values) {
    output_treenode(Solution().reverseOddLevels(create_treenode2(values)));
}

int main()
{
    test(get_list_optional_int("[2,3,5,8,13,21,34]"));
    test(get_list_optional_int("[7,13,11]"));
    test(get_list_optional_int("[0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]"));
    return 0;
}