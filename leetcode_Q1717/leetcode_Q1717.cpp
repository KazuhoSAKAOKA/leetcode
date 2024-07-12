// leetcode_Q1717.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <deque>
#include <stack>
using namespace std;

class Solution {
public:

    static int rec(string&& s, int x, int y) {
        if (s.size() < 2) {
            return 0;
        }
        int max_score = 0;
        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == 'a' && s[i + 1] == 'b') {
                max_score = max(max_score, rec(s.substr(0, i) + s.substr(i + 2), x, y) + x);
            }
            else if (s[i] == 'b' && s[i + 1] == 'a') {
                max_score = max(max_score, rec(s.substr(0, i) + s.substr(i + 2), x, y) + y);
            }
        }
        return max_score;
    }

    static int tle(string&& s, int x, int y) {
        int total_score = 0;

        int series = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'a' || s[i] == 'b') {
                series++;
            }
            else {
                if (series > 1) {
                    total_score += rec(s.substr(i - series, series), x, y);
                }
                series = 0;
            }
        }
        if (series > 1) {
            total_score += rec(s.substr(s.size() - series), x, y);
        }

        return total_score;
    }
    

    int maximumGain(string s, int x, int y) {
        int total_score = 0;
        char first_target;
        char second_target;
        int first_score;
        int second_score;
        if (x > y) {
            first_target = 'a';
            first_score = x;
            second_target = 'b';
            second_score = y;
        }
        else {
            first_target = 'b';
            first_score = y;
            second_target = 'a';
            second_score = x;
        }
        
        deque<char> dq;
        for (int i = 0; i < s.size(); i++) {
            if (!dq.empty() && (dq.back() == first_target && s[i] == second_target)) {
                dq.pop_back();
                total_score += first_score;
            }
            else {
                dq.push_back(s[i]);
            }
        }
        stack<char> st;
        while (!dq.empty()) {
            const char c = dq.front();
            dq.pop_front();
            if (!st.empty() && (st.top() == second_target && c == first_target)) {
                st.pop();
                total_score += second_score;
            }
            else {
                st.push(c);
            }
        }

        return total_score;
    }
};

void test(string&& s, int x, int y) {
    cout << Solution().maximumGain(s, x, y) << endl;
}

int main()
{
    test("ba", 10, 1);
    test("aba", 10, 1);
    test("bab", 10, 1);
    test("cdbcbbaaabab", 4, 5);
    test("aabbaaxybbaabb", 5, 4);
    return 0;
}