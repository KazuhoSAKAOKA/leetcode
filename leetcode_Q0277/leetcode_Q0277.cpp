// leetcode_Q0277.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <set>
using namespace std;

bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        set<int> candidates;
        for (int i = 0; i < n; i++) {
            candidates.insert(i);
        }

        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                if (a == b) { continue; }
                if (candidates.count(b) == 0) { continue; }
                if (knows(a, b)) {
                    candidates.erase(a);
                }
                else {
                    candidates.erase(b);
                }
            }
        }

        if (candidates.empty()) {
            return -1;
        }
        return *cbegin(candidates);
    }
};
int main()
{
    std::cout << "Hello World!\n";
}

