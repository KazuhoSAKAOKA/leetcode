// leetcode_Q0109.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

    TreeNode* sortedListToBST(ListNode* head) {
        if (head == nullptr) { return nullptr; }
        vector<int> list;
        ListNode* current = head;
        while (current != nullptr) {
            list.push_back(current->val);
            current = current->next;
        }
        return create(list, 0, list.size());
    }
};
int main()
{
}

