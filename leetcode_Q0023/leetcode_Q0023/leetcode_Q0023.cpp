// leetcode_Q0023.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "../../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:



    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) { return nullptr; }

        ListNode dummy_head;
        ListNode* before = &dummy_head;
        vector<int> values;
        //merge
        for (auto&& node : lists) {
            if (node != nullptr) {
                before->next = node;
                ListNode* ptr = node;
                while (ptr != nullptr) {
                    values.emplace_back(ptr->val);
                    before = ptr;
                    ptr = ptr->next;
                }
            }
        }

        sort(begin(values), end(values));

        ListNode* ptr = dummy_head.next;
        for (auto&& value : values) {
            ptr->val = value;
            ptr = ptr->next;
        }

        return dummy_head.next;
    }
};

void test(const vector<vector<int>>& valuess) {
    vector<ListNode*> lists;
    for (auto&& inner_list : valuess) {
        ListNode* head = create_listnode(inner_list);
        lists.emplace_back(head);
    }
    const ListNode* ans = Solution().mergeKLists(lists);
    output_listnode(ans);
}

int main()
{
    test({ {1, 4, 5}, {1, 3, 4}, {2, 6} });
    test({ });
    test({ {} });
}

