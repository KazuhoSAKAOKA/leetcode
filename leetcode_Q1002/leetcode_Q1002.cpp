// leetcode_Q1002.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {

        vector<unordered_map<char, int>> freqss;
        freqss.reserve(words.size());
        auto create_freq_map = [](const string& word) {
            unordered_map<char, int> freqs;
            for(auto&& c: word){
                freqs[c]++;
            }
            return freqs;
            };
        for (auto&& word : words) {
            freqss.emplace_back(create_freq_map(word));
        }

        vector<string> ans;
        for (char c = 'a'; c <= 'z'; c++){
            int min_count = INT_MAX;
            for (int i = 0; i < freqss.size(); i++) {
                const auto it = freqss[i].find(c);
                if (it != cend(freqss[i])) {
                    min_count = min(min_count, it->second);
                }
                else {
                    min_count = 0;
                }
            }
            if (min_count != INT_MAX) {
                for (int i = 0; i < min_count; i++) {
                    ans.push_back(string(1, c));
                }
            }
        }
        return ans;
    }
};

void test(vector<string>&& words) {
    const auto ans = Solution().commonChars(words);
    for (auto&& s : ans) {
        cout << s << ",";
    }
    cout << endl;
}


int main()
{
    test(get_list_str(R"(["bella","label","roller"])"));
    test(get_list_str(R"(["cool","lock","cook"])"));
}