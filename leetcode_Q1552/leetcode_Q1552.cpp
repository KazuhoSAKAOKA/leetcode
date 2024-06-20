// leetcode_Q1552.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        if (m < 2) {
            return 0;
        }
        sort(begin(position), end(position));
        const int min_value = position.front();
        const int max_value = position.back();

        auto check = [&](int force) {
            auto it = cbegin(position);
            for (int i = 1; i < m; i++) {
                it = lower_bound(it, cend(position), *it + force);
                if (it == cend(position)) {
                    return false;
                }
            }
            return true;
            };
        int l = 1;
        int r = (max_value - min_value) / (m - 1) + 1;
        int ans = 1;
        while (l <= r) {
            const auto mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }


        return ans;
    }
};

void test(vector<int>&& position, int m) {
    cout << Solution().maxDistance(position, m) << endl;
}

int main()
{
    test(get_list_int("[1,2,3,4,7]"), 3);
    test(get_list_int("[5,4,3,2,1,1000000000]"), 2);
}