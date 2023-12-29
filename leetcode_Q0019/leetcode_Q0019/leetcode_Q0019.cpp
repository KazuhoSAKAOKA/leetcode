// leetcode_Q0019.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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

class Solution {
public:


    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* forward_ptr = head;
        ListNode* backward_ptr = head;

        for (int i = 0; i < n; i++) {
            if (forward_ptr == nullptr) { return head; }
            forward_ptr = forward_ptr->next;
        }
        if (forward_ptr == nullptr) { return head->next; }
        while (forward_ptr->next != nullptr) {
            forward_ptr = forward_ptr->next;
            backward_ptr = backward_ptr->next;
        }
        backward_ptr->next = backward_ptr->next->next;
        return head;
    }
};

void init_listnode(vector<ListNode>& listnode) {
    for (int i = 1; i < listnode.size(); i++) {
        listnode[i - 1].next = &listnode[i];
    }
}

void output(const ListNode* head) {
    const ListNode* current = head;
    while (current != nullptr) {
        cout << current->val << ",";
        current = current->next;
    }
    cout << endl;
}

void test(vector<int>&& list, int n) {
    vector<ListNode> listNodes;
    listNodes.reserve(list.size());
    for (int i = 0; i < list.size(); i++) {
        listNodes.emplace_back(ListNode{ list[i], nullptr });
    }
    init_listnode(listNodes);

    output(Solution().removeNthFromEnd(&listNodes[0], n));
}

int main()
{
    test({ 1,2 }, 2);
    test({ 1,2,3,4,5 }, 2);
    test({ 1 }, 1);
    test({ 1,2 }, 1);
}

