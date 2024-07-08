// leetcode_Q1823.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <list>

using namespace std;

class Solution {
public:
    int findTheWinner(int n, int k) {

        list<int> persons;
        for (int i = 0; i < n; i++) {
            persons.push_back(i + 1);
        }
        auto it = begin(persons);

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < k - 1; j++) {
                ++it;
                if (it == end(persons)) {
                    it = begin(persons);
                }
            }
            it = persons.erase(it);
            if (it == end(persons)) {
                it = begin(persons);
            }
        }
        return persons.front();
    }
};

void test(int n, int k) {
    cout << Solution().findTheWinner(n, k) << endl;
}
int main()
{
    test(5, 2);
    test(6, 5);
}