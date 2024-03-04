// leetcode_Q0948.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;


class Solution {
public:

    int bagOfTokensScore(vector<int>& tokens, int power) {
        multiset<int> token_set(cbegin(tokens), cend(tokens));

        int score = 0;
        while (!token_set.empty()) {
            const auto it = token_set.upper_bound(power);
            const auto low_count = distance(cbegin(token_set), it);
            if (low_count == 0) {
                if (score > 0 && token_set.size() > 1) {
                    auto max_it = prev(end(token_set));
                    if (*cbegin(token_set) <= *max_it) {
                        power += *max_it;
                        token_set.erase(max_it);
                        score--;
                        continue;
                    }
                }
                break;
            }
            else {
                power -= *cbegin(token_set);
                token_set.erase(cbegin(token_set));
                score++;
            }
        }
        return score;
    }
};


void test(vector<int>&& tokens, int power) {
    cout << Solution().bagOfTokensScore(tokens, power) << endl;
}

int main()
{
    test({ 100 }, 50);
    test({ 200,100 }, 150);
    test({ 100,200,300, 400 }, 200);
}
