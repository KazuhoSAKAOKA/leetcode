// leetcode_Q1137.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:

    static long tribonacci(int n, unordered_map<int, int>& memo) {
        if (n == 0) { return 0; }
        if (n == 1 || n == 2) { return 1; }
        const auto it = memo.find(n);
        if (it != cend(memo)) {
            return it->second;
        }
        const auto v = tribonacci(n - 3, memo) + tribonacci(n - 2, memo) + tribonacci(n - 1, memo);
        memo[n] = v;
        return v;
    }


    int tribonacci(int n) {
        unordered_map<int, int> memo;
        return tribonacci(n, memo);
    }
};

void test(int n) {
    cout << Solution().tribonacci(n) << endl;
}


int main()
{
    test(4);
    test(25);
    test(37);
}