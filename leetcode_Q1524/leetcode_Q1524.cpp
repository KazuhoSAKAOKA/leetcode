// leetcode_Q1524.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
constexpr long long MODULO = 1e9 + 7;

class Solution {
public:
    static
        int tle(vector<int>& arr) {
        vector<int> prefix_sums(size(arr) + 1);
        for (int i = 0; i < size(arr); i++) {
            prefix_sums[i + 1] = prefix_sums[i] + arr[i] % 2;
        }
        long long count = 0;
        for (int i = 0; i < size(arr); i++) {
            for (int j = i + 1; j <= size(arr); j++) {
                if ((prefix_sums[j] - prefix_sums[i]) % 2 != 0) {
                    count++;
                    count %= MODULO;
                }
            }
        }
        return static_cast<int>(count);
    }

    int numOfSubarrays(vector<int>& arr) {
        long long count = 0;
        long long odd_count = 0;
        long long even_count = 0;
        for (int i = 0; i < size(arr); i++) {
            if (arr[i] % 2 == 0) {
                even_count++;
                even_count %= MODULO;
            }
            else {
                swap(odd_count, even_count);
                odd_count++;
                odd_count %= MODULO;
            }
            count += odd_count;
            count %= MODULO;
        }
        return static_cast<int>(count);
    }
};

void test(vector<int>&& arr) {
    cout << Solution().numOfSubarrays(arr) << endl;
}
int main() {
    test(get_list_int("[1,3,5]"));
    test(get_list_int("[2,4,6]"));
    test(get_list_int("[1,2,3,4,5,6,7]"));
    return 0;
}
