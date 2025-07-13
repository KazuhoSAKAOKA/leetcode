#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    static TreeNode* find_successor(TreeNode* node, TreeNode* p, bool& next_switch) {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode* left = find_successor(node->left, p, next_switch);
        if (left != nullptr) { return left; }
        if (next_switch) {
            next_switch = false;
            return node;
        }
        if (node->val == p->val) {
            next_switch = true;
        }
        return find_successor(node->right, p, next_switch);
    }

    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        bool next_switch = false;
        return find_successor(root, p, next_switch);
    }
};

static void test() {

}

int main() {
	return 0;
}