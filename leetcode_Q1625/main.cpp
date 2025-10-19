#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>

using namespace std;
class Solution {
public:
    static int get_acount(int a) {
        int count = 1;
        int s = a;
        while (s != 0) {
            s += a;
            s %= 10;
            count++;
        }
        return count;
    }
    static int get_bcount(int len, int b) {
        int count = 1;
        int s = b % len;
        while (s != 0) {
            s += b;
            s %= len;
            count++;
        }
        return count;
    }

    static void do_op_a(string& s, int a) {
        string temp(s);
        for (int i = 0; i < size(s) / 2; i++) {
            s[i * 2 + 1] = static_cast<char>((((temp[i * 2 + 1] - '0') + a) % 10) + '0');
        }
    }
    static void do_op_b(string& s, int b) {
        const auto len = size(s);
        string temp(s);
        for (int i = 0; i < len; i++) {
            s[(i + b) % len] = temp[i];
        }
    }
    static string mle(string s, int a, int b) {
        const int n = static_cast<int>(size(s));
        string lex_min(s);
        const auto a_count = get_acount(a);
        const auto b_count = get_bcount(n, b);
        string work(s);
        for (int i = 0; i < b_count; i++) {
            do_op_b(work, b);
            for (int j = 0; j < a_count; j++) {
                do_op_a(work, a);
                for (int k = 0; k < b_count; k++) {
                    do_op_b(work, b);
                    for (int l = 0; l < a_count; l++) {
                        do_op_a(work, a);
                        if (work < lex_min) {
                            lex_min = work;
                        }
                    }
                }
            }
        }
        return lex_min;
    }
    string findLexSmallestString(string s, int a, int b) {
        const int n = static_cast<int>(size(s));
        set<string> visited;
        visited.insert(s);

        queue<string> q;
        q.push(s);

        auto pa = [&](const string& source)->string {
            string temp(source);
            for (int i = 0; i < n / 2; i++) {
                temp[i * 2 + 1] = static_cast<char>((((source[i * 2 + 1] - '0') + a) % 10) + '0');
            }
            return temp;
            };

        auto pb = [&](const string& source)->string {
            string temp(n, 0);
            for (int i = 0; i < n; i++) {
                temp[(i + b) % n] = source[i];
            }
            return temp;
            };


        while (!q.empty()) {
            const string cur = q.front();
            q.pop();
            const string after_a = pa(cur);
            if (visited.count(after_a) == 0) {
                visited.insert(after_a);
                q.push(after_a);
            }
            const string after_b = pb(cur);
            if (visited.count(after_b) == 0) {
                visited.insert(after_b);
                q.push(after_b);
            }
        }

        return *cbegin(visited);
    }
};

static void test(string s, int a, int b) {
    cout << Solution().findLexSmallestString(s, a, b) << endl;
}
int main() {
    test("74", 5, 1);
    test("5525", 9, 2);
    test("0011", 4, 2);
    return 0;
}