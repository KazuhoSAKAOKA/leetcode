// leetcode_Q1580.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    struct state {
        const vector<int>& warehouse;
        vector<int> from_left;
        vector<int> from_right;

        inline bool full() const { return from_left.size() + from_right.size() >= warehouse.size(); }

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

        bool allow_from_right(int height) const {
            if (full()) {
                return false;
            }
            if (height > warehouse[warehouse.size() - 1]) {
                return false;
            }
            for (int i = 0; i < from_right.size(); i++) {
                if (from_right[i] > warehouse[warehouse.size() - from_right.size() - 1 + i]) {
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
        bool try_push_from_right(int height) {
            if (!allow_from_right(height)) {
                return false;
            }
            from_right.push_back(height);
            return true;
        }

        void pop_left() {
            from_left.pop_back();
        }
        void pop_right() {
            from_right.pop_back();
        }

    };

    static int rec(state& st, const vector<int>& boxes, int index) {
        if (boxes.size() == index) {
            return 0;
        }
        int max_count = 0;
        if (st.try_push_from_left(boxes[index])) {
            max_count = max(max_count, rec(st, boxes, index + 1) + 1);
            st.pop_left();
        }
        if (st.try_push_from_right(boxes[index])) {
            max_count = max(max_count, rec(st, boxes, index + 1) + 1);
            st.pop_right();
        }
        return max_count;
    }
    static int tle(vector<int>& boxes, vector<int>& warehouse) {
        sort(begin(boxes), end(boxes));

        state st{
            warehouse,
            vector<int>(),
            vector<int>(),
        };

        const auto ans = rec(st, boxes, 0);
        return ans;
    }

    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        sort(begin(boxes), end(boxes), [](const auto& a, const auto& b) {return a > b; });
        int l = 0;
        int r = warehouse.size() - 1;
        int index = 0;
        int count = 0;
        while (index < boxes.size() && l <= r) {
            if (boxes[index] > warehouse[l] && boxes[index] > warehouse[r]) {
            }
            else {
                if (boxes[index] <= warehouse[l] && boxes[index] <= warehouse[r]) {
                    if (warehouse[l] < warehouse[r]) {
                        r--;
                    }
                    else {
                        l++;
                    }
                }
                else {
                    if (boxes[index] <= warehouse[l]) {
                        l++;
                    }
                    else {
                        r--;
                    }
                }
                count++;
            }
            index++;
        }
        
        return count;
    }
};

void test(vector<int>&& boxes, vector<int>&& warehouse) {
    cout << Solution().maxBoxesInWarehouse(boxes, warehouse) << endl;
}
int main()
{
    test(get_list_int("[4,3,4,1]"), get_list_int("[5,3,3,4,1]"));
    test(get_list_int("[1,2,2,3,4]"), get_list_int("[3,4,1,2]"));
    test(get_list_int("[3,5,5,2]"), get_list_int("[2,1,3,4,5]"));
}