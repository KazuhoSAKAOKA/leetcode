// leetcode_Q0543.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>

#include "./../../utility/TreeNodeUtil.h"
using namespace std;

class Solution {
public:

    static int dfs(const TreeNode* node, int current_depth, int& max_length) {
        if (node->left == nullptr && node->right == nullptr) {
            return current_depth;
        }

        int left_depth = current_depth;
        int right_depth = current_depth;

        if (node->left != nullptr) {
            left_depth = dfs(node->left, current_depth + 1, max_length);

        }
        if(node->right != nullptr) {
            right_depth = dfs(node->right, current_depth + 1, max_length);
            
        }

        max_length = max(max_length, (left_depth - current_depth) + (right_depth - current_depth));
        return max(left_depth, right_depth);
    }


    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) { return 0; }
        int max_length = 0;
        dfs(root, 0, max_length);
        return max_length;
    }
};


void test(std::vector<std::optional<int>>&& nodes) {
    auto root = create_treenode(nodes);
    cout << Solution().diameterOfBinaryTree(root) << endl;
}


int main()
{
    test({ 1,2,3,4,5, });
    test({ 1,2,});

}