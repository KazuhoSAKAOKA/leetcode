// leetcode_Q1367.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static bool rec(const ListNode* ln, const TreeNode* tn, bool is_head) {
        if (ln == nullptr) {
            return true;
        }
        if (tn == nullptr) {
            return false;
        }
        const auto value = ln->val;
        if (is_head) {
            if (value == tn->val) {
                if (rec(ln->next, tn->left, false)) {
                    return true;
                }
                if (rec(ln->next, tn->right, false)) {
                    return true;
                }
            }
            if (rec(ln, tn->left, true)) {
                return true;
            }
            if (rec(ln, tn->right, true)) {
                return true;
            }
        }
        else {
            if (value == tn->val) {
                return rec(ln->next, tn->left, false) || rec(ln->next, tn->right, false);
            }
        }
        return false;
    }


    bool isSubPath(ListNode* head, TreeNode* root) {
        return rec(head, root, true);
    }
};

void test(vector<int>&& head_values, vector<optional<int>>&& root_values) {
    cout << Solution().isSubPath(create_listnode(head_values), create_treenode2(root_values)) << endl;
}

int main()
{
    test(get_list_int("[1,10]"), get_list_optional_int("[1,null,1,10,1,9]"));
    test(get_list_int("[1,4,2,6]"), get_list_optional_int("[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]"));
    test(get_list_int("[4,2,8]"), get_list_optional_int("[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]"));
    test(get_list_int("[1,4,2,6,8]"), get_list_optional_int("[1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]"));
    return 0;
}
