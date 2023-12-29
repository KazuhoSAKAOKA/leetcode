// leetcode_Q0061.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) { return nullptr; }
        ListNode* before = nullptr;
        int count = 1;
        {
            ListNode* tail = head;
            while (tail->next != nullptr) {
                tail = tail->next;
                count++;
            }
            tail->next = head;
            before = tail;
        }

        const auto n = count - (k % count);

        ListNode* current = head;
        for (auto i = 0; i < n; i++) {
            before = current;
            current = current->next;
        }
        before->next = nullptr;
        return current;
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

void test(vector<int>&& list, int k) {
    if (list.empty()) {
        output(Solution().rotateRight(nullptr, k));
        return;
    }
    vector<ListNode> listNodes;
    listNodes.reserve(list.size());
    for (int i = 0; i < list.size(); i++) {
        listNodes.emplace_back(ListNode{ list[i], nullptr });
    }
    init_listnode(listNodes);
    output(Solution().rotateRight(&listNodes[0], k));
}

int main()
{
    test({ 1,2,3,4,5 }, 2);
    test({},3);
    test({ 0,1,2 }, 4);
}
