// leetcode_Q0076.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;

class Solution {
public:
    static bool match(const string& s, const string& t, int index1, int index2 ,const map<char, size_t>& expected, const map<char, size_t>& current) {
        if ((index2 - index1) < t.size()) { return false; }
        return all_of(cbegin(expected), cend(expected), [&](const auto& kv)
            {
                const auto it = current.find(kv.first);
                return it != cend(current) && kv.second <= it->second;
            });
    }

    string minWindow(string s, string t) {
        map<char, size_t> t_map;
        for (auto&& c : t) {
            t_map[c]++;
        }

        map<char, size_t> current_map;
        int index1 = 0;
        int index2 = 0;
        int min_index1 = 0;
        int min_index2 = 0;

        while (index1 < s.size()) {
            while (!match(s, t, index1, index2, t_map, current_map)) {
                if (s.size() == index2) { goto EXIT; }
                current_map[s[index2]]++;
                index2++;
            }

            do {
                if (min_index2 == 0 || (index2 - index1) < (min_index2 - min_index1)) {
                    min_index1 = index1;
                    min_index2 = index2;
                }
                current_map[s[index1]]--;
                index1++;
            } while (match(s, t, index1, index2, t_map, current_map));
        }

        EXIT:

        return s.substr(min_index1, min_index2 - min_index1);
    }
};


void test(string&& s, string&& t) {
    cout << Solution().minWindow(s, t) << endl;
}

int main()
{
    test("ADOBECODEBANC", "ABC");
    test("a", "a");
    test("a", "aa");
}