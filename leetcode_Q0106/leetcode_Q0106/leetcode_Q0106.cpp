// leetcode_Q0106.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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


    int liner_search(const vector<int>& list, int offset, int value) {
        for (int i = offset; i < list.size(); i++) {
            if (list[i] == value) {
                return i;
            }
        }
        return -1;
    }


    TreeNode* build_sub_tree(
            const vector<int>& inorder, int inorder_begin, int inorder_end,
            const vector<int>& postorder, int postorder_begin, int postorder_end) {
        if (inorder_end - inorder_begin <= 0) {
            return nullptr;
        }
        if (postorder_end - postorder_begin <= 0) {
            return nullptr;
        }
        const int value = postorder[postorder_end - 1];
        TreeNode* current_parent_node = new TreeNode(value, nullptr, nullptr);
        if (postorder_end - postorder_begin == 1) {
            return current_parent_node;
        }
        // left nodeのサイズはinorderでcurrentnodeの値が出てくるまで
        const int inorder_left_node_end = liner_search(inorder, inorder_begin, value);
        const int left_node_size = inorder_left_node_end - inorder_begin;

        auto* left_node = build_sub_tree(
                inorder, inorder_begin, inorder_left_node_end,
                postorder, postorder_begin, postorder_begin + left_node_size);
        current_parent_node->left = left_node;

        auto* right_node = build_sub_tree(
            inorder, inorder_left_node_end + 1, inorder_end,
            postorder, postorder_begin + left_node_size, postorder_end - 1);
        current_parent_node->right = right_node;
        return current_parent_node;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty()) { return nullptr; }

        return build_sub_tree(
            inorder, 0, static_cast<int>(inorder.size()),
            postorder, 0, static_cast<int>(postorder.size()));
    }
};

void output_treenode(const TreeNode* root) {
    using LIST = vector<const TreeNode*>;
    LIST current{ root };
    LIST next;
    bool exist = true;
    while (exist) {
        exist = false;
        for (auto&& node : current) {
            if (node == nullptr) {
                cout << "null,";
                next.emplace_back(nullptr);
                next.emplace_back(nullptr);
            }
            else {
                cout << node->val << ",";
                next.emplace_back(node->left);
                next.emplace_back(node->right);
                exist |= node->left != nullptr || node->right != nullptr;
            }
        }
        swap(current, next);
        next.clear();
    }
    cout << endl;
}

void test(vector<int>&& preorder, vector<int>&& inorder) {
    TreeNode* ans = Solution().buildTree(preorder, inorder);
    output_treenode(ans);
}

int main()
{
    test({ 8,4,9,2,10,5,11,1,12,6,13,3,14,7,15 }, { 8,9,4,10,11,5,2,12,13,6,14,15,7,3,1 });

    //inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
    test({ 9,3,15,20,7 }, { 9,15,7,20,3 });
    test({ -1 }, { -1 });
}