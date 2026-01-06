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
    int maxLevelSum(TreeNode* root) {
        
        long long max_sum = LLONG_MIN;
        int max_level = 0;
        vector<const TreeNode*> before{ root };
        int cur_level = 1;
        while (!before.empty()) {
            vector<const TreeNode*> current;
            long long sum = 0;
            for (auto&& node : before) {
                sum += static_cast<long long>(node->val);
                if (node->left != nullptr) {
                    current.emplace_back(node->left);
                }
                if (node->right != nullptr) {
                    current.emplace_back(node->right);
                }
            }
            if (max_sum < sum) {
                max_sum = sum;
                max_level = cur_level;
            }
            cur_level++;
            swap(before, current);
        }
        return max_level;
    }
};

static void test(vector<optional<int>>&& values) {
    cout << Solution().maxLevelSum(create_treenode2(values)) << endl;
}
int main()
{
    test(get_list_optional_int("[1,7,0,7,-8,null,null]"));
    test(get_list_optional_int("[989,null,10250,98693,-89388,null,null,null,-32127]"));
    return 0;
}