// leetcode_Q0320.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:

    void rec(const string& word, size_t index, bool allow_conv, string& current, vector<string>& result) {
        if (size(word) == index) {
            result.emplace_back(current);
            return;
        }

        current += word[index];
        rec(word, index + 1, true, current, result);
        current.pop_back();

        if (allow_conv) {
            for (size_t len = 1; len <= size(word) - index; len++) {
                const auto abb = to_string(len);
                current += abb;
                rec(word, index + len, false, current, result);
                for (size_t i = 0; i < size(abb); i++) {
                    current.pop_back();
                }
            }
        }
    }

    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        string work;
        rec(word, 0, true, work, result);
        return result;
    }
};

void test(string&& word) {
    const auto ans = Solution().generateAbbreviations(word);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
int main()
{
    test("word");
    test("a");
    return 0;
}