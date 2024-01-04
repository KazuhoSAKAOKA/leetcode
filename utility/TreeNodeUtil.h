#pragma once
#include <vector>
#include <optional>
#include <utility>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/// <summary>
/// TreeNode構築
/// </summary>
/// <param name="values">完全二分木として指定、nulloptの子ノードもnullopt指定する必要がある</param>
/// <returns></returns>
TreeNode* create_treenode(const std::vector<std::optional<int>>& values) {
    TreeNode* root = nullptr;

    if (!values.empty() && values[0].has_value()) {
        root = new TreeNode(values[0].value());
        int index = 1;
        std::vector<TreeNode*> before{ root, };
        std::vector<TreeNode*> current;
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
            std::swap(current, before);
            current.clear();
        }
    }

    return root;
}


