// leetcode_Q1239.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:

    static int rec(const vector<string>& arr, int index, unordered_set<char>& current_char_set) {
        if (arr.size() == index) {
            return current_char_set.size();
        }
        
        int max_len = current_char_set.size();

        for (int i = index; i < arr.size(); i++) {
            const string& s = arr[i];
            if (all_of(cbegin(s), cend(s), [&](const auto c) { return current_char_set.find(c) == cend(current_char_set); })) {
                const size_t current_size = current_char_set.size();
                for (auto&& c: s) {
                    current_char_set.insert(c);
                }
                if (current_size + s.size() == current_char_set.size()) {
                    max_len = max(max_len, rec(arr, i + 1, current_char_set));
                }
                for (auto&& c : s) {
                    current_char_set.erase(c);
                }
            }
        }
        return max_len;
    }


    int maxLength(vector<string>& arr) {
        unordered_set<char> current;
        return rec(arr, 0, current);
    }
};

void test(vector<string>&& arr) {
    cout << Solution().maxLength(arr) << endl;
}

int main()
{
    test({ "aa","bb","cc", "de"});
    test({ "un","iq","ue" });
    test({ "cha","r","act","ers"});
    test({ "abcdefghijklmnopqrstuvwxyz" });
}