// leetcode_Q0160.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        unordered_set<ListNode*> exists;
        ListNode* current = headA;
        while (current != nullptr) {
            exists.insert(current);
            current = current->next;
        }
        current = headB;
        while (current != nullptr) {
            if (exists.find(current) != cend(exists)) {
                return current;
            }
            exists.insert(current);
            current = current->next;
        }
        return nullptr;
    }
};
int main()
{
}

