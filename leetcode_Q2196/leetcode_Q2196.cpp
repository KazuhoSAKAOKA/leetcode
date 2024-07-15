// leetcode_Q2196.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/TreeNodeUtil.h"

using namespace std;

class Solution {
public:
    static TreeNode* create_tree(const unordered_map<int, unordered_map<bool, int>>& descriptions, int parent) {
        const auto it = descriptions.find(parent);
        if (it == cend(descriptions)) {
            return new TreeNode(parent, nullptr, nullptr);
        }

        TreeNode* node = new TreeNode(parent, nullptr, nullptr);
        const auto& inner_map = it->second;
        const auto left_it = inner_map.find(true);
        if (left_it != cend(inner_map)) {
            node->left = create_tree(descriptions, left_it->second);
        }
        const auto right_it = inner_map.find(false);
        if (right_it != cend(inner_map)) {
            node->right = create_tree(descriptions, right_it->second);
        }
        return node;
    }


    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, unordered_map<bool, int>> node_map;
        unordered_set<int> parents;
        unordered_set<int> childs;
        for (auto&& description : descriptions) {
            const auto parent = description[0];
            const auto child = description[1];
            const auto is_left = description[2] != 0;
            const auto [_, r] = node_map[parent].insert(make_pair(is_left, child));
            if (!r) {
                cerr << "invalid";
                return nullptr;
            }
            childs.insert(child);
            parents.insert(parent);
        }
        for (auto&& child : childs) {
            parents.erase(child);
        }
        if (parents.size() != 1) {
            cerr << "invalid";
            return nullptr;
        }

        TreeNode* root = create_tree(node_map, *cbegin(parents));

        return root;
    }
};

void test(vector<vector<int>>&& descriptions) {
    const TreeNode* ans = Solution().createBinaryTree(descriptions);
    output_treenode(ans);
}

int main()
{
    test(get_matrix_int("[[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]"));
    test(get_matrix_int("[[1,2,1],[2,3,0],[3,4,1]]"));
    return 0;
}