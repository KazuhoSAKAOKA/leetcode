// leetcode_Q1564.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    struct state {
        const vector<int>& warehouse;
        vector<int> from_left;

        inline bool full() const { return from_left.size() >= warehouse.size(); }

        bool allow_from_left(int height) const {
            if (full()) {
                return false;
            }
            if (height > warehouse[0]) {
                return false;
            }
            for (int i = 0; i < from_left.size(); i++) {
                if (from_left[i] > warehouse[from_left.size() - i]) {
                    return false;
                }
            }
            return true;
        }

        bool try_push_from_left(int height) {
            if (!allow_from_left(height)) {
                return false;
            }
            from_left.push_back(height);
            return true;
        }

    };

    int tle(vector<int>& boxes, vector<int>& warehouse) {
        sort(begin(boxes), end(boxes));
        state st{ warehouse, vector<int>() };
        int index = 0;
        while (index < boxes.size() && st.try_push_from_left(boxes[index])) {
            index++;
        }
        return static_cast<int>(st.from_left.size());
    }

    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(begin(boxes), end(boxes));
        stack<int> mono_stack;
        mono_stack.push(0);
        for (int i = 1; i < warehouse.size(); i++) {
            if (warehouse[mono_stack.top()] > warehouse[i]) {
                mono_stack.push(i);
            }
        }
        int before_index = mono_stack.top();
        int current_height = warehouse[before_index];
        int current_count = static_cast<int>(warehouse.size()) - before_index;
        mono_stack.pop();
        for (int i = 0; i < boxes.size(); i++) {
            if (current_count > 0 && boxes[i] <= current_height) {
                current_count--;
                continue;
            }

            while (!mono_stack.empty() && warehouse[mono_stack.top()] < boxes[i]) {
                before_index = mono_stack.top();
                mono_stack.pop();
            }
            if (mono_stack.empty()) {
                return i;
            }
            int pos = mono_stack.top();
            current_height = warehouse[pos];
            mono_stack.pop();
            current_count = before_index - pos;
            before_index = pos;
            current_count--;
        }

        return static_cast<int>(boxes.size());
    }
};

void test(vector<int>&& boxes, vector<int>&& warehouse) {
    cout << Solution().maxBoxesInWarehouse(boxes, warehouse) << endl;
}
int main()
{
    test(get_list_int("[26,33,44,67,66,64,71,78,62,89,24,92,69,23,10,66,18,48,39,17,37,46,27,14,87,19,81,93,77,4,16,82,2,39,57,78,26,35,62,67,66,45,49,71,90,93,59]"), get_list_int("[19,62,8,83,41,17,12,20,12,10,67,55,58,50,50,71,67,50,86,10,55,70,75,49,85,22,46,14,8,7,7,35,46,16,73,86,88,39,79,6,10,56,79]"));
    test(get_list_int("[4,3,4,1]"), get_list_int("[5,3,3,4,1]"));
    test(get_list_int("[1,2,2,3,4]"), get_list_int("[3,4,1,2]"));
    test(get_list_int("[1,2,3]"), get_list_int("[1,2,3,4]"));
}