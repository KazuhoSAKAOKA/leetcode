// leetcode_Q1171.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include "./../../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:

    static pair<ListNode*, bool> rec(ListNode* node, int current_sum) {
        if (node == nullptr) {
            return make_pair(nullptr, false);
        }
        const auto new_sum = node->val + current_sum;
        if (new_sum == 0) {
            return make_pair(node, true);
        }
        return rec(node->next, new_sum);
    }


    static pair<ListNode*, bool> erase_zero_subarray(ListNode* head) {
        
        ListNode dummy_head;
        dummy_head.next = head;
        ListNode* prev = &dummy_head;
        ListNode* node = head;

        while (node != nullptr) {
            auto [end_node, eq_zero] = rec(node, 0);
            if (eq_zero) {
                prev->next = end_node->next;
                return make_pair(dummy_head.next, true);
            }
            else {
                prev = node;
                node = node->next;
            }
        }
        return make_pair(dummy_head.next, false);
    }

    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode dummy_head;
        dummy_head.next = head;

        for (;;) {
            auto [new_head, erased] = erase_zero_subarray(dummy_head.next);
            if (erased) {
                dummy_head.next = new_head;
            }
            else {
                break;
            }
        }
        return dummy_head.next;
    }
};

void test(vector<int>&& values) {
    ListNode* head = create_listnode(values);
    ListNode* ans = Solution().removeZeroSumSublists(head);
    output_listnode(ans);
}


int main()
{
    test({ 1,2,-3, 3,1 });
    test({ 1,2,3,-3,4 });
    test({ 1,2,3,-3, -2 });
}