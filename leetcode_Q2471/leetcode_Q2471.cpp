// leetcode_Q2471.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:

    static int counting(vector<int>& values) {
        map<int, int> correct_map;
        for (int i = 0; i < size(values); i++) {
            correct_map[values[i]] = i;
        }
        int count = 0;
        int i = 0;
        for (auto&& [k, v] : correct_map) {
            if(v != i){
                const auto other_index = v;
                const auto other = values[i];
                v = i;
                correct_map[other] = other_index;
                swap(values[i], values[other_index]);
                count++;
            }

            i++;
        }
        return count;
    }


    int minimumOperations(TreeNode* root) {
        vector<TreeNode*> nexts;
        nexts.emplace_back(root);
        int count = 0;
        while (!nexts.empty()) {
            vector<int> values;
            vector<TreeNode*> currents;
            for (int i = 0; i < size(nexts); i++) {
                TreeNode* node = nexts[i];
                if (node->left != nullptr) {
                    currents.emplace_back(node->left);
                }
                if (node->right != nullptr) {
                    currents.emplace_back(node->right);
                }

                values.emplace_back(node->val);
            }
            count += counting(values);
            swap(nexts, currents);
        }
        return count;
    }
};

void test(vector<optional<int>>&& values) {
    cout << Solution().minimumOperations(create_treenode2(values)) << endl;
}
int main()
{
    test(get_list_optional_int("[49,45,1,20,46,15,39,27,null,null,null,25]"));
    test(get_list_optional_int("[1,4,3,7,6,8,5,null,null,null,null,9,null,10]"));
    test(get_list_optional_int("[1,3,2,7,6,5,4]"));
    test(get_list_optional_int("[1,2,3,4,5,6]"));
    return 0;
}