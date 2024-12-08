// leetcode_Q1891.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "./../utility/leetcode_testcase_helper.h"


using namespace std;
template <typename T = long long>
T binary_search1(T ok, T ng, std::function<bool(T)> check) {
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

class Solution {
public:
    int maxLength(vector<int>& ribbons, int k) {
        return binary_search1<int>(0, *max_element(cbegin(ribbons), cend(ribbons)) + 1, 
            [&](int len) {
                int cuts = 0;
                for (auto&& ribbon : ribbons) {
                    cuts += ribbon / len;
                }
                return cuts >= k;
            });
    }
};

void test(vector<int>&& ribbons, int k) {
    cout << Solution().maxLength(ribbons, k) << endl;
}
int main()
{
    test(get_list_int("[9,7,5]"), 3);
    test(get_list_int("[7,5,9]"), 4);
    test(get_list_int("[5,7,9]"), 22);
    return 0;
}