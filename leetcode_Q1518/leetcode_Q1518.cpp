// leetcode_Q1518.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        if (numExchange == 0) {
            return 0;
        }
        int count = 0;
        int current_bottles = numBottles;
        int empty_bottles = 0;
        while (current_bottles > 0) {
            count += current_bottles;
            empty_bottles += current_bottles;
            current_bottles = empty_bottles / numExchange;
            empty_bottles %= numExchange;
        }

        return count;
    }
};

void test(int numBottles, int numExchange) {
    cout << Solution().numWaterBottles(numBottles, numExchange) << endl;
}
int main()
{
    test(9, 3);
    test(15, 4);
}