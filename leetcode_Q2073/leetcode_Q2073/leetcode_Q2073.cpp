// leetcode_Q2073.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        set<int> indexes;
        for (int i = 0; i < tickets.size(); i++) {
            indexes.insert(i);
        }
        int count = 0;
        while(tickets[k] > 0) {
            for (auto it = begin(indexes); it != end(indexes);) {
                count++;
                tickets[*it]--;
                if (tickets[*it] == 0) {
                    it = indexes.erase(it);
                }
                else {
                    ++it;
                }
                if (tickets[k] == 0) {
                    break;
                }
            }
        }

        return count;
    }
};


void test(vector<int>&& tickets, int k) {
    cout << Solution().timeRequiredToBuy(tickets, k) << endl;
}


int main()
{
    test({ 2,3,2 }, 2);
    test({ 5,1,1,1, }, 0);
}