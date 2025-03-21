﻿// leetcode_Q2226.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>


#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

template <typename T = long long>
T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
    while (abs(ng - ok) > 1) {
        const auto mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        }
        else {
            ng = mid;
        }
    }
    return ok;
}


class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        const long long total = accumulate(cbegin(candies), cend(candies), 0LL, [](long long a, long long b) { return a + b; });
        auto check = [&](long long v)->bool {
            long long total = 0;
            for (auto&& candy : candies) {
                total += candy / v;
            }
            return total >= k;
            };
        return binary_search_meguru<long long>(0LL, total / k + 1LL, check);
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
