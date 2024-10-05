// leetcode_Q0567.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<size_t> freqs(26, 0);
        for (auto&& c : s1) {
            freqs[c - 'a']++;
        }
        size_t short_count = count_if(cbegin(freqs), cend(freqs), [](const auto& c) { return c > 0; });
        size_t over_count = 0;
        vector<size_t> cur_freqs(26, 0);

        size_t l = 0;
        for (size_t r = 0; r < size(s2); r++) {
            size_t right_ind = static_cast<size_t>(s2[r] - 'a');
            if (freqs[right_ind] == cur_freqs[right_ind]) {
                over_count++;
            }
            cur_freqs[right_ind]++;
            if (freqs[right_ind] == cur_freqs[right_ind]) {
                short_count--;
            }

            while (l < r && over_count > 0) {
                size_t left_ind = static_cast<size_t>(s2[l] - 'a');
                if (freqs[left_ind] == cur_freqs[left_ind]) {
                    short_count++;
                }
                cur_freqs[left_ind]--;
                if (freqs[left_ind] == cur_freqs[left_ind]) {
                    over_count--;
                }
                l++;
            }

            if (short_count == 0 && over_count == 0) {
                return true;
            }
        }
        return false;
    }
};

void test(string&& s1, string&& s2) {
    cout << Solution().checkInclusion(s1, s2) << endl;
}

int main()
{
    test("rvwrk", "lznomzggwrvrkxecjaq");
    test("r", "pilmtnzraxj");
    test("ab","eidbaooo");
    test("ab","eidboaoo");
    return 0;
}