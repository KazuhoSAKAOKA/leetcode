// leetcode_Q2373.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {

    ///https://nyaannyaan.github.io/library/data-structure-2d/2d-segment-tree.hpp.html

    template <typename T, typename F>
    struct SegmentTree2D {
    private:
        int id(int h, int w) const { return h * 2 * W + w; }

    public:
        int H, W;
        vector<T> seg;
        const F f;
        const T I;

        SegmentTree2D(int h, int w, F _f, const T& i) : f(_f), I(i) { init(h, w); }

        void init(int h, int w) {
            H = W = 1;
            while (H < h) H <<= 1;
            while (W < w) W <<= 1;
            seg.assign(4 * H * W, I);
        }

        // build にのみ呼ぶ
        void set(int h, int w, const T& x) { seg[id(h + H, w + W)] = x; }

        void build() {
            // w in [W, 2W)
            for (int w = W; w < 2 * W; w++) {
                for (int h = H - 1; h; h--) {
                    seg[id(h, w)] = f(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]);
                }
            }
            // h in [0, 2H)
            for (int h = 0; h < 2 * H; h++) {
                for (int w = W - 1; w; w--) {
                    seg[id(h, w)] = f(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]);
                }
            }
        }

        T get(int h, int w) const { return seg[id(h + H, w + W)]; }
        T operator()(int h, int w) const { return seg[id(h + H, w + W)]; }

        void update(int h, int w, const T& x) {
            h += H, w += W;
            seg[id(h, w)] = x;
            for (int i = h >> 1; i; i >>= 1) {
                seg[id(i, w)] = f(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]);
            }
            for (; h; h >>= 1) {
                for (int j = w >> 1; j; j >>= 1) {
                    seg[id(h, j)] = f(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]);
                }
            }
        }

        T _inner_query(int h, int w1, int w2) {
            T res = I;
            for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
                if (w1 & 1) res = f(res, seg[id(h, w1)]), w1++;
                if (w2 & 1) --w2, res = f(res, seg[id(h, w2)]);
            }
            return res;
        }

        // [ (h1,w1), (h2,w2) ) 半開
        T query(int h1, int w1, int h2, int w2) {
            if (h1 >= h2 || w1 >= w2) return I;
            T res = I;
            h1 += H, h2 += H, w1 += W, w2 += W;
            for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
                if (h1 & 1) res = f(res, _inner_query(h1, w1, w2)), h1++;
                if (h2 & 1) --h2, res = f(res, _inner_query(h2, w1, w2));
            }
            return res;
        }
    };

	static int get_max(int a, int b) { return max(a, b); }

	using st = SegmentTree2D<int, std::function<int(int, int)>>;

public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
		st stree(grid.size(), grid.front().size(), get_max, INT_MIN);
		const size_t n = grid.size();
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid.front().size(); j++) {
				stree.set(i, j, grid[i][j]);
			}
		}
		stree.build();
		vector<vector<int>> ans(grid.size() - 2, vector<int>(grid.front().size() - 2, 0));

		for (int i = 0; i < grid.size() - 2; i++) {
			for (int j = 0; j < grid.front().size() - 2; j++) {
				ans[i][j] = stree.query(i, j, i + 3, j + 3);
			}
		}

		return ans;
    }
};

void test(vector<vector<int>>&& grid) {
    const auto ans = Solution().largestLocal(grid);
    for (auto&& list : ans) {
        for (auto&& value : list) {
            cout << value << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    test({ {2, 5, 5
}, { 3, 2, 5
}, { 1, 2, 3
} });
    test({ {9,9,8,1,},{5,6,2,6,},{8,2,6,4,},{6,2,2,2,}, });
    test({ {1,1,1,1,1,},{1,1,1,1,1,},{1,1,2,1,1,},{1,1,1,1,1,},{1,1,1,1,1,}, });
}