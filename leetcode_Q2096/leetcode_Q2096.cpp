// leetcode_Q2096.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static bool dfs(const TreeNode* node, int target, vector<char>& current) {
        if (node == nullptr) {
            return false;
        }
        if (node->val == target) {
            return true;
        }
        if (node->left != nullptr) {
            current.push_back('L');
            if (dfs(node->left, target, current)) {
                return true;
            }
            current.pop_back();
        }
        if (node->right != nullptr) {
            current.push_back('R');
            if (dfs(node->right, target, current)) {
                return true;
            }
            current.pop_back();
        }
        return false;
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        if (startValue == destValue) {
            return "";
        }
        vector<char> to_start_route;
        if (!dfs(root, startValue, to_start_route)) {
            return "";
        }
        vector<char> to_dest_route;
        if (!dfs(root, destValue, to_dest_route)) {
            return "";
        }

        size_t start_index = 0;
        size_t dest_index = 0;
        while (start_index < to_start_route.size() && dest_index < to_dest_route.size() && to_start_route[start_index] == to_dest_route[dest_index]) {
            start_index++;
            dest_index++;
        }

        string ans;
        ans.reserve(to_start_route.size() - start_index + to_dest_route.size() - dest_index);
        ans.append(to_start_route.size() - start_index, 'U');
        for (size_t index = dest_index; index < to_dest_route.size(); index++) {
            ans.append(1, to_dest_route[index]);
        }

        return ans;
    }
};

void test(vector<optional<int>>&& values, int startValue, int destValue) {
    TreeNode* root = create_treenode2(values);
    cout << Solution().getDirections(root, startValue, destValue) << endl;
}
int main()
{
    test(get_list_optional_int("[5,1,2,3,null,6,4]"), 4, 6);
    test(get_list_optional_int("[5,1,2,3,null,6,4]"), 3, 6);
    test(get_list_optional_int("[2,1]"), 2, 1);
}