// leetcode_Q0021.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* top = nullptr;
        ListNode* list1Top = list1;
        ListNode* list2Top = list2;

        if (list1Top != nullptr && list2Top != nullptr)
        {
            if (list1Top->val < list2Top->val)
            {
                top = list1Top;
                list1Top = list1Top->next;
            }
            else
            {
                top = list2Top;
                list2Top = list2Top->next;
            }
        }
        else if (list1Top != nullptr)
        {
            top = list1Top;
            list1Top = list1Top->next;
        }
        else if (list2Top != nullptr)
        {
            top = list2Top;
            list2Top = list2Top->next;
        }
        else
        {
            return nullptr;
        }
        ListNode* current = top;



        while (list1Top != nullptr && list2Top != nullptr)
        {
            if (list1Top->val < list2Top->val)
            {
                current->next = list1Top;
                current = list1Top;
                list1Top = list1Top->next;
            }
            else
            {
                current->next = list2Top;
                current = list2Top;
                list2Top = list2Top->next;
            }
        }
        while (list1Top != nullptr)
        {
            current->next = list1Top;
            current = list1Top;
            list1Top = list1Top->next;
        }
        while (list2Top != nullptr)
        {
            current->next = list2Top;
            current = list2Top;
            list2Top = list2Top->next;
        }

        return top;
    }
};



int main()
{
    std::cout << "Hello World!\n";
}

