// leetcode_Q1740.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <cassert>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static pair<optional<int>, optional<int>> rec(const TreeNode* node, int p, int q, int depth, optional<int>& ans) {
        if (node == nullptr) {
            return { nullopt, nullopt };
        }

        const auto [left_p, left_q] = rec(node->left, p, q, depth + 1, ans);
        if (ans.has_value()) {
            return { nullopt, nullopt };
        }
        const auto [right_p, right_q] = rec(node->right, p, q, depth + 1, ans);
        if (ans.has_value()) {
            return { nullopt, nullopt };
        }

        optional<int> pret = nullopt;
        optional<int> qret = nullopt;

        if (node->val == p) {
            assert(!left_p.has_value() || !right_p.has_value());
            if (left_q.has_value()) {
                ans = left_q.value() - depth;
                return { nullopt, nullopt };
            }
            if (right_q.has_value()) {
                ans = right_q.value() - depth;
                return { nullopt, nullopt };
            }
            pret = depth;
        }
        else if (node->val == q) {
            assert(!left_q.has_value() || !right_q.has_value());
            if (left_p.has_value()) {
                ans = left_p.value() - depth;
                return { nullopt, nullopt };
            }
            if (right_p.has_value()) {
                ans = right_p.value() - depth;
                return { nullopt, nullopt };
            }
            qret = depth;
        }
        else {
            if (left_p.has_value() && right_q.has_value()) {
                ans = (left_p.value() - depth) + (right_q.value() - depth);
                return { nullopt, nullopt };
            }
            else if (left_q.has_value() && right_p.has_value()) {
                ans = (left_q.value() - depth) + (right_p.value() - depth);
                return { nullopt,nullopt };
            }

            if (left_p.has_value()) {
                pret = left_p;
            }
            else if (right_p.has_value()) {
                pret = right_p;
            }

            if (left_q.has_value()) {
                qret = left_q;
            }
            else if (right_q.has_value()) {
                qret = right_q;
            }
        }

        return { pret, qret };
    }

    int findDistance(TreeNode* root, int p, int q) {
        if (p == q) { return 0; }//edge
        optional<int> ans = nullopt;
        rec(root, p, q, 0, ans);
        return ans.value();
    }
};

void test(vector<optional<int>>&& values, int p, int q) {
    TreeNode* root = create_treenode2(values);
    cout << Solution().findDistance(root, p, q) << endl;
}

int main()
{
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 6, 2);
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 5, 0);
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 5, 7);
    test(get_list_optional_int("[3,5,1,6,2,0,8,null,null,7,4]"), 5, 5);
    return 0;
}