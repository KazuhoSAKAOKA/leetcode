// leetcode_Q1813.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:

    static vector<string> split(const string& sentence) {
        vector<string> words;
        size_t index = 0;
        while (index < size(sentence)) {
            const size_t p = sentence.find(' ', index);
            if (p == string::npos) {
                words.emplace_back(sentence.substr(index));
                break;
            }
            words.emplace_back(sentence.substr(index, p - index));
            index = p + 1;
        }
        return words;
    }

    template <typename T>
    static size_t get_common_length(T it1_begin, T it1_end, T it2_begin, T it2_end) {
        T it1 = it1_begin;
        T it2 = it2_begin;
        size_t length = 0;
        while (it1 != it1_end && it2 != it2_end && *it1 == *it2) {
            length++;
            ++it1;
            ++it2;
        }
        return length;
    }

    bool areSentencesSimilar(string sentence1, string sentence2) {
        if (sentence1 == sentence2) {
            return true;
        }
        const vector<string> sentence1_words = split(sentence1);
        const vector<string> sentence2_words = split(sentence2);
        if (size(sentence1_words) == size(sentence2_words)) {
            return false;
        }
        const auto& small_words = size(sentence1_words) < size(sentence2_words) ? sentence1_words : sentence2_words;
        const auto& large_words = size(sentence1_words) < size(sentence2_words) ? sentence2_words : sentence1_words;

        const auto common_prefix = get_common_length(cbegin(small_words), cend(small_words), cbegin(large_words), cend(large_words));
        const auto common_suffix = get_common_length(crbegin(small_words), crend(small_words), crbegin(large_words), crend(large_words));

        return common_prefix + common_suffix == size(small_words);
    }
};

void test(string&& sentence1, string&& sentence2) {
    cout << Solution().areSentencesSimilar(sentence1, sentence2) << endl;
}

int main()
{
    test("qbaVXO Msgr aEWD v ekcb", "Msgr aEWD ekcb");
    test("A", "a A b A");
    test("My name is Haley", "My Haley");
    test("of", "A lot of words");
    test("Eating right now", "Eating");
    return 0;
}