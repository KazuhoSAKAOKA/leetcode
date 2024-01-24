// leetcode_Q1457.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <unordered_map>

#include "../../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    bool is_pseudo_palindromic(unordered_map<int, int>& current_node_values) {
        bool exist_odd = false;
        for (auto&& [_ignore, count] : current_node_values) {
            if (count % 2 != 0) {
                if (exist_odd) {
                    return false;
                }
                exist_odd = true;
            }
        }
        return true;
    }

    int rec(const TreeNode* node, unordered_map<int, int>& current_node_values) {

        current_node_values[node->val]++;

        if (node->left == nullptr && node->right == nullptr) {
            const auto count_leaf = is_pseudo_palindromic(current_node_values) ? 1 : 0;
            current_node_values[node->val]--;
            return count_leaf;
        }
        int count = 0;

        if (node->left != nullptr) {
            count += rec(node->left, current_node_values);
        }
        if (node->right != nullptr) {
            count += rec(node->right, current_node_values);
        }
        current_node_values[node->val]--;
        return count;
    }

    int pseudoPalindromicPaths(TreeNode* root) {
        unordered_map<int, int> current_node_values;
        return rec(root, current_node_values);
    }
};

void test(vector<optional<int>>&& nums) {
    TreeNode* root = create_treenode(nums);
    cout << Solution().pseudoPalindromicPaths(root) << endl;
}

int main()
{
    test({ 2, 
        3, 1, 
        3, 1, nullopt, 1 });
    test({ 2
        , 1, 1, 
        1,3, nullopt, nullopt, 
        nullopt, nullopt, nullopt, 1,});
    test({ 1 });

}