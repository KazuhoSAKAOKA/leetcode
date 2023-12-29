// leetcode_Q0002.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <utility>
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

    pair<int, ListNode*> getValueAndNext(ListNode* node) {
        if (node == nullptr) {
            return make_pair(0, static_cast<ListNode*>(nullptr));
        }
        return make_pair(node->val, node->next);
    }


    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* left = l1;
        ListNode* right = l2;

        ListNode* top = nullptr;
        ListNode* before = nullptr;
        bool overflow = false;
        while (left != nullptr || right != nullptr) {
            auto [v1, leftNext] = getValueAndNext(left);
            auto [v2, rightNext] = getValueAndNext(right);
            left = leftNext;
            right = rightNext;
            int nextVal = v1 + v2 + (overflow ? 1 : 0);
            overflow = false;
            if (9 < nextVal) {
                overflow = true;
                nextVal %= 10;
            }
            ListNode* node = new ListNode(nextVal);
            if (before == nullptr) {
                before = node;
                top = node;
            }
            else {
                before->next = node;
                before = before->next;
            }
        }

        if (overflow) {
            ListNode* node = new ListNode(1);
            before->next = node;
        }
        return top;
    }
};

void outputListNode(ListNode* ptr) {
    ListNode* current = ptr;

    while (current != nullptr) {
        std::cout << current->val << ",";
        current = current->next;
    }
    std::cout << std::endl;
}

void deleteListNode(ListNode* ptr) {
    ListNode* current = ptr;
    while (current != nullptr) {
        ListNode* temp = current->next;
        delete current;
        current = temp;
    }
}

void testListNode(ListNode* l1, ListNode* l2) {
    auto* ptr = Solution().addTwoNumbers(l1, l2);

    outputListNode(ptr);
    deleteListNode(ptr);

}


void setupListNode(vector<ListNode>& list) {
    auto it = begin(list);
    ListNode* before = &(*it);
    ++it;
    for (; it != end(list); ++it) {
        before->next = &(*it);
        before = before->next;
    }
}

int main()
{
    vector<ListNode> left{ {2,nullptr},{4,nullptr}, {3, nullptr}, };
    vector<ListNode> right{ {5,nullptr},{6,nullptr}, {4, nullptr}, };
    setupListNode(left);
    setupListNode(right);

    testListNode(&left[0], &right[0]);

}

