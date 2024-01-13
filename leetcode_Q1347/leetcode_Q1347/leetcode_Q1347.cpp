// leetcode_Q1347.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    int minSteps(string s, string t) {

        map<char, int> map;
        for (int i = 0; i < s.size(); i++) {
            map[s[i]]++;
        }

        int count = 0;
        for (int i = 0; i < t.size(); i++) {
            if (map[t[i]] == 0) {
                count++;
            }
            else {
                map[t[i]]--;
            }
           
        }
        return count;
    }
};

void test(string&& s, string&& t) {
    cout << Solution().minSteps(s, t) << endl;
}


int main()
{
    test("bab", "aba");
    test("leetcode", "practice");
    test("anagram", "mangaar");
}