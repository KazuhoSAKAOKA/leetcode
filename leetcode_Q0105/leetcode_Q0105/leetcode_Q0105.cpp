// leetcode_Q0105.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <span>

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

    int liner_search(const vector<int>& list, int offset, int value) {
        for (int i = offset; i < list.size(); i++) {
            if (list[i] == value) {
                return i;
            }
        }
        return -1;
    }

    pair<TreeNode*, int> build_sub_tree(const vector<int>& preorder, int preorder_index, const vector<int>& inorder, int inorder_offset, int inorder_end) {
        if (inorder_end - inorder_offset <= 0) {
            return make_pair(nullptr, 0);
        }
        if (preorder.size() == preorder_index) {
            return make_pair(nullptr, 0);
        }
        const int value = preorder[preorder_index];

        TreeNode* current_parent_node = new TreeNode(value, nullptr, nullptr);
        
        const int inorder_split_end = liner_search(inorder, inorder_offset, value);
        auto [left_node, left_count] = build_sub_tree(preorder, preorder_index + 1, inorder, inorder_offset, inorder_split_end);
        current_parent_node->left = left_node;

        auto [right_node, right_count] = build_sub_tree(preorder, preorder_index + left_count + 1, inorder, inorder_split_end + 1, inorder_end);
        current_parent_node->right = right_node;

        return make_pair(current_parent_node, left_count + right_count + 1);
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) { return nullptr; }

        auto [root, count] = build_sub_tree(preorder, 0, inorder, 0, static_cast<int>(inorder.size()));
        return root;
    }
};

void test(vector<int>&& preorder, vector<int>&& inorder) {
    TreeNode* ans = Solution().buildTree(preorder, inorder);
}

int main()
{
    test({ 3,9,20,15,7 }, { 9,3,15,20,7 });
    test({-1}, {-1});
}

