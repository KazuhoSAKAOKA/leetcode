// leetcode_Q0129.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <string>

#include "./../../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    int rec(TreeNode* node, string& current_values) {
        if(node == nullptr){throw exception(); }
        current_values.push_back(static_cast<char>('0' + node->val));
        if (node->left == nullptr && node->right == nullptr) {
            const int result = stoi(current_values);
            current_values.pop_back();
            return result;
        }
        int sum = 0;
        if (node->left != nullptr) {
            sum += rec(node->left, current_values);
        }
        if (node->right != nullptr) {
            sum += rec(node->right, current_values);
        }
        current_values.pop_back();
        return sum;
    }


    int sumNumbers(TreeNode* root) {
        if(root == nullptr){return 0;}
        string current_values;
        return rec(root, current_values);
    }
};


void test(vector<optional<int>>&& nums) {
    TreeNode* root = create_treenode(nums);
    cout << Solution().sumNumbers(root) << endl;
}

int main()
{
    test({ 1 });
    test({ 1,2,3 });
    test({ 4,9,0,5,1, });
}