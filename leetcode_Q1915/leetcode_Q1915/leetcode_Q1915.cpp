// leetcode_Q1915.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:

    static long long mle(string word) {
        if (word.empty()) { return 0LL; }
        long long count = 0;
        auto get_bit = [](const char c)->int { return 1 << (c - 'a'); };
        auto check = [](int v)->bool {
            return
                ((v & 0x00000001) != 0 ? 1 : 0) +
                ((v & 0x00000002) != 0 ? 1 : 0) +
                ((v & 0x00000004) != 0 ? 1 : 0) +
                ((v & 0x00000008) != 0 ? 1 : 0) +
                ((v & 0x00000010) != 0 ? 1 : 0) +
                ((v & 0x00000020) != 0 ? 1 : 0) +
                ((v & 0x00000040) != 0 ? 1 : 0) +
                ((v & 0x00000080) != 0 ? 1 : 0) +
                ((v & 0x00000100) != 0 ? 1 : 0) +
                ((v & 0x00000200) != 0 ? 1 : 0)
                < 2;
            };

        vector<int> before;
        for (int i = 0; i < word.size(); i++) {
            vector<int> current;
            current.reserve(before.size() + 1);
            const auto bit = get_bit(word[i]);
            for (auto&& value : before) {
                const auto new_value = value ^ bit;
                if (new_value == 0 || check(new_value)) {
                    count++;
                }
                current.emplace_back(new_value);
            }
            current.emplace_back(bit);
            count++;
            before = current;
        }
        return count;

    }

    long long wonderfulSubstrings(string word) {
        if (word.empty()) { return 0LL; }
        long long count = 0;
        auto get_bit = [](const char c)->int { return 1 << (c - 'a'); };
        unordered_map<int, int> freq_map{ {0,1}, };
        int mask = 0;
        for (int i = 0; i < word.size(); i++) {
            const auto bit = get_bit(word[i]);
            mask ^= bit;
            count += freq_map[mask];
            freq_map[mask]++;
            for (int i = 0; i < 10; i++) {
                const auto v = 1 << i;
                const auto key = mask ^ v;
                count += freq_map[key];
            }
        }
        return count;
    }
};

void test(string&& word) {
    cout << Solution().wonderfulSubstrings(word) << endl;
}
int main()
{
    test("aabb");
    test("fiabhedce");
    test("aba");
    test("he");
}