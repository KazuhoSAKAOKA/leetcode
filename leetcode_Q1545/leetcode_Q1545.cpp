// leetcode_Q1545.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Solution {
public:

    static string rev_invert(const string& s) {
        string ret;
        ret.reserve(size(s));
        for (auto it = crbegin(s); it != crend(s); ++it) {
            ret += *it == '0' ? '1' : '0';
        }
        return ret;
    }

    inline static char rev(char c) {
        return c == '0' ? '1' : '0';
    }

    static char rec(int depth, int index, int begin_index, int len) {
        if (depth == 0) {
            return '0';
        }
        if (index == begin_index) {
            return '1';
        }
        const int before_len = len / 2;
        if (index < begin_index) {
            return rec(depth - 1, index, begin_index - before_len, before_len);
        }
        else {
            return rev(rec(depth - 1, (begin_index + len) - index - 1, begin_index - before_len, before_len));
        }
    }


    char findKthBit(int n, int k) {
        int begin_index = 0;
        int cur_len = 1;
        int total_len = 1;
        int depth = 0;
        while (total_len < k) {
            begin_index += cur_len;
            cur_len = total_len + 1;
            total_len += cur_len;
            depth++;
        }
        return rec(depth, k - 1, begin_index, cur_len);
    }
};

void test(int n, int k) {
    cout << Solution().findKthBit(n, k) << endl;
}


int main()
{
    test(3, 4);


    test(3, 1);
    test(4, 11);
    test(3, 7);
    test(5, 30);
    return 0;
}