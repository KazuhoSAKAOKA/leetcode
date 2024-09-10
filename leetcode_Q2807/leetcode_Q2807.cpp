// leetcode_Q2807.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;

template <typename T>
T gcd(const T& a, const T& b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* before = head;
        ListNode* current = head->next;
        while (current != nullptr) {
            ListNode* next_node = current->next;
            const auto value = current->val;
            const auto new_val = gcd(before->val, value);
            before->next = new ListNode(new_val, current);
            before = current;
            current = next_node;
        }
        return head;
    }
};

void test(vector<int>&& head_values) {
    output_listnode (Solution().insertGreatestCommonDivisors(create_listnode(head_values)));
}
int main()
{
    test(get_list_int("[18,6,10,3]"));
    test(get_list_int("[7]"));
    return 0;
}