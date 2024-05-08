// leetcode_Q0506.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        vector<pair<int, size_t>> score_indexs;
        const size_t N = score.size();
        score_indexs.reserve(N);
        for (size_t i = 0; i < N; i++) {
            score_indexs.emplace_back(make_pair(score[i], i));
        }
        
        sort(begin(score_indexs), end(score_indexs));
        vector<string> ans(N, "");

        if (N > 0) {
            ans[score_indexs[N - 1].second] = "Gold Medal";
            if (N > 1) {
                ans[score_indexs[N - 2].second] = "Silver Medal";
                if (N > 2) {
                    ans[score_indexs[N - 3].second] = "Bronze Medal";
                    for (size_t i = 0; i < score.size() - 3; i++) {
                        ans[score_indexs[i].second] = to_string(N - i);
                    }
                }
            }
        }
        return ans;
    }
};


void test(vector<int>&& score) {
    const auto ans = Solution().findRelativeRanks(score);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}


int main()
{
    test({ 10, });
    test({ 11,12 });
    test({ 20,19,18, });
    test({ 17,20,19,18, });
    test({5,4,3,2,1,});
    test({10,3,8,9,4,});

}