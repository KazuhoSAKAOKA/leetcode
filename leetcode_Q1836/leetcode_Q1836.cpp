// leetcode_Q1836.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        unordered_set<int> exists;
        unordered_set<int> duplicates;
        ListNode* current = head;
        while (current != nullptr) {
            if (exists.count(current->val) > 0) {
                duplicates.insert(current->val);
            }
            else {
                exists.insert(current->val);
            }
            current = current->next;
        }

        ListNode dummy_head;
        dummy_head.next = head;
        ListNode* before = &dummy_head;
        current = head;
        while (current != nullptr) {
            if (duplicates.count(current->val) > 0) {
                before->next = current->next;
                current = current->next;
            }
            else {
                before = current;
                current = current->next;
            }
        }
        return dummy_head.next;
    }
};

void test(vector<int>&& values) {
    ListNode* head = create_listnode(values);
    const ListNode* ans = Solution().deleteDuplicatesUnsorted(head);
    output_listnode(ans);
}

int main()
{
    test(get_list_int("[1,2,3,2]"));
    test(get_list_int("[2,1,1,2]"));
    test(get_list_int("[3,2,2,1,3,2,4]"));
}