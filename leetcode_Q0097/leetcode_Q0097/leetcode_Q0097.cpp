// leetcode_Q0097.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <utility>
#include <map>

using namespace std;

class Solution {
public:

    using memo_type = map<tuple<size_t, size_t, size_t>, bool>;

    bool isInterleave(const string& s1, size_t index1, const string& s2, size_t index2, const string& s3, size_t index3, memo_type& memo) {
        const auto key = make_tuple(index1, index2, index3);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        if (s3.size() == index3) {
            return s1.size() == index1 && s2.size() == index2;
        }
        
        if (index1 < s1.size() && s1[index1] == s3[index3]) {
            if (isInterleave(s1, index1 + 1, s2, index2, s3, index3 + 1, memo)) {
                memo[key] = true;
                return true;
            }
        }

        if (index2 < s2.size() && s2[index2] == s3[index3]) {
            if (isInterleave(s1, index1, s2, index2 + 1, s3, index3 + 1, memo)) {
                memo[key] = true;
                return true;
            }
        }

        memo[key] = false;
        return false;
    }


    bool isInterleave(string s1, string s2, string s3) {
        memo_type memo;
        return isInterleave(s1, 0, s2, 0, s3, 0, memo);
    }
};


void test(string&& s1, string&& s2, string&& s3) {
    cout << Solution().isInterleave(s1, s2, s3) << endl;
}

int main()
{
    test("a", "b", "a");
    test("aabcc", "dbbca", "aadbbcbcac");
    test("aabcc", "dbbca", "aadbbbaccc");
    test("", "", "");
}

