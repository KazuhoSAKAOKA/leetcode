// leetcode_Q2955.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


class Solution {
public:

    static int counting(const string& s, int first, int last) {
        int count = 0;
        vector<int> freq(26, 0);

        for (int i = first; i <= last; i++) {
            const int index = s[i] - 'a';
            freq[index]++;
            count += freq[index];
        }
        return count;
    }

    static vector<int> tle(const string& s, vector<vector<int>>&& queries) {
        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            ans.emplace_back(counting(s, query.front(), query.back()));
        }
        return ans;
    }

    vector<int> sameEndSubstringCount(string s, vector<vector<int>>& queries) {
        vector<vector<int>> prefix_sums_list(26, vector<int>(size(s) + 1, 0));
        for (int i = 0; i < size(s); i++) {
            for (int j = 0; j < 26; j++) {
                prefix_sums_list[j][i + 1] = prefix_sums_list[j][i];
            }
            const int index = s[i] - 'a';
            prefix_sums_list[index][i + 1]++;
        }
        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            int count = 0;
            for (int j = 0; j < 26; j++) {
                const auto char_count = prefix_sums_list[j][query.back() + 1] - prefix_sums_list[j][query.front()];
                count += char_count * (char_count + 1) / 2;
            }
            ans.emplace_back(count);
        }
        return ans;
    }
};

void test(string s, vector<vector<int>>&& queries) {
    output(Solution().sameEndSubstringCount(s, queries));
}
int main()
{
    test("abcaab", get_matrix_int("[[0,0],[1,4],[2,5],[0,5]]"));
    test("abcd", get_matrix_int("[[0,3]]"));

    return 0;
}