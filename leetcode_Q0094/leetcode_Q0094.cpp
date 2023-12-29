// leetcode_Q0094.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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

    static void inorder(TreeNode* node, vector<int>& list) {
        if (node == nullptr) { return; }
        inorder(node->left, list);
        list.push_back(node->val);
        inorder(node->right, list);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> list;
        inorder(root, list);
        return list;
    }
};
int main()
{
    std::cout << "Hello World!\n";
}

