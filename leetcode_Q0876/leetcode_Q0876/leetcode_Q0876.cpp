// leetcode_Q0876.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        auto* slow = head;
        auto* fast = head;

        while (fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
            if (fast->next != nullptr) {
                fast = fast->next;
            }
        }
        return slow;
    }
};

void test(const std::vector<int>& list) {
    auto* head = create_listnode(list);

    auto* ans = Solution().middleNode(head);

    if (ans == nullptr) {
        cout << "nullptr" << endl;
    }
    else {
        cout << ans->val << endl;
    }
}


int main()
{
    test({ 1,2,3,4, });
    test({ 1,2,3,4,5, });
    test({ 1,2,3,4,5,6, });
    test({ 1,2,3,4,5,6,7, });
    test({ 1,2,3,4,5,6,7,8, });
}