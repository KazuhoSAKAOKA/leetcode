// leetcode_Q0143.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>

#include "./../../utility/ListNodeUtil.h"

using namespace std;


class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr) { return; }

        ListNode* fast = head;
        ListNode* slow = head;
        ListNode dummy_head;
        dummy_head.next = head;
        ListNode* before_slow = &dummy_head;
        while(fast != nullptr){
            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
            }
            before_slow = slow;
            slow = slow->next;
        }
        if (slow == nullptr) {
            return;
        }
        before_slow->next = nullptr;
        ListNode* reverse_prev = slow;
        ListNode* reverse_current = reverse_prev->next;
        reverse_prev->next = nullptr;
        while (reverse_current != nullptr) {
            ListNode* next = reverse_current->next;
            reverse_current->next = reverse_prev;
            reverse_prev = reverse_current;
            reverse_current = next;
        }

        ListNode* node1 = head;
        ListNode* node2 = reverse_prev;
        
        while (node1 != nullptr && node2 != nullptr) {
            ListNode* next = node1->next;
            ListNode* next_next = node2->next;
            node1->next = node2;
            node2->next = next;
            node1 = next;
            node2 = next_next;
        }
    }
};

void test(vector<int>&& values) {
    ListNode* head = create_listnode(values);
    Solution().reorderList(head);
    output_listnode(head);
}


int main()
{
    test({ 1 });
    test({ 1,2,3,4 });
    test({ 1,2,3,4,5 });
}