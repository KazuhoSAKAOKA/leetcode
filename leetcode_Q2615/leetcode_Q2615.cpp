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
#include <numbers>
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
    vector<long long> distance(vector<int>& nums) {
        const auto n = size(nums);
        vector<long long> ans(n);

        struct info_t {
            long long index;
            long long value;
            long long count;
        };
        unordered_map<int, info_t> mp;

        auto update = [](unordered_map<int, info_t>& mp, long long i, int num)-> long long {
            auto it = mp.find(num);
            if (it == cend(mp)) {
                mp.insert({ num,info_t{i, 0, 1} });
                return 0LL;
            }
            auto& info = it->second;
            const auto v1 = abs(i - info.index) * info.count;
            const auto cur_val = v1 + info.value;
            info.index = i;
            info.count++;
            info.value = cur_val;
            return cur_val;
            };

        for (long long i = 0; i < n; i++) {
            ans[i] += update(mp, i, nums[i]);
        }
        mp.clear();
        for (long long i = n- 1; i >= 0; i--) {
            ans[i] += update(mp, i, nums[i]);
        }
        return ans;
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
