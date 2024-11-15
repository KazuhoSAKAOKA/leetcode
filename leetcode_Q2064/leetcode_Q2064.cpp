// leetcode_Q2064.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <functional>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    template <typename T = long long>
    static T binary_search(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    int minimizedMaximum(int n, vector<int>& quantities) {
        auto check = [&](long long v) {
            int count = 0;
            for (int i = 0; i < size(quantities); i++) {
                const auto temp = (quantities[i] + v - 1) / v;
                count += temp;
            }
            return count <= n;
            };
        auto m = *max_element(cbegin(quantities), cend(quantities));
        const auto ans = binary_search<int>(m, 0, check);
        return ans;
    }
};

void test(int n, vector<int>&& quantities) {
    cout << Solution().minimizedMaximum(n, quantities) << endl;
}
int main()
{
    test(6, get_list_int("[11,6]"));
    test(7, get_list_int("[15,10,10]"));
    test(1, get_list_int("[100000]"));

    return 0;
}