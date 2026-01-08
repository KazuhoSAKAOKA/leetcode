#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        const auto n = size(nums1);
        const auto m = size(nums2);
        vector<vector<int>> dp(n, vector<int>(m));
        dp[0][0] = nums1[0] * nums2[0];
        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i-1][0], nums1[i] * nums2[0]);
        }
        for (int j = 1; j < m; j++) {
            dp[0][j] = max(dp[0][j - 1], nums1[0] * nums2[j]);
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                int value = max(dp[i - 1][j], dp[i][j - 1]);
                value = max(value, dp[i - 1][j - 1]);
                value = max(value, dp[i - 1][j - 1] + nums1[i] * nums2[j]);
                value = max(value, nums1[i] * nums2[j]);
                dp[i][j] = value;
            }
        }
        return dp.back().back();
    }
};
int main()
{
    std::cout << "Hello World!\n";
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
