// leetcode_Q0082.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) { return nullptr; }

        ListNode dummy(0, head);

        ListNode* before_ptr = &dummy;
        ListNode* current_ptr = head;
        while (current_ptr != nullptr) {
            bool duplicated = false;
            ListNode* forward_ptr = current_ptr->next;
            while (forward_ptr != nullptr && current_ptr->val == forward_ptr->val) {
                forward_ptr = forward_ptr->next;
                duplicated = true;
            }
            if (duplicated) {
                before_ptr->next = forward_ptr;
                current_ptr = forward_ptr;
            }
            else {
                before_ptr = current_ptr;
                current_ptr = forward_ptr;
            }
        }

        return dummy.next;
    }
};

void test(ListNode* head) {
    const auto* ret = Solution().deleteDuplicates(head);

    while (ret != nullptr) {
        cout << ret->val << ",";
        ret = ret->next;
    }
    cout << endl;
}

vector<ListNode> init_list_node(vector<int>&& list) {
    vector<ListNode> ret(list.size(), ListNode());
    ListNode* after = nullptr;
    size_t index = list.size() - 1;
    for (auto it = crbegin(list); it != crend(list); ++it) {
        ret[index].val = *it;
        ret[index].next = after;
        after = &ret[index];
        index--;
    }
    return ret;
}

int main()
{
    test(&init_list_node({ 1,1,1, })[0]);
    test(&init_list_node({ 1, })[0]);

    test(&init_list_node({ 1,2,3,3,4,4,5 })[0]);
    test(&init_list_node({ 1,1,1,2,3 })[0]);
}

