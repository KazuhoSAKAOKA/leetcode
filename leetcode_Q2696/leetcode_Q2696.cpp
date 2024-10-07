// leetcode_Q2696.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minLength(string s) {
        bool exist = true;
        string current(s);
        const vector<string> removes{ "AB","CD" };
        while (exist) {
            exist = false;
            for (auto&& rm : removes) {
                size_t pos = current.find(rm);
                if (pos != string::npos) {
                    current = current.substr(0, pos) + current.substr(pos + 2);
                    exist = true;
                }
            }
        }
        return static_cast<int>(size(current));
    }
};

void test(string&& s) {
    cout << Solution().minLength(s) << endl;
}
int main()
{
    test("ABFCACDB");
    test("ACBBD");
    return 0;
}