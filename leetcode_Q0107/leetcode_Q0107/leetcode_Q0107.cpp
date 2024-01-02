// leetcode_Q0107.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <queue>


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

    void DFS(const TreeNode* node, int depth, vector<vector<int>>& list) {
        if (node == nullptr) {
            return;
        }

        if (list.size() <= depth) {
            list.emplace_back(vector<int>{ node->val });
        }
        else {
            list[depth].emplace_back(node->val);
        }

        DFS(node->left, depth + 1, list);
        DFS(node->right, depth + 1, list);
    }

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> rev;
        DFS(root, 0, rev);
        vector<vector<int>> ans(crbegin(rev), crend(rev));
        return ans;
    }
};


void test(vector<optional<int>>&& list) {
}

int main()
{
}