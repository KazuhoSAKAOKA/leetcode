// leetcode_Q0513.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include "./../../utility/TreeNodeUtil.h"
using namespace std;

class Solution {
public:

    static optional<pair<int, int>> dfs(const TreeNode* node, int row) {
        if (node == nullptr) {
            return nullopt;
        }
        const auto left_result = dfs(node->left, row + 1);
        const auto right_result = dfs(node->right, row + 1);

        // is leaf
        if (!left_result.has_value() && !right_result.has_value()) {
            return make_pair(node->val, row);
        }

        if (left_result.has_value() && right_result.has_value()) {
            if (right_result.value().second <= left_result.value().second) {
                return left_result;
            }
            return right_result;
        }
        else {
            return left_result.has_value() ? left_result : right_result;
        }
    }


    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return dfs(root, 0).value().first;
    }
};

void test(std::vector<std::optional<int>>&& values) {
    auto* root = create_treenode(values);
    cout << Solution().findBottomLeftValue(root) << endl;
}


int main()
{
    test({ 2,1,3, });
    test({ 1,2,3,4,nullopt, 5,6,nullopt,nullopt,nullopt, nullopt, 7, });
}