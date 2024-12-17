// leetcode_Q2182.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

#include <map>

using namespace std;

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        map<char, int, std::greater<>> freq_map;
        for (auto&& c : s) {
            freq_map[c]++;
        }

        string ans;
        ans.reserve(size(s));
        while (!freq_map.empty()) {
            auto top_it = begin(freq_map);
            const auto top = top_it->first;
            const auto count = top_it->second;
            if (count <= repeatLimit) {
                ans.append(count, top);
                freq_map.erase(top);
            }
            else {
                ans.append(repeatLimit, top);
                top_it->second -= repeatLimit;
                auto next_it = next(top_it);
                if (next_it == end(freq_map)) {
                    break;
                }
                ans.append(1, next_it->first);
                if (next_it->second == 1) {
                    freq_map.erase(next_it);
                }
                else {
                    next_it->second--;
                }
            }
        }
        return ans;
    }
};

void test(string&& s, int repeatLimit) {
    cout << Solution().repeatLimitedString(s, repeatLimit) << endl;
}

int main()
{
    test("cczazcc", 3);
    test("aababab", 2);
    return 0;
}