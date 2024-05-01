// leetcode_Q2000.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string reversePrefix(string word, char ch) {
        stack<char> st;
        int index = 0;
        
        while (index < word.size()) {
            const char c = word[index++];
            st.push(c);
            if (c == ch) {
                string ans;
                ans.reserve(word.size());
                while (!st.empty()) {
                    ans.push_back(st.top());
                    st.pop();
                }
                for (int i = index; i < word.size(); i++) {
                    ans.push_back(word[i]);
                }
                return ans;
            }
        }
        return word;
    }
};

void test(string&& word, char ch) {
    cout << Solution().reversePrefix(word, ch) << endl;
}

int main()
{
    test("abcdefd", 'd');
    test("xyxzxe", 'z');
    test("abcd", 'z');
}