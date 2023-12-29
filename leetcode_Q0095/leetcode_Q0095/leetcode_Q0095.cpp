// leetcode_Q0095.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
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

    TreeNode* AddToTree(TreeNode* tree, int value) {
        if (value < tree->val) {
            if (tree->left == nullptr) {
                tree->left = new TreeNode(value);
                return tree->left;
            }
            return AddToTree(tree->left, value);
        }
        else {
            if (tree->right == nullptr) {
                tree->right = new TreeNode(value);
                return tree->right;
            }
            return AddToTree(tree->right, value);
        }
    }

    static bool IsEquals(const TreeNode* left, const TreeNode* right) {
        if (left != nullptr && right != nullptr) {
            if (left->val != right->val) {
                return false;
            }
            return IsEquals(left->left, right->left) && IsEquals(left->right, right->right);
        }
        return (left == nullptr) == (right == nullptr);
    }

    vector<TreeNode*> generateTrees(int n) {
        vector<int> list;
        for (int i = 0; i < n; i++) {
            list.emplace_back(i + 1);
        }
        vector<TreeNode*> treeNodes;

        do {
            TreeNode* node = new TreeNode(list[0]);
            for (int i = 1; i < list.size(); i++) {
                AddToTree(node, list[i]);
            }
            if (!any_of(cbegin(treeNodes), cend(treeNodes), [node](auto& v) { return IsEquals(node, v);})) {
                treeNodes.emplace_back(node);
            }
        } while (next_permutation(begin(list), end(list)));

        return treeNodes;
    }
};

void output_tree(TreeNode* node, int depth) {
    if (node == nullptr) { return; }
    cout << node->val << endl;
    if (node->left != nullptr) {
        output_tree(node->left, depth + 1);
    }
    if (node->right != nullptr) {
        output_tree(node->right, depth + 1);
    }

}

void test(int n) {
    const auto trees = Solution().generateTrees(n);
    cout << "begin" << endl;
    for (auto&& tree : trees) {
        output_tree(tree, 0);
        cout << endl;
    }
    cout << "end" << endl;
}

int main()
{
    test(3);
    test(1);
}

