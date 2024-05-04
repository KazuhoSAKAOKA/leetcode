// leetcode_Q0881.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        multiset<int> values(cbegin(people), cend(people));
        int count = 0;
        while (!values.empty()) {
            auto it = begin(values);
            const auto value = *it;
            values.erase(it);
            if (value < limit) {
                const auto remain = limit - value;
                auto pair_it = values.upper_bound(remain);
                if (pair_it != begin(values)) {
                    auto prev_it = prev(pair_it);
                    values.erase(prev_it);
                }
            }
            count++;
        }
        return count;
    }
};

void test(vector<int>&& people, int limit) {
    cout << Solution().numRescueBoats(people, limit) << endl;
}

int main()
{
    test({ 1, }, 3);

    test({ 1,2, }, 3);
    test({ 3,2,2,1, }, 3);
    test({ 3,5,3,4, }, 5);
    test({ 1,2,3, }, 4);
}