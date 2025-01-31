// leetcode_Q0827.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

class Solution {
public:

    struct union_find {

        std::vector<size_t> parents_;
        std::vector<size_t> sizes_;

        union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
            for (size_t i = 0; i < n; i++) {
                parents_[i] = i;
            }
        }

        size_t root(size_t x) {
            if (x == parents_[x]) { return x; }
            parents_[x] = root(parents_[x]);
            return parents_[x];
        }

        bool same(size_t x, size_t y) {
            return root(x) == root(y);
        }

        void unite(size_t x, size_t y) {
            const auto rootx = root(x);
            const auto rooty = root(y);
            if (rootx == rooty) { return; }
            if (sizes_[rootx] < sizes_[rooty]) {
                parents_[rootx] = rooty;
                sizes_[rooty] += sizes_[rootx];
            }
            else {
                parents_[rooty] = rootx;
                sizes_[rootx] += sizes_[rooty];
            }
        }

        size_t size(size_t x) {
            return sizes_[root(x)];
        }

        bool is_root(size_t x) {
            return root(x) == x;
        }
    };

    int largestIsland(vector<vector<int>>& grid) {
        const auto H = size(grid);
        const auto W = size(grid.front());
        const auto N = H * W;
        union_find uf(N);
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (grid[y][x] != 0) {
                    const auto index = y * W + x;
                    if (y < H - 1) {
                        if (grid[y + 1][x] != 0) {
                            uf.unite(index, (y + 1) * W + x);
                        }
                    }
                    if (x < W - 1) {
                        if (grid[y][x + 1] != 0) {
                            uf.unite(index, y * W + x + 1);
                        }
                    }
                }
            }
        }
        int max_lands = 0;
        map<int, int> land_map;
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (grid[y][x] != 0) {
                    const auto root = uf.root(uf.root(y * W + x));
                    land_map[root]++;
                    max_lands = max(max_lands, land_map[root]);
                }
            }
        }

        const vector<pair<int, int>> directions{
            {-1,0},{1,0},{0,-1},{0,1},
        };
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (grid[y][x] == 0) {

                    int current_lands = 1;
                    set<int> used_land;
                    const auto index = y * W + x;
                    for (auto&& [dy, dx] : directions) {
                        const auto n_y = y + dy;
                        const auto n_x = x + dx;
                        if (0 <= n_y && n_y < H && 0 <= n_x && n_x < W && grid[n_y][n_x] != 0) {
                            const auto root = uf.root(n_y * W + n_x);
                            if (used_land.count(root) == 0) {
                                current_lands += land_map[root];
                                used_land.insert(root);
                            }
                        }
                    }
                    max_lands = max(max_lands, current_lands);
                }
            }
        }


        return max_lands;
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
