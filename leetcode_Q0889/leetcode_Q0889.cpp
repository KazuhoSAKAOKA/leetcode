// leetcode_Q0889.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"
using namespace std;
class Solution {
public:
    static TreeNode* rec(const vector<int>& preorder, size_t& preorder_index, const vector<int>& postorder, size_t& postorder_index) {
        if (size(preorder) == preorder_index) {
            return nullptr;
        }
        const auto cur_preorder_index(preorder_index);
        const auto cur_postordr_index(postorder_index);
        const int cur_val = preorder[cur_preorder_index];
        const auto it_begin = next(cbegin(postorder), cur_postordr_index);
        const auto it = find(it_begin, cend(postorder), cur_val);
        if (it == cend(postorder)) {
            return nullptr;
        }
        TreeNode* node = new TreeNode(cur_val);
        preorder_index++;
        if (postorder[postorder_index] != cur_val) {
            node->left = rec(preorder, preorder_index, postorder, postorder_index);
            if (postorder[postorder_index] != cur_val) {
                node->right = rec(preorder, preorder_index, postorder, postorder_index);
            }
        }
        postorder_index++;
        return node;
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        size_t i = 0;
        size_t j = 0;
        return rec(preorder, i, postorder, j);
    }
};

void test(vector<int>&& preorder, vector<int>&& postorder) {
    output_treenode(Solution().constructFromPrePost(preorder, postorder));
}

int main()
{
    test(get_list_int("[3,4,1,2]"), get_list_int("[1,4,2,3]"));
    test(get_list_int("[1,2,4,5,3,6,7]"), get_list_int("[4,5,2,6,7,3,1]"));
    test(get_list_int("[1]"), get_list_int("[1]"));
    return 0;
}