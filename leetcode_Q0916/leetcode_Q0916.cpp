// leetcode_Q0916.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static void counting(const string& word, vector<int>& freqs) {
        for (auto&& c : word) {
            freqs[c - 'a']++;
        }
    }
    static bool including(const vector<int>& freq1, const vector<int>& freq2) {
        for (int i = 0; i < 26; i++) {
            if (freq1[i] < freq2[i]) { return false; }
        }
        return true;
    }

    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        
        vector<int> words2_freq(26);
        for (int i = 0; i < size(words2); i++) {
            vector<int> cur_freq(26);
            counting(words2[i], cur_freq);
            for (int j = 0; j < 26; j++) {
                words2_freq[j] = max(words2_freq[j], cur_freq[j]);
            }
        }
        vector<string> ans;
        for (auto&& word : words1) {
            vector<int> freqs(26);
            counting(word, freqs);
            if (including(freqs, words2_freq)) {
                ans.emplace_back(word);
            }
        }
        return ans;
    }
};


void test(vector<string>&& words1, vector<string>&& words2) {
    output(Solution().wordSubsets(words1, words2));
}
int main()
{

    return 0;
}