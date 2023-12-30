// leetcode_Q0102.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include <queue>

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
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;
        if (root == nullptr) { return ans; }
        using queue_type = queue<pair<TreeNode*, int>>;
        queue_type work_queue;

        work_queue.push(make_pair(root, 0));

        while (!work_queue.empty()) {
            const auto [node, level] = work_queue.front();
            work_queue.pop();
            if (ans.size() == level) {
                ans.emplace_back(vector<int>());
            }
            ans.back().emplace_back(node->val);
            if (node->left != nullptr) {
                work_queue.push(make_pair(node->left, level + 1));
            }
            if (node->right != nullptr) {
                work_queue.push(make_pair(node->right, level + 1));
            }
        }
        return ans;
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
    const auto ans = Solution().levelOrder(node);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    test({ 3,9, 20, nullopt,nullopt, 15,7, });
    test({ 1, });
    test({ });
}