// leetcode_Q0108.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

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

    static TreeNode* create(vector<int>& nums, size_t index, size_t size)
    {
        if (size == 0) { return nullptr; }
        if (size == 1) {
            return new TreeNode{ nums[index], nullptr, nullptr, };
        }
        const auto mid = size / 2;
        const auto right_size = size - mid - 1;
        TreeNode* left_node = create(nums, index, mid);
        TreeNode* right_node = create(nums, index + mid + 1, right_size);
        TreeNode* node = new TreeNode{
            nums[index + mid],
            left_node,
            right_node,
        };
        return node;
    }


    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return create(nums, 0, nums.size());
    }
};
int main()
{
    std::vector<int> list{ -10,-3, 0, 5, 9, };
    auto* ptr = Solution().sortedArrayToBST(list);
}

