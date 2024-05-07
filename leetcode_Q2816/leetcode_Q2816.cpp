// leetcode_Q2816.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:

    static int rec(ListNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int carry = 0;
        if (node->next != nullptr) {
            carry = rec(node->next);
        }
        const auto doubled_value = node->val * 2 + carry;
        node->val = doubled_value % 10;
        return doubled_value / 10;
    }

    ListNode* doubleIt(ListNode* head) {
        if (head == nullptr) { return nullptr; }
        const auto carry = rec(head);
        if (carry == 0) {
            return head;
        }
        ListNode* new_head = new ListNode(carry, head);
        return new_head;
    }
};

void test(vector<int>&& values) {
    auto* head = create_listnode(values);
    const auto* ans = Solution().doubleIt(head);
    output_listnode(ans);
}


int main()
{
    test({ 1,8,9, });
    test({ 9,9,9, });
}