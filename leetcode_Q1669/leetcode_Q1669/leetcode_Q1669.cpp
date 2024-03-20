// leetcode_Q1669.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "./../../utility/ListNodeUtil.h"
using namespace std;


class Solution {
public:

    static ListNode* next(ListNode* node, int c) {
        ListNode* current = node;
        for (int i = 0; i < c; i++) {
            current = current->next;
        }
        return current;
    }


    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode dummy_head;
        dummy_head.next = list1;

        ListNode* prev_remove = a == 0 ? &dummy_head : next(list1, a - 1);
        ListNode* remove_tail = a == b ? prev_remove->next : next(prev_remove, b - a + 1);
        if (list2 == nullptr) { return list1; }

        ListNode* current = list2;
        while (current->next != nullptr) {
            current = current->next;
        }

        prev_remove->next = list2;
        current->next = remove_tail->next;

        return dummy_head.next;
    }
};

void test(vector<int>&& list1, int a, int b, vector<int>&& list2) {
    auto* list1node = create_listnode(list1);
    auto* list2node = create_listnode(list2);

    output_listnode(Solution().mergeInBetween(list1node, a, b, list2node));
}

int main()
{
    test({ 10, 1, 13, 6, 9, 5 }, 1, 1, { 1000000, 1000001, 1000002 });
    test({ 10, 1, 13, 6, 9, 5 }, 3, 4, { 1000000, 1000001, 1000002 });
    test({ 0,1,2,3,4,5,6 }, 2, 5, { 1000000,1000001,1000002,1000003,1000004 });
}
