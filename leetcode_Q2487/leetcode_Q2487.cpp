// leetcode_Q2487.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:

    static pair<ListNode*, int> rec(ListNode* current) {
        if (current == nullptr) {
            return make_pair(nullptr, INT_MIN);
        }
        if (current->next == nullptr) {
            return make_pair(current, current->val);
        }

        auto [p, v] = rec(current->next);

        if (current->val < v) {
            return make_pair(p, v);
        }
        else {
            current->next = p;
            return make_pair(current, current->val);
        }
    }


    ListNode* removeNodes(ListNode* head) {
        auto [p, _] = rec(head);
        return p;
    }
};

void test(vector<int>&& values) {
    ListNode* head = create_listnode(values);
    const ListNode* ans = Solution().removeNodes(head);
    output_listnode(ans);
}

int main()
{
    test({ 5,2,13,3,8, });
    test({ 1,1,1,1, });
}