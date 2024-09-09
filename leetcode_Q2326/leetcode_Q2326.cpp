// leetcode_Q2326.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
#include "./../utility/ListNodeUtil.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ans(m, vector<int>(n, -1));
        struct pos {
            int y;
            int x;
        };
        enum class direction {
            right,
            down,
            left,
            up,
        };
        auto next_dir = [](direction dir) {
            if(dir == direction::up){
                return direction::right;
            }
            return static_cast<direction>(static_cast<int>(dir) + 1);
            };

        auto next_pos = [](const pos& p, direction dir)->pos {
            switch (dir) {
            case direction::right:
                return { p.y, p.x + 1 };
            case direction::down:
                return { p.y + 1, p.x };
            case direction::left:
                return { p.y, p.x - 1 };
            case direction::up:
                return { p.y - 1, p.x };
            }
            };

        auto valid_next = [&](const pos& p)->bool {
            if (p.y < 0 || p.x < 0 || m <= p.y || n <= p.x) {
                return false;
            }
            if (ans[p.y][p.x] != -1) {
                return false;
            }
            return true;
            };

        auto get_next = [&](pos& p, direction& dir) {
            auto next = next_pos(p, dir);
            while (!valid_next(next)) {
                dir = next_dir(dir);
                next = next_pos(p, dir);
            }
            p = next;
            };

        pos current_pos = { 0,0 };
        direction current_dir = direction::right;
        ListNode* current = head;

        ans[current_pos.y][current_pos.x] = current->val;
        current = current->next;
        while (current != nullptr) {
            get_next(current_pos, current_dir);
            ans[current_pos.y][current_pos.x] = current->val;
            current = current->next;
        }
        return ans;
    }
};

void test(int m, int n, vector<int>&& node_values) {
    output(Solution().spiralMatrix(m, n, create_listnode(node_values)));
}
int main()
{
    test(3, 5, get_list_int("[3,0,2,6,8,1,7,9,4,2,5,5,0]"));
    test(1, 4, get_list_int("[0,1,2]"));
}