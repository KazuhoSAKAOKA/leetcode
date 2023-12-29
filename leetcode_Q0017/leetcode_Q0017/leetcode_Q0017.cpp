// leetcode_Q0017.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class Solution {
public:

    void combination(const map<char, string>& key_map, const string& digits, size_t index, const string& current, vector<string>& list) {
        if (digits.size() <= index) {
            if (current.size() > 0) {
                list.emplace_back(current);
            }
            return;
        }
        const auto& values = key_map.at(digits[index]);
        for (auto&& c : values) {
            combination(key_map, digits, index + 1, current + c, list);
        }
    }

    vector<string> letterCombinations(string digits) {
        const map<char, string> key_map
        {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"},
        };
        vector<string> list;
        combination(key_map, digits, 0, "", list);
        return list;
    }
};


void output(const vector<string>& list) {
    for (auto&& s : list)
    {
        cout << s << ",";
    }
    cout << endl;
}


int main()
{
    output(Solution().letterCombinations("23"));
    output(Solution().letterCombinations(""));
    output(Solution().letterCombinations("2"));
}

