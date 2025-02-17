// leetcode_Q1079.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    static void rec(const string& tiles, vector<bool>& used, string& current, set<string>& totalset) {
        if (size(tiles) == size(current)) { return; }
        
        for (int i = 0; i < size(tiles); i++) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(tiles[i]);
                totalset.insert(current);
                rec(tiles, used, current, totalset);
                current.pop_back();
                used[i] = false;
            }
        }
    }


    int numTilePossibilities(string tiles) {
        set<string> totalset;
        string current;
        vector<bool> used(size(tiles));
        rec(tiles, used, current, totalset);
        return static_cast<int>(size(totalset));
    }
};

void test(string&& tiles) {
    cout << Solution().numTilePossibilities(tiles) << endl;
}

int main()
{
    test("ABC");
    test("AAB");

    test("AB");
    test("AAABBC");
    test("V");
    return 0;
}