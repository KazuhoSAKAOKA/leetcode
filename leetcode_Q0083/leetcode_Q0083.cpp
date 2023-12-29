#include <iostream>


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
        auto* current = head;
        auto* before = head;

        while (current != nullptr)
        {
            if (before->val == current->val)
            {
                auto* next = current->next;
                before->next = next;
            }
            else
            {
                before = current;
                current = current->next;
            }
        }
        return head;
    }
};
int main()
{
    std::cout << "Hello World!\n";
}
