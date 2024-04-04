// leetcode_Q0205.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        unordered_map<char, char> convert_map;
        unordered_set<char> reverse_set;

        for (int i = 0; i < s.size(); i++) {
            const auto it = convert_map.find(s[i]);
            if (it == cend(convert_map)) {
                if (reverse_set.find(t[i]) != cend(reverse_set)) {
                    return false;
                }
                convert_map.insert(make_pair(s[i], t[i]));
                reverse_set.insert(t[i]);
            }
            else {
                if (it->second != t[i]) {
                    return false;
                }
            }
        }

        return true;
    }
};

void test(string&& s, string&& t) {
    cout << Solution().isIsomorphic(s, t) << endl;
}

int main()
{
    test("egg", "add");
    test("foo", "bar");
    test("paper", "title");
}