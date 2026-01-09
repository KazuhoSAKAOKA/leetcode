#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;
class Solution {
public:

    static int dfs(TreeNode* node, int cur_depth, TreeNode** current_ans, int& max_depth) {
        if (node->left == nullptr && node->right == nullptr) {
            max_depth = max(max_depth, cur_depth);
            if (cur_depth == max_depth) {
                *current_ans = node;
                return cur_depth;
            }
        }

        int left_max = 0;
        if (node->left != nullptr) {
            left_max = dfs(node->left, cur_depth + 1, current_ans, max_depth);
        }
        int right_max = 0;
        if (node->right != nullptr) {
            right_max = dfs(node->right, cur_depth + 1, current_ans, max_depth);
        }
        if (left_max != 0 && right_max != 0) {
            if (left_max == right_max && left_max == max_depth) {
                *current_ans = node;
            }
        }
        return max(left_max, right_max);
    }


    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        TreeNode* ans = nullptr;
        int max_depth = 0;
        dfs(root, 1, &ans, max_depth);
        return ans;
    }
};

static void test(vector<optional<int>>&& values) {
    TreeNode* root = create_treenode2(values);
    const TreeNode* p = Solution().subtreeWithAllDeepest(root);
    output_treenode(p);
}
int main()
{
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"));
    test(get_list_optional_int("[1]"));
    test(get_list_optional_int("[0,1,3,null,2]"));
    return 0;
}