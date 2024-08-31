// leetcode_Q0666.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static tuple<int, int, int> get_info(int value) {
        int h = value / 100;
        int t = (value % 100) / 10;
        int u = (value % 10);
        return { h,t,u };
    }
    static int get_index(int depth, int level_index) {
        int v = 1;
        for (int i = 0; i < depth; i++) {
            v *= 2;
        }
        return v + level_index - 1;
    }

    static void rec(const vector<int>& nodes, int index, int current_sum, int& total) {
        const int left = (index + 1) * 2 - 1;
        const int right = (index + 1) * 2;
        // leaf
        if (nodes[left] == -1 && nodes[right] == -1) {
            total += nodes[index] + current_sum;
            return;
        }

        if (nodes[left] != -1) {
            rec(nodes, left, current_sum + nodes[index], total);
        }
        if (nodes[right] != -1) {
            rec(nodes, right, current_sum + nodes[index], total);
        }
    }

    int pathSum(vector<int>& nums) {
        vector<int> nodes(32, -1);
        for (auto&& num : nums) {
            auto [depth, level_index, value] = get_info(num);
            const auto index = get_index(depth - 1, level_index - 1);
            nodes[index] = value;
        }
        int total = 0;
        rec(nodes, 0, 0, total);
        return total;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().pathSum(nums) << endl;
}
int main()
{
    test(get_list_int("[113,229,330,466]"));
    test(get_list_int("[113,215,221]"));
    test(get_list_int("[113,221]"));
    return 0;
}