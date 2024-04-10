// leetcode_Q0950.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(begin(deck), end(deck));
        if (deck.size() < 3) {
            return vector<int>(cbegin(deck), cend(deck));
        }

        vector<int> working(deck.size() * 2, 0);
        for (int i = 0; i < deck.size(); i++) {
            working[i * 2] = deck[i];
        }
        int index = (deck.size() - 1) * 2;
        int index2 = index - 3;
        working[index2] = working[index];
        index -= 2;
        index2 -= 2;
        while (index2 > 0) {
            working[index2] = working[index];
            index--;
            index2 -= 2;
        }
        return vector<int>(cbegin(working), next(cbegin(working), deck.size()));
    }
};

void test(vector<int>&& deck) {
    const auto ans = Solution().deckRevealedIncreasing(deck);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test({ 1,2,3,4,5,6, });
    test({ 17,13,11,2,3,5,7 });
    test({ 1,1000 });
}