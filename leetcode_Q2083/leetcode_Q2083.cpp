// leetcode_Q2083.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    long long numberOfSubstrings(string s) {
        unordered_map<char, long long> freq_map;

        long long total = 0;

        for (auto&& c : s) {
            const auto it = freq_map.find(c);
            total++;
            if (it != cend(freq_map)) {
                total += it->second;
            }
            freq_map[c]++;
        }


        return total;
    }
};

void test(string&& s) {
    cout << Solution().numberOfSubstrings(s) << endl;
}

int main()
{
    test("abcba");
    test("abacad");
    test("a");
}