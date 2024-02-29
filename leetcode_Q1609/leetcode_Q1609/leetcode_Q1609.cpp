// leetcode_Q1609.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <iostream>
#include <vector>
#include <queue>

#include <optional>
#include "./../../utility/TreeNodeUtil.h"
using namespace std;


class Solution {
public:


    bool isEvenOddTree(TreeNode* root) {
        if (root == nullptr) { return false; }

        using node_depth = pair<const TreeNode*, int>;

        queue<node_depth> nd_queue;

        nd_queue.push({ root, 0 });
        int current_depth = -1;
        int before_value = 0;
        while (!nd_queue.empty()) {
            auto [node, depth] = nd_queue.front();
            nd_queue.pop();
            if (node->left != nullptr) {
                nd_queue.push({ node->left, depth + 1 });
            }
            if (node->right != nullptr) {
                nd_queue.push({ node->right, depth + 1 });
            }
            if (depth % 2 == node->val % 2) {
                return false;
            }
            if (current_depth != depth) {
                current_depth = depth;
            }
            else {
                if (depth % 2 == 0) {
                    if (before_value >= node->val) {
                        return false;
                    }
                }
                else {
                    if (before_value <= node->val) {
                        return false;
                    }
                }
            }
            before_value = node->val;
        }


        return true;
    }
};

void test(vector<optional<int>>&& values) {
    auto root = create_treenode(values);
    cout << Solution().isEvenOddTree(root) << endl;
}

int main()
{
    test({ 1,10,4,3, nullopt, 7,9, 12,8,nullopt, nullopt,6, nullopt, nullopt, 2, });
    test({ 5, 4,2,3,3,7, });
}