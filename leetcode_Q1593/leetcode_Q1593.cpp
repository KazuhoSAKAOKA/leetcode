// leetcode_Q1593.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <climits>
using namespace std;

class Solution {
public:

    static int rec(const string& s, size_t index, string& working, unordered_set<string>& current) {
        if (size(s) == index) {
            if (working.empty()) {
                return static_cast<int>(size(current));
            }
            return 0;
        }
        
        working += s[index];
        auto count = rec(s, index + 1, working, current);
            
        if(current.count(working) == 0){
            current.insert(working);
            string new_working;
            count = max(count, rec(s, index + 1, new_working, current));
            current.erase(working);
        }
        working.pop_back();
        return count;
    }


    int maxUniqueSplit(string s) {
        string working;
        unordered_set<string> current;
        return rec(s, 0, working, current);
    }
};

void test(string&& s) {
    cout << Solution().maxUniqueSplit(s) << endl;
}
int main()
{
    test("ababccc");
    test("aba");
    test("aa");
    return 0;
}