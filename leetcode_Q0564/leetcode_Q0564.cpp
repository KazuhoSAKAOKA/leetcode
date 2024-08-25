// leetcode_Q0564.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

class Solution {
public:

    static char convert_down(char c) {
        if (c == '0') {
            return '1';
        }
        else {
            return c - 1;
        }
    }
    static char convert_up(char c) {
        if (c == '9') {
            return '0';
        }
        else {
            return c + 1;
        }
    }


    static string wa(const string& n) {
        if (size(n) == 1) {
            string ans0(1, ' ');
            ans0[0] = convert_down(n[0]);
            return ans0;
        }

        size_t half = size(n) / 2;
        bool changed = false;
        string ans1(n);
        for (size_t i = 0; i < half; i++) {
            if (n[i] != n[size(n) - i - 1]) {
                ans1[size(n) - i - 1] = n[i];
                changed = true;
            }
        }
        if (!changed) {
            string ans1_1(ans1);
            string ans1_2(ans1);
            if (size(n) % 2 == 0) {
                const char c1 = convert_down(n[half - 1]);
                const char c2 = convert_down(n[half - 1]);
                ans1_1[half - 1] = c1;
                ans1_1[half] = c1;
                ans1_2[half - 1] = c2;
                ans1_2[half] = c2;
            }
            else {
                ans1_1[half] = convert_down(n[half]);
                ans1_2[half] = convert_up(n[half]);
            }
            if (get_diff(n, ans1_1) < get_diff(n, ans1_2)) {
                ans1 = ans1_1;
            }
            else {
                ans1 = ans1_2;
            }
        }
        string col_up(size(n) + 1, '0');
        col_up[0] = '1';
        col_up[size(n)] = '1';

        const auto diff1 = get_diff(n, ans1);
        string ans;
        string col_down(size(n) - 1, '9');
        const auto d_diff = get_diff(n, col_down);
        int diff;
        if (d_diff <= diff1) {
            ans = col_down;
            diff = d_diff;
        }
        else {
            ans = ans1;
            diff = diff1;
        }

        const auto diff_up = get_diff(n, col_up);
        if (diff_up < diff) {
            ans = col_up;
        }

        return ans;
    }
    static long long get_diff(const string& n1, const string& n2) {
        long long v1 = stoll(n1);
        long long v2 = stoll(n2);
        return abs(v1 - v2);
    }
    string create(const string& n, int offset) {
        string r(n);
        auto half = size(n) / 2;
        for (int i = 0; i < half - 1; i++) {
            r[size(n) - i - 1] = n[i];
        }
        if (offset < 0) {
            r[half] = n[half];
        }
    }

    string nearestPalindromic(string n) {
        vector<string> poss;
        poss.push_back(string(size(n) - 1, '9'));
        {
            string temp(size(n) + 1, '0');
            temp[0] = '1';
            temp[size(n)] = '1';
            poss.push_back(temp);
        }

    }
};

void test(string&& n) {
    cout << Solution().nearestPalindromic(n) << endl;
}
int main()
{
    test("1283");
    test("999999999999999999");
    test("999");
    test("1000");
    test("123");
    test("1");
    return 0;
}
