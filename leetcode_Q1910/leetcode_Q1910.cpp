// leetcode_Q1910.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:

    static string estimate_tle(const string& s, const string& part) {
        string current(s);
        for(;;) {
            auto pos = current.find(part);
            if (pos == string::npos) {
                break;
            }
            current = current.substr(0, pos) + current.substr(pos + size(part));
        }
        return current;
    }

    static pair<bool, size_t> search_rec(const string& s, size_t index, const string& part, size_t part_index) {
        if (size(part) == part_index) {
            return { true, index };
        }
        if (size(s) == index) {
            return { false, 0 };
        }
        if (s[index] != part[part_index]) {
            return { false, 0 };
        }
        int cur_index = index + 1;
        for (;;) {
            const auto [r, ret_index] = search_rec(s, cur_index, part, part_index + 1);
            if (r) {
                return { true, ret_index };
            }
            const auto [r2, ret_index2] = search_rec(s, cur_index, part, 0);
            if (!r2) {
                return { false, 0 };
            }
            cur_index = ret_index2;
        }
    }

    string removeOccurrences(string s, string part) {
        string ans;
        ans.reserve(size(s));
        size_t index = 0;
        while (index < size(s)) {
            const auto p = search_rec(s, index, part, 0);
            if (!p.first) {
                ans += s[index];
                index++;
            }
            else {
                index = p.second;
            }
        }
        return ans;
    }
};

void test(string&& s, string&& part) {
    cout << Solution().removeOccurrences(s, part) << endl;
}
int main()
{
    test("aabcbc", "abc");
    test("daabcbaabcbc", "abc");
    test("axxxxyyyyb", "xy");
    return 0;
}