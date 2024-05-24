// leetcode_Q1255.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    using A = pair<int, unordered_map<char, int>>;

    static int rec(const vector<A>& list, int index, unordered_map<char, int>& letter_counts) {
        if (index == list.size()) {
            return 0;
        }

        int value_not_include_me = rec(list, index + 1, letter_counts);
        const auto& current = list[index];
        int value_include_me = 0;
        auto check_and_update = [](unordered_map<char, int>& counts, const unordered_map<char, int>& use)-> bool{
            bool invalid = false;;
            for (auto [c, count] : use) {
                counts[c] -= count;
                if (counts[c] < 0) {
                    invalid = true;
                }
            }
            return invalid;
            };


        if (!check_and_update(letter_counts, list[index].second)) {
            value_include_me = rec(list, index + 1, letter_counts) + list[index].first;
        }
        for (auto& [c, count] : list[index].second) {
            letter_counts[c] += count;
        }


        return max(value_not_include_me, value_include_me);
    }

    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        vector<A> converted;
        converted.reserve(words.size());

        for (auto&& word : words) {
            unordered_map<char, int> m;
            int temp_score = 0;
            for (auto&& c: word) {
                m[c]++;
                temp_score += score[c - 'a'];
            }
            converted.emplace_back(A(temp_score, m));
        }
        unordered_map<char, int> letter_count_map;
        for (auto&& c : letters) {
            letter_count_map[c]++;
        }

        return rec(converted, 0, letter_count_map);
    }
};

void test(vector<string>&& words, vector<char>&& letters, vector<int>&& score) {
    cout << Solution().maxScoreWords(words, letters, score) << endl;
}

int main()
{
    test(get_list_str(R"(["dog","cat","dad","good"])"), get_list_char(R"(["a","a","c","d","d","d","g","o","o"])"), get_list_int("[1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]"));
    test(get_list_str(R"(["xxxz","ax","bx","cx"])"), get_list_char(R"(["z","a","b","c","x","x","x"])"), get_list_int("[4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]"));
    test(get_list_str(R"(["leetcode"])"), get_list_char(R"(["l","e","t","c","o","d"])"), get_list_int("[0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]"));
}