// leetcode_Q2181.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"
using namespace std;

class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        if (head->val != 0) {
            return nullptr;
        }
        ListNode dummy_head{ 0, nullptr };
        ListNode* tail = &dummy_head;
        ListNode* current = head->next;
        int current_value = 0;
        while (current != nullptr) {
            if (current->val == 0) {
                tail->next = new ListNode(current_value, nullptr);
                tail = tail->next;
                current_value = 0;
            }
            else {
                current_value += current->val;
            }
            current = current->next;
        }
        return dummy_head.next;
    }
};

void test(vector<int>&& values) {
    ListNode* head = create_listnode(values);
    const ListNode* ans = Solution().mergeNodes(head);
    output_listnode(ans);
}

int main()
{
    test(get_list_int("[0,3,1,0,4,5,2,0]"));
    test(get_list_int("[0,1,0,3,0,2,2,0]"));
}