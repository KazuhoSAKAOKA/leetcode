// leetcode_Q3066.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        priority_queue<long long, vector<long long>, std::greater<long long>> pq;
        for (auto&& num : nums) {
            pq.push(num);
        }

        int count = 0;
        while (pq.top() < k) {
            const auto v1 = pq.top();
            pq.pop();
            const auto v2 = pq.top();
            pq.pop();
            const auto v = min(v1, v2) * 2 + max(v1, v2);
            pq.push(v);
            count++;
        }
        return count;
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
