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
#include <numbers>
#include <iomanip>
#include <exception>
using namespace std;
constexpr long long MODULO = 1e9 + 7;

class Fancy {
    vector<long long> values_;
    vector<size_t> op_indexes_;
    vector<pair<int, long long>> operations_;
public:
    Fancy() {

    }

    void append(int val) {
        values_.emplace_back(val);
    }

    void addAll(int inc) {
        const auto n = size(values_);
        if (op_indexes_.empty() || op_indexes_.back() != n || operations_.back().first != 1) {
            op_indexes_.emplace_back(n);
            operations_.emplace_back(make_pair(1, inc));
        }
        else {
            operations_.back().second += inc;
            operations_.back().second %= MODULO;
        }
    }

    void multAll(int m) {
        const auto n = size(values_);
        if (op_indexes_.empty() || op_indexes_.back() != n || operations_.back().first != 2) {
            op_indexes_.emplace_back(n);
            operations_.emplace_back(make_pair(2, m));
        }
        else {
            operations_.back().second *= m;
            operations_.back().second %= MODULO;
        }
    }

    int getIndex(int idx) {
        const auto n = size(values_);
        if (n <= idx) { return -1; }
        const auto op_start_it = upper_bound(cbegin(op_indexes_), cend(op_indexes_), idx);
        const auto op_start_index = distance(cbegin(op_indexes_), op_start_it);
        long long value = values_[idx];
        for (long long i = op_start_index; i < size(operations_); i++) {
            const auto& [optype, opval] = operations_[i];
            if (optype == 1) {
                value += opval;
            }
            else {
                value *= opval;
            }
            value %= MODULO;
        }
        return static_cast<int>(value);
    }
};
/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
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
