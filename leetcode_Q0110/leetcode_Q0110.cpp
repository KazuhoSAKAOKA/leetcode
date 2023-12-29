// leetcode_Q0110.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    static pair<bool, int> isBalanced(TreeNode* node, int depth) {
        if (node == nullptr) { return make_pair(true, depth); }

        const auto left_ret = isBalanced(node->left, depth + 1);
        if (!left_ret.first) { return make_pair(false, 0); }
        const auto right_ret = isBalanced(node->right, depth + 1);
        if (!right_ret.first) { return make_pair(false, 0); }
        if (1 < abs(left_ret.second - right_ret.second)) {
            return make_pair(false, 0);
        }
        return make_pair(true, max(left_ret.second, right_ret.second));
    }

    bool isBalanced(TreeNode* root) {
        return isBalanced(root, 0).first;
    }
};
int main()
{
}

