// leetcode_Q2559.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static bool is_vowel(char c) {
        return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o';
    }

    static bool is_vowel_start_end(const string& word) {
        return is_vowel(word.front()) && is_vowel(word.back());
    }

    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {

        vector<int> prefix_sums(size(words) + 1);
        int index = 0;
        for (auto&& word : words) {
            prefix_sums[index + 1] = prefix_sums[index] + (is_vowel_start_end(word) ? 1 : 0);
            index++;
        }
        vector<int> ans;
        ans.reserve(size(queries));

        for (auto&& query : queries) {
            const auto count = prefix_sums[query.back() + 1] - prefix_sums[query.front()];
            ans.emplace_back(count);
        }
        return ans;
    }
};

void test(vector<string>&& words, vector<vector<int>>&& queries) {
    output(Solution().vowelStrings(words, queries));
}
int main()
{
    test(get_list_str(R"(["aba","bcb","ece","aa","e"])"), get_matrix_int("[[0,2],[1,4],[1,1]]"));
    test(get_list_str(R"(["a","e","i"])"), get_matrix_int("[[0,2],[0,1],[2,2]]"));
    return 0;
}