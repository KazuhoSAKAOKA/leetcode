// leetcode_Q0024.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    ListNode* swapPairs(ListNode* head) {
        ListNode dummyHead{ 0, head };
        ListNode* previous = &dummyHead;

        while (previous->next != nullptr) {
            ListNode* front = previous->next;
            ListNode* front_2 = front->next;
            if (front_2 == nullptr) {
                break;
            }
            ListNode* front_3 = front_2->next;

            previous->next = front_2;
            front_2->next = front;
            front->next = front_3;

            previous = front;
        }

        return dummyHead.next;
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

void test(vector<int>&& list) {
    if (list.empty()) {
        output(Solution().swapPairs(nullptr));
        return;
    }
    vector<ListNode> listNodes;
    listNodes.reserve(list.size());
    for (int i = 0; i < list.size(); i++) {
        listNodes.emplace_back(ListNode{ list[i], nullptr });
    }
    init_listnode(listNodes);

    output(Solution().swapPairs(&listNodes[0]));
}

int main()
{
    test({ 1,2,3,4 });
    test({});
    test({ 1 });
    test({ 1,2, });
}