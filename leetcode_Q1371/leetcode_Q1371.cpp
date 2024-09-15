// leetcode_Q1371.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findTheLongestSubstring(string s) {
        unordered_map<char, int> vowels{ {'a', 1},{'e',2},{'i',4},{'o', 8},{'u',16}, };
        unordered_map<int, size_t> bitmask_index_map{ {0, -1} };
        size_t max_len = 0;
        int bitmask = 0;
        for (size_t i = 0; i < size(s); i++) {
            int current_bitmask = 0;
            const auto it = vowels.find(s[i]);
            if (it != cend(vowels)) {
                current_bitmask = it->second;
            }
            bitmask ^= current_bitmask;

            size_t current_len = 0;
            if (bitmask == 0) {
                const auto bitmask_it = bitmask_index_map.find(bitmask);
                current_len = i - (*bitmask_it).second;
            }
            else {
                const auto bitmask_it = bitmask_index_map.find(bitmask);
                if (bitmask_it == cend(bitmask_index_map)) {
                    bitmask_index_map[bitmask] = i;
                }
                else {
                    current_len = i - (*bitmask_it).second;
                }
            }
            max_len = max(max_len, current_len);
        }
        return static_cast<int>(max_len);
    }
};

void test(string&& s) {
    cout << Solution().findTheLongestSubstring(s) << endl;
}

int main()
{
    test("leetcodegreat");
    test("eleetminicoworoep");
    test("leetcodeisgreat");
    test("bcbcbc");
    return 0;
}