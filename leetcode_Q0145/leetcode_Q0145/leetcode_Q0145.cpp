// leetcode_Q0145.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void postorderTraversal(TreeNode* node, vector<int>& list) {
        if (node == nullptr) { return; }
        postorderTraversal(node->left, list);
        postorderTraversal(node->right, list);
        list.push_back(node->val);
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> list;
        postorderTraversal(root, list);
        return list;
    }
};

int main()
{
}

