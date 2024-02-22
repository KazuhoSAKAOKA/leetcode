// leetcode_Q0997.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        if (n == 1 && trust.empty()) { return 1; }
        unordered_map<int, int> trust_rev;
        unordered_set<int> removes;

        for (auto&& value : trust) {
            removes.insert(value[0]);
            trust_rev[value[1]]++;
        }
        int ans = -1;
        for (auto& [k,v] : trust_rev) {
            if (removes.find(k) == cend(removes) && v == n - 1) {
                if(ans == -1){
                    ans = k;
                }
                else {
                    return -1;
                }
            }
        }
        return ans;
    }
};

void test(int n, vector<vector<int>>&& trust) {
    cout << Solution().findJudge(n, trust) << endl;
}

int main()
{
    test(1, {});
    test(3, { {1,2},{2,3} });
    test(2, { { 1,2 } });
    test(3, { {1,3},{2,3} });
    test(3, { {1,3},{2,3},{3,1} });
}