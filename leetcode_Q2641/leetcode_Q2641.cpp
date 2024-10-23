// leetcode_Q2641.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <queue>
#include <map>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        struct info{
            TreeNode* node;
            int depth;
            const TreeNode* parent;
        };

        map<const TreeNode*, int> parents_map;
        vector<int> sums;
        int current_depth = 0;
        queue<info> info_queue;
        info_queue.push(info{ root, 0, nullptr });
        vector<info> current_depth_infos;
        sums.emplace_back(0);

        auto do_change_depth = [&]() {
            const auto current_depth_sum = sums.back();
            for (auto&& inf : current_depth_infos) {
                const auto value = current_depth_sum - parents_map[inf.parent];
                inf.node->val = value;
            }
            current_depth_infos.clear();
            };
        while (!info_queue.empty()) {
            info current = info_queue.front();
            info_queue.pop();

            if (current_depth != current.depth) {
                do_change_depth();
                sums.emplace_back(0);
                current_depth = current.depth;
            }
            sums.back() += current.node->val;
            parents_map[current.parent] += current.node->val;
            if (current.node->left != nullptr) {
                info_queue.push(info{ current.node->left, current.depth + 1, current.node });
            }
            if (current.node->right != nullptr) {
                info_queue.push(info{ current.node->right, current.depth + 1, current.node });
            }
            current_depth_infos.emplace_back(current);
        }
        do_change_depth();


        return root;
    }
};


void test(vector<optional<int>>&& values) {
    output_treenode(Solution().replaceValueInTree(create_treenode2(values)));
}
int main()
{
    test(get_list_optional_int("[5,4,9,1,10,null,7]"));
    test(get_list_optional_int("[3,1,2]"));
    return 0;
}