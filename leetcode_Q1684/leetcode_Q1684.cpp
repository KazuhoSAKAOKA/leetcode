// leetcode_Q1684.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set exists(cbegin(allowed), cend(allowed));
        const auto count = count_if(cbegin(words), cend(words), [&](const auto& s) { return all_of(cbegin(s), cend(s), [&](const auto& c) { return exists.count(c) > 0; }); });
        return static_cast<int>(count);
    }
};

void test(string allowed, vector<string>&& words) {
    cout << Solution().countConsistentStrings(allowed, words) << endl;
}

int main()
{
    test("ab", get_list_str(R"(["ad","bd","aaab","baa","badab"])"));
    test("abc", get_list_str(R"(["a","b","c","ab","ac","bc","abc"])"));
    test("cad", get_list_str(R"(["cc","acd","b","ba","bac","bad","ac","d"])"));
    return 0;
}