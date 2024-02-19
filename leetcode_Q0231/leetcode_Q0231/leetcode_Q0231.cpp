// leetcode_Q0231.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class Solution {
public:


    bool isPowerOfTwo(int n) {
        if (n < 0) { return false; }
        for (int i = 0; i < 32; i++) {
            if (n == (1 << i)) {
                return true;
            }
        }
        return false;
    }
};


void test(int n) {
    cout << (Solution().isPowerOfTwo(n) ? "true" : "false") << endl;
}

int main(){
    test(1);
    test(16);
    test(3);
    test(pow(2, 31));
}