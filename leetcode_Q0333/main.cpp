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

    static tuple<int, int, int> dfs(const TreeNode* node) {
        if (node == nullptr) {
            return { 0, INT_MAX, INT_MIN };
        }
        int min_value = node->val;
        int max_value = node->val;
        int my_size = 1;
        bool left_ok = false;
        bool right_ok = false;
        const auto [left_size, left_min, left_max] = dfs(node->left);
        if (left_max < node->val) {
            my_size += left_size;
            min_value = min(min_value, left_min);
            left_ok = true;
        }
        const auto [right_size, right_min, right_max] = dfs(node->right);
        if (right_min >= node->val) {
            my_size += right_size;
            max_value = max(max_value, right_max);
            right_ok = true;
        }

        if (left_ok && right_ok) {
            return { my_size, min_value, max_value };
        }
        else {
            return { max(left_size, right_size), INT_MIN, INT_MAX };
        }
    }


    int largestBSTSubtree(TreeNode* root) {
        return get<0>(dfs(root));
    }
};
void test(vector<optional<int>>&& values) {
    cout << Solution().largestBSTSubtree(create_treenode2(values)) << endl;
}
int main() {
    test(get_list_optional_int("[10,5,15,1,8,null,7]"));
    test(get_list_optional_int("[4,2,7,2,3,5,null,2,null,null,null,null,null,1]"));
    return 0;
}