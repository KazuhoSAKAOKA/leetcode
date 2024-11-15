// leetcode_Q1574.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    int findLengthOfShortestSubarray(vector<int>& arr) {
        auto find_forward = [&]() {
            for (int i = 0; i < size(arr) - 1; i++) {
                if (arr[i] > arr[i + 1]) {
                    return i;
                }
            }
            return static_cast<int>(size(arr) - 1);
            };

        const auto l = find_forward();
        if (l == size(arr) - 1) {
            return 0;
        }

        auto find_backward = [&]() {
            for (int i = size(arr) - 1; i >=1 ; i--) {
                if (arr[i] < arr[i - 1]) {
                    return i;
                }
            }
            return 0;
            };

        const auto r = find_backward();

        if (arr[l] <= arr[r]) {
            return size(arr) - (l + 1 + size(arr) - r);
        }
        const auto search_range_begin = next(cbegin(arr), r);
        const auto loop_end = next(cbegin(arr), l + 1);

        int min_length = size(arr) - max(l, static_cast<int>(size(arr)) - r);
        for (auto it = cbegin(arr); it != loop_end; ++it) {
            const auto current_value = *it;
            const auto it_r = lower_bound(search_range_begin, cend(arr), current_value);
            const auto dist = static_cast<int>(distance(it, it_r)) - 1;
            min_length = min(min_length, dist);
        }
        return min_length;
    }
};

void test(vector<int>&& arr) {
    cout << Solution().findLengthOfShortestSubarray(arr) << endl;
}

int main()
{
    test(get_list_int("[6,3,10,11,15,20,13,3,18,12]"));
    test(get_list_int("[1,2,3,10,4,2,3,5]"));
    test(get_list_int("[5,4,3,2,1]"));
    test(get_list_int("[1,2,3]"));
    return 0;
}