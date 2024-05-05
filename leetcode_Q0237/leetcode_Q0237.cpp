// leetcode_Q0237.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* prev = node;
        ListNode* current = prev->next;

        for(;;) {
            prev->val = current->val;
            
            if (current->next == nullptr) {
                prev->next = nullptr;
                break;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    }
};

void test(vector<int>&& values, int value) {
    ListNode * head = create_listnode(values);
    ListNode* node = head;
    while (node->val != value) {
        node = node->next;
    }
    Solution().deleteNode(node);
    output_listnode(head);
}


int main()
{
    test({ 4,5,1,9, }, 5);
    test({ 4,5,1,9, }, 1);
}