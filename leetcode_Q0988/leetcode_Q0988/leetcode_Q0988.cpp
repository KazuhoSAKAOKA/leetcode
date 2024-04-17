// leetcode_Q0988.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <optional>

#include "./../../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:


    static string rec(const TreeNode* node, const string& current) {
        if (node == nullptr) {
            return current;
        }
        auto temp = static_cast<char>(node->val + 'a') + current;
        if (node->left == nullptr && node->right == nullptr) {
            return temp;
        }
        if (node->left != nullptr && node->right != nullptr) {
            auto left = rec(node->left, temp);
            auto right = rec(node->right, temp);
            return left < right ? left : right;
        }
        if (node->left != nullptr) {
            auto left = rec(node->left, temp);
            return left;
        }
        else {
            auto right = rec(node->right, temp);
            return right;
        }
    }

    string smallestFromLeaf(TreeNode* root) {
        if (root == nullptr) { return ""; }
        return rec(root, "");
    }
};

void test(vector<optional<int>>&& values) {
    auto* root = create_treenode(values);
    cout << Solution().smallestFromLeaf(root) << endl;
}

int main()
{

    test({4,0,1,1,});
    test({ 0,1,2,3,4,3,4, });
    test({ 25,1,3,1,3,0,2, });
    test({ 2,
        2, 1, 
        nullopt,1,0, nullopt,
        nullopt, nullopt, 0,});
}