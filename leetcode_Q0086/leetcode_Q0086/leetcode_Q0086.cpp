// leetcode_Q0086.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
    ListNode* partition(ListNode* head, int x) {
        ListNode dummy(0, head);
        ListNode* current_ptr = head;
        ListNode* partition_ptr = &dummy;
        ListNode* before_ptr = partition_ptr;
        while (current_ptr != nullptr) {
            if (current_ptr->val < x) {
                if (partition_ptr->next != current_ptr) {
                    before_ptr->next = current_ptr->next;
                    current_ptr->next = partition_ptr->next;
                    partition_ptr->next = current_ptr;
                    partition_ptr = partition_ptr->next;
                    current_ptr = before_ptr->next;
                }
                else {
                    partition_ptr = current_ptr;
                    before_ptr = partition_ptr;
                    current_ptr = current_ptr->next;
                }
            }
            else {
                before_ptr = current_ptr;
                current_ptr = current_ptr->next;
                //partition_ptr = partition_ptr->next;
            }
        }

        return dummy.next;
    }
};


vector<ListNode> init_list_node(const vector<int>& nums) {
    vector<ListNode> ret(nums.size(), ListNode{ 0, nullptr });
    ListNode* before = nullptr;
    for (int i = nums.size() - 1; i >= 0; i--) {
        ret[i].val = nums[i];
        ret[i].next = before;
        before = &ret[i];
    }
    return ret;
}

void test(vector<int>&& nums, int x) {
    if (nums.size() == 0) {
        ListNode* head = Solution().partition(nullptr, x);
        cout << "null" << endl;
        return;
    }

    auto items = init_list_node(nums);
    ListNode* head = Solution().partition(&items[0], x);
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val << ",";
        current = current->next;
    }
    cout << endl;
}

int main()
{
    test({  }, 3);
    test({ 1 }, 3);
    test({ 3 }, 3);
    test({ 1,4,3,2,5,2 }, 3);
    test({ 2,1 }, 2);
}

