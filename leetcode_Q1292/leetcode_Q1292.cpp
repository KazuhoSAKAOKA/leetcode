#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <climits>
#include <cassert>
#include <tuple>
#include <chrono>
#include <optional>
#include <queue>
#include <memory>
#include <random>
#include <exception>
#include <functional>
#include <ranges>
#include <iomanip>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        const auto n = size(mat);
        const auto m = size(mat[0]);
        vector<vector<long long>> prefix_sums(n + 1, vector<long long>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + mat[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto get_sum = [&](int y1, int x1, int y2, int x2)-> long long {
            return prefix_sums[y2][x2] - prefix_sums[y1][x2] - prefix_sums[y2][x1] + prefix_sums[y1][x1];
            };

        int max_len = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                const auto limit = min(n - i, m - j);
                int len = 1;
                while (len <= limit) {
                    const int total = get_sum(i, j, i + len, j + len);
                    if (threshold < total) {
                        break;
                    }
                    max_len = max(max_len, len);
                    len++;
                }
            }
        }

        return max_len;
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
