// leetcode_Q1925.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    int countTriples(int n) {
        int count = 0;
        bool exit = false;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                const auto k = i * i + j * j;
                const auto cand2 = static_cast<long long>(sqrt(k));
                if (n < cand2) {
                    break;
                }
                if (cand2 * cand2 == k) {
                    count++;
                }
            }
        }
        return count;
    }
};

static void test(int n) {
    cout << Solution().countTriples(n) << endl;
}
int main()
{

    test(10);
    return 0;
}