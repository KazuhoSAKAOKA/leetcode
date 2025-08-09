#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"
using namespace std;
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root != nullptr) {
            map<int, vector<int>> val_map;
            queue<pair<const TreeNode*, int>> q;
            q.push({ root,0 });
            while (!q.empty()) {
                const auto [node, no] = q.front();
                q.pop();
                val_map[no].emplace_back(node->val);
                if (node->left != nullptr) {
                    q.push({ node->left, no - 1 });
                }
                if (node->right != nullptr) {
                    q.push({ node->right, no + 1 });
                }
            }
            for (auto&& [_, list] : val_map) {
                ans.emplace_back(list);
            }
        }
        return ans;
    }
};
static void test(vector<optional<int>>&& values) {
    output_matrix(Solution().verticalOrder(create_treenode2(values)));
}
int main() {
    test(get_list_optional_int("[3,9,20,null,null,15,7]"));
    test(get_list_optional_int("[3,9,8,4,0,1,7]"));
    test(get_list_optional_int("[1,2,3,4,10,9,11,null,5,null,null,null,null,null,null,null,6]"));
    return 0;
}