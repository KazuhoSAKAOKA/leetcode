// leetcode_Q0144.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

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

    void preorderTraversal(TreeNode* node, vector<int>& list) {
        if (node == nullptr) { return; }
        list.push_back(node->val);
        preorderTraversal(node->left, list);
        preorderTraversal(node->right, list);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> list;
        preorderTraversal(root, list);
        return list;
    }
};


int main()
{
}

