// leetcode_Q0092.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr) { return nullptr; }
        ListNode dummyHead{ 0, head };
        if (left < right) {
            ListNode* before = &dummyHead;
            ListNode* current = head;
            int index = 0;
            while (index < left - 1) {
                if (current == nullptr) { return head; }
                before = current;
                current = current->next;
                index++;
            }
            ListNode* leftBeforeNode = before;
            ListNode* leftNode = current;
            ListNode* reverseBefore = current;
            current = current->next;
            index++;
            while (index < right - 1) {
                if (current == nullptr) { return head; }
                ListNode* next = current->next;
                current->next = reverseBefore;
                reverseBefore = current;
                current = next;
                index++;
            }
            ListNode* rightNode = current;

            leftBeforeNode->next = rightNode;
            leftNode->next = rightNode->next;
            rightNode->next = reverseBefore;
        }
        return  dummyHead.next;
    }
};

vector<ListNode> CreateListNode(const vector<int>& nums) {
    ListNode* next = nullptr;
    vector<ListNode> ret(nums.size(), ListNode());
    for (int i = nums.size() - 1; i >= 0; i--) {
        ret[i].val = nums[i];
        ret[i].next = next;
        next = &ret[i];
    }
    return ret;
}

void test(vector<int>&& nums, int left, int right) {
    auto listNodes = CreateListNode(nums);
    ListNode* head = Solution().reverseBetween(&listNodes.front(), left, right);
    while (head != nullptr) {
        cout << head->val;
        head = head->next;
    }
    cout << endl;
}

int main()
{
    test({ 1,2,3,4,}, 1, 4);
    test({ 1,5 }, 1, 2);
    test({ 1,2,3,4,5},2 ,4 );
    test({ 1,2,3,4,5 }, 1, 5);
    test({5},1 ,1 );
}

