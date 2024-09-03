// leetcode_Q1945.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    static int transform(int value) {
        int current = value;
        int total = 0;
        while (current > 0) {
            total += current % 10;
            current /= 10;
        }
        return total;
    }

    static int convert_transform(const string& s) {
        int transformed = 0;
        for (auto&& c : s) {
            auto value = static_cast<int>(c - 'a' + 1);
            transformed += transform(value);
        }
        return transformed;
    }

    int getLucky(string s, int k) {
        auto current = convert_transform(s);
        for (int i = 0; i < k - 1; i++) {
            current = transform(current);
        }
        return current;
    }
};

void test(string&& s, int k) {
    cout << Solution().getLucky(s, k) << endl;
}
int main()
{
    test("iiii", 1);
    test("leetcode", 2);
    test("zbax", 2);
    return 0;
}