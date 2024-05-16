// leetcode_Q0025.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <stack>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:

    static pair<ListNode*, ListNode*> reverse_k(ListNode* node, int k) {
        stack<ListNode*> st;
        ListNode* current = node;
        while (current != nullptr) {
            st.push(current);
            if (st.size() == k) {
                ListNode* ret_head = st.top();
                ListNode* ret_tail = ret_head->next;
                ListNode* before = st.top();
                st.pop();
                while (!st.empty()) {
                    ListNode* current = st.top();
                    st.pop();
                    before->next = current;
                    before = current;
                }
                current->next = ret_tail;
                return make_pair(ret_head, current);
            }
            current = current->next;
        }
        return make_pair(node, nullptr);
    }


    static ListNode* use_stack(ListNode* head, int k) {
        if (k == 1) { return head; }

        ListNode dummy_head;
        dummy_head.next = head;
        ListNode* before = &dummy_head;

        while (before != nullptr) {
            auto [head_reversed, tail_reversed] = reverse_k(before->next, k);
            before->next = head_reversed;
            before = tail_reversed;
        }
        return dummy_head.next;
    }



    ListNode* reverseLinkedList(ListNode* head, int k) {
        ListNode* new_head = nullptr;
        ListNode* ptr = head;
        while (k > 0) {
            ListNode* next_node = ptr->next;
            ptr->next = new_head;
            new_head = ptr;
            ptr = next_node;
            k--;
        }
        return new_head;
    }
    ListNode* reverseKGroupEditional(ListNode* head, int k) {
        ListNode* ptr = head;
        ListNode* ktail = nullptr;
        ListNode* new_head = nullptr;
        while (ptr != nullptr) {
            int count = 0;
            ptr = head;
            while (count < k && ptr != nullptr) {
                ptr = ptr->next;
                count++;
            }
            if (count == k) {
                ListNode* revHead = this->reverseLinkedList(head, k);
                if (new_head == nullptr) new_head = revHead;
                if (ktail != nullptr) ktail->next = revHead;
                ktail = head;
                head = ptr;
            }
        }
        if (ktail != nullptr) ktail->next = head;
        return new_head == nullptr ? head : new_head;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        return reverseKGroupEditional(head, k);
    }
};


void test(vector<int>&& values, int k) {
    ListNode* head = create_listnode(values);
    const ListNode* ans = Solution().reverseKGroup(head, k);
    output_listnode(ans);
}

const string example_1 = "[1,2,3,4,5]";
const string example_2 = "[1,2,3,4,5]";

const string example_my_1 = "[1,2,3,4,5,6,7,8,9,10]";


int main()
{
    test(get_list_int(example_my_1), 10);
    test(get_list_int(example_1), 2);
    test(get_list_int(example_2), 3);
}