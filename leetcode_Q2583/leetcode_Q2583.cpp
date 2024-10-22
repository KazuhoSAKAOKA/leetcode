// leetcode_Q2583.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    static void dfs(const TreeNode* node, unordered_map<int, long long>& depth_values_map, int depth) {
        if (node == nullptr) {
            return;
        }
        depth_values_map[depth] += static_cast<long long>(node->val);
        dfs(node->left, depth_values_map, depth + 1);
        dfs(node->right, depth_values_map, depth + 1);
    }

    long long kthLargestLevelSum(TreeNode* root, int k) {
        unordered_map<int, long long> depth_values_map;
        dfs(root, depth_values_map, 0);
        if (size(depth_values_map) < k) {
            return -1;
        }
        vector<long long> list;
        list.reserve(size(depth_values_map));
        for (auto&& [_, v] : depth_values_map) {
            list.emplace_back(v);
        }
        sort(begin(list), end(list), std::greater<long long>());
        return list[k - 1];
    }
};

void test(vector<optional<int>>&& values, int k) {
    auto* root = create_treenode2(values);
    cout << Solution().kthLargestLevelSum(root, k) << endl;
}

int main()
{
    test(get_list_optional_int("[5,8,9,2,1,3,7,4,6]"), 2);
    test(get_list_optional_int("[1,2,null,3]"), 1);
    return 0;
}