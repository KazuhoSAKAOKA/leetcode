// leetcode_Q0206.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../../utility/ListNodeUtil.h"

using namespace std;


class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) { return nullptr; }
        ListNode* prev = head;
        ListNode* current = head->next;
        prev->next = nullptr;
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};

void test(vector<int>&& values) {
    output_listnode(Solution().reverseList(create_listnode(values)));
}


int main()
{
    test({ 1,2, });
    test({ 1,2,3, });
    test({ 1, });
    test({});
}