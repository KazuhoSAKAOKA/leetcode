// leetcode_Q0141.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* current = head;
        unordered_set<ListNode*> exist;
        while (current != nullptr)
        {
            if (exist.find(current) != cend(exist)) { return true; }
            exist.insert(current);
            current = current->next;
        }
        return false;
    }
};

int main()
{
}

