// leetcode_Q2331.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>

#include "./../utility/TreeNodeUtil.h"
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static bool rec(const TreeNode* node) {
        if (node == nullptr) {
            throw std::exception();
        }

        if (node->left == nullptr && node->right == nullptr) {
            return node->val != 0 ? true : false;
        }
        if (node->val == 2) {
            return rec(node->left) || rec(node->right);
        }
        else {
            return rec(node->left) && rec(node->right);
        }
    }

    bool evaluateTree(TreeNode* root) {
        if (root == nullptr) {
            return false;
        }
        return rec(root);
    }
};

void test(vector<optional<int>>&& values) {
    TreeNode* root = create_treenode2(values);
    cout << Solution().evaluateTree(root) << endl;
}

const string example_1 = "[2,1,3,null,null,0,1]";
const string example_2 = "[0]";
int main(){
    test(get_list_optional_int(example_1));
    test(get_list_optional_int(example_2));
}

