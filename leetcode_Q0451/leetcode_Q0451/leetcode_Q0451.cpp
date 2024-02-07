// leetcode_Q0451.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


class Solution {
public:
    string frequencySort(string s) {
        map<char, size_t> count_map;
        for (auto&& c : s) {
            count_map[c]++;
        }

        map<size_t, vector<char>> reverse_map;
        for (auto& kv : count_map) {
            reverse_map[kv.second].emplace_back(kv.first);
        }

        string ans;
        ans.reserve(s.size());
        for (auto it = crbegin(reverse_map); it != crend(reverse_map); ++it) {
            const auto& chars = it->second;
            for (auto c : chars) {
                ans.append(it->first, c);
            }
        }
        return ans;
    }
};

void test(string&& s) {
    cout << Solution().frequencySort(s) << endl;
}

int main()
{
    test("tree");
    test("cccaaa");
    test("Aabb");
}