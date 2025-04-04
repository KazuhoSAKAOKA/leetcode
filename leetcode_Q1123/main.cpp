#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;


class Solution {
public:

    static pair<TreeNode*, int> dfs(TreeNode* node, int depth) {
        if (node->left == nullptr && node->right == nullptr) {
            return { node, depth };
        }
        if (node->left == nullptr || node->right == nullptr) {
            return node->right == nullptr ? dfs(node->left, depth + 1) : dfs(node->right, depth + 1);
        }
        auto left_ans = dfs(node->left, depth + 1);
        auto right_ans = dfs(node->right, depth + 1);
        if (left_ans.second == right_ans.second) {
            return { node, left_ans.second };
        }
        return left_ans.second > right_ans.second ? left_ans : right_ans;
    }

    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        return dfs(root, 0).first;
    }
};


int main() {
	return 0;
}