// leetcode_Q0404.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include "./../../utility/TreeNodeUtil.h"

using namespace std;
class Solution {
public:

    static int dfs(const TreeNode* node, bool is_left) {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return is_left ? node->val : 0;
        }
        return dfs(node->left, true) + dfs(node->right, false);
    }

    int sumOfLeftLeaves(TreeNode* root) {
        return dfs(root, false);
    }
};

void test(const std::vector<std::optional<int>>& values) {
    auto* root = create_treenode(values);
    cout << Solution().sumOfLeftLeaves(root) << endl;
}
int main()
{
    test({ 1,2,3,4,5, });
    test({ 3,9,20,nullopt, nullopt, 15, 7 });
    test({ 1, });
}