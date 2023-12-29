// leetcode_Q0091.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    int64_t numDecodingsBK(const string& s, int index, char before, map<pair<int, char>, int64_t>& memo) {
        const auto key = make_pair(index, before);
        auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        if (s.size() <= index) {
            return before == 0 ? 1 : 0;
        }

        int64_t count = 0;
        const char c = s[index];
        if (c == '0') {
            if (before != '1' && before != '2') {
                return 0;
            }
            count += numDecodingsBK(s, index + 1, 0, memo);
        }
        else {
            if (before == '2') {
                if (c < '7') {
                    count += numDecodingsBK(s, index + 1, 0, memo);
                }
                else {
                    return 0;
                }
            }
            else {
                count += numDecodingsBK(s, index + 1, 0, memo);
            }
            if (before == 0) {
                if (c == '1' || c == '2') {
                    count += numDecodingsBK(s, index + 1, c, memo);
                }
            }
        }
        memo[key] = count;

        return count;
    }

    int64_t numDecodings(string s) {

        map<pair<int, char>, int64_t> memo;
        return numDecodingsBK(s, 0, 0, memo);
    }
};


int main()
{
    cout << Solution().numDecodings("10") << endl;
    cout << Solution().numDecodings("12") << endl;
    cout << Solution().numDecodings("226") << endl;
    cout << Solution().numDecodings("06") << endl;
    cout << Solution().numDecodings("30") << endl;
    cout << Solution().numDecodings("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111") << endl;

}

