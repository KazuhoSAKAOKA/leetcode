// leetcode_Q0725.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        if (k == 0) {
            return vector<ListNode*>();
        }

        vector<ListNode*> working;
        ListNode* current = head;
        while (current != nullptr) {
            working.emplace_back(current);
            current = current->next;
        }
        vector<ListNode*> ans;
        ans.reserve(k);
        const auto standard_len = size(working) / k;
        const auto forward_size = size(working) % k;
        size_t current_index = 0;
        for (size_t i = 0; i < k; i++) {
            const auto current_size = i < forward_size ? standard_len + 1 : standard_len;
            if (size(working) <= current_index) {
                ans.emplace_back(nullptr);
            }
            else {
                ans.emplace_back(working[current_index]);
                working[current_index + current_size - 1]->next = nullptr;
            }
            current_index += current_size;
        }

        return ans;
    }
};

void test(vector<int>&& values, int k) {
    const auto ans = Solution().splitListToParts(create_listnode(values), k);
    for (auto&& node : ans) {
        output_listnode(node);
    }
}

int main()
{
    test(get_list_int("[1,2,3]"), 5);
    test(get_list_int("[1,2,3,4,5,6,7,8,9,10]"), 3);
    return 0;
}