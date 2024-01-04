// leetcode_Q0113.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../../utility/TreeNodeUtil.h"

using namespace std;

 
class Solution {
public:

    static bool rec(const TreeNode* node, int targetSum, int work_sum, vector<int>& worklist, vector<vector<int>>& ans) {
        if (node == nullptr) {
            return true;
        }
        const int new_sum = work_sum + node->val;
        worklist.emplace_back(node->val);

        bool isLeaf = rec(node->left, targetSum, new_sum, worklist, ans);
        isLeaf &= rec(node->right, targetSum, new_sum, worklist, ans);

        if (isLeaf && new_sum == targetSum) {
            ans.emplace_back(worklist);
        }

        worklist.pop_back();
        return false;
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> work;
        rec(root, targetSum, 0, work, ans);
        return ans;
    }
};


void test(vector<optional<int>>&& data, int targetSum) {
    auto* root = create_treenode(data);
    const auto ans = Solution().pathSum(root, targetSum);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    test({ 5,4,8,11,nullopt,13,4,7,2,nullopt,nullopt,nullopt,nullopt,5,1 }, 22);
    test({ 1,2,3, }, 5);
}

