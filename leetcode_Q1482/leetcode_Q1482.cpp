// leetcode_Q1482.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {

        auto check = [&](int day)->bool {
            int bloom_count = 0;
            int cont_count = 0;
            for (int i = 0; i < bloomDay.size(); i++) {
                if (bloomDay[i] <= day) {
                    cont_count++;
                    if (cont_count == k) {
                        bloom_count++;
                        if (bloom_count == m) {
                            return true;
                        }
                        cont_count = 0;
                    }
                }
                else {
                    cont_count = 0;
                }
            }
            return false;
            };

        int l = 0;
        int r = *max_element(cbegin(bloomDay), cend(bloomDay)) + 1;
        int ans = -1;

        while (l <= r) {
            const auto mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

void test(vector<int>&& bloomDay, int m, int k) {
    cout << Solution().minDays(bloomDay, m, k) << endl;
}

int main()
{
    test(get_list_int("[1,10,3,10,2]"), 3, 1);
    test(get_list_int("[1,10,3,10,2]"), 3, 2);
    test(get_list_int("[7,7,7,7,12,7,7]"), 2, 3);
}