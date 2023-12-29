// leetcode_Q0098.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isValidBST_bt(const TreeNode* node, optional<int> floor, optional<int> ceiling) {
        if (node == nullptr) {
            return true;
        }
        if (floor.has_value() && node->val <= floor.value()) {
            return false;
        }
        if (ceiling.has_value() && ceiling.value() <= node->val) {
            return false;
        }

        if (node->left != nullptr) {
            if (!isValidBST_bt(node->left, floor, node->val)) {
                return false;
            }
        }
        if (node->right != nullptr) {
            if (!isValidBST_bt(node->right, node->val, ceiling)) {
                return false;
            }
        }
        return true;
    }

    bool isValidBST(TreeNode* root) {
        return isValidBST_bt(root, nullopt, nullopt);
    }
};

TreeNode* init(const vector<optional<int>>& values) {
    TreeNode* root = nullptr;

    if (!values.empty() && values[0].has_value()) {
        root = new TreeNode(values[0].value());
        int index = 1;
        vector<TreeNode*> before{ root, };
        vector<TreeNode*> current;
        while (index < values.size()) {
            for (int i = 0; i < before.size(); i++) {
                if (values.size() <= index) { break; }
                if (values[index].has_value()) {
                    current.emplace_back(new TreeNode(values[index].value()));
                    before[i]->left = current.back();
                }
                else {
                    current.emplace_back(nullptr);
                }
                index++;
                if (values.size() <= index) { break; }
                if (values[index].has_value()) {
                    current.emplace_back(new TreeNode(values[index].value()));
                    before[i]->right = current.back();
                }
                else {
                    current.emplace_back(nullptr);
                }
                index++;
            }
            swap(current, before);
            current.clear();
        }
    }

    return root;
}

void test(vector<optional<int>>&& values) {
    TreeNode* node = init(values);
    cout << Solution().isValidBST(node) << endl;
}

int main()
{
    test({ 2,2,2, });
    test({ 2,1,3, });
    test({ 5,1,4,nullopt, nullopt, 3,6, });
}

