// leetcode_Q0234.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <stack>
#include <vector>
#include "./../../utility/ListNodeUtil.h"


using namespace std;


class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) { return false; }
        ListNode* fast = head;
        ListNode* slow = head;
        stack<int> past;
        for(;;){
            if (fast == nullptr) {
                break;
            }
            fast = fast->next;
            past.push(slow->val);
            slow = slow->next;
            if (fast == nullptr) {
                if (slow == nullptr) { return true; }
                past.pop();
                break;
            }
            fast = fast->next;
        }

        while (slow != nullptr && !past.empty()) {
            if (slow->val != past.top()) {
                return false;
            }
            slow = slow->next;
            past.pop();
        }

        return slow == nullptr && past.empty();
    }
};

void test(vector<int>&& values) {
    cout << Solution().isPalindrome(create_listnode(values)) << endl;
}
int main()
{
    test({ 1, });
    test({ 1,2,1 });
    test({1,2,2,1});
    test({ 1,2 });
}