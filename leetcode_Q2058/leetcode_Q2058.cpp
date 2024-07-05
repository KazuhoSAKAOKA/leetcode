// leetcode_Q2058.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:

    static bool is_positive(int value) {
        return value > 0;
    }

    static void rec(const ListNode* head, int index, int state, int before_value, optional<int> far_point, optional<int> near_point, pair<int, int>& current) {
        if (head == nullptr) {
            return;
        }

        int current_state;

        if (before_value == head->val) {
            current_state = 0;
        }
        else {
            if (state != 0 && is_positive(state) == is_positive(before_value - head->val)) {
                //critical point
                if (!far_point.has_value()) {
                    far_point = index - 1;
                    near_point = index - 1;
                }
                else {
                    current.first = min(current.first, index - 1 - near_point.value());
                    current.second = index - 1 - far_point.value();
                    near_point = index - 1;
                }
            }
            current_state = head->val - before_value;
        }
        rec(head->next, index + 1, current_state, head->val, far_point, near_point, current);
    }

    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (head == nullptr) { return { -1,-1 }; }
        pair<int, int> p{ INT_MAX,-1 };
        rec(head, 0, 0, head->val, nullopt, nullopt, p);
        if (p.first == INT_MAX) {
            return { -1,-1 };
        }
        return vector<int>{p.first, p.second};
    }
};

void test(vector<int>&& values) {
    ListNode* head = create_listnode(values);
    const auto ans = Solution().nodesBetweenCriticalPoints(head);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(get_list_int("[3,1]"));
    test(get_list_int("[5,3,1,2,5,1,2]"));
    test(get_list_int("[1,3,2,2,3,2,2,2,7]"));
}