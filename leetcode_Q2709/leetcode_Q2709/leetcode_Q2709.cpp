// leetcode_Q2709.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;


class Solution {
public:

    struct union_find {
        
        vector<int> _parents;
        vector<int> _sizes;

    public:
        union_find(int n) : _parents(n, 0), _sizes(n, 1) {
            for (int i = 0; i < n; i++) {
                _parents[i] = i;
            }
        }

        int root(int x) {
            if (x == _parents[x]) { return x; }
            _parents[x] = root(_parents[x]);
            return _parents[x];
        }

        bool same(int x, int y) {
            return root(x) == root(y);
        }

        void unite(int x, int y) {
            int rootx = root(x);
            int rooty = root(y);
            if (rootx == rooty) { return; }
            if (_sizes[rootx] < _sizes[rooty]) {
                _parents[rootx] = rooty;
                _sizes[rooty] += _sizes[rootx];
            }
            else {
                _parents[rooty] = rootx;
                _sizes[rootx] += _sizes[rooty];
            }
        }
    };


    static int gcd(int a, int b) {
        const auto r = a % b;
        if (r == 0) { return b; }
        return gcd(b, r);
    }

    bool canTraverseAllPairs(vector<int>& nums) {
        if (nums.size() == 1) { return true; }
        if (any_of(cbegin(nums), cend(nums), [](const auto& v) { return v == 1; })) { return false; }

        union_find groups(nums.size());
        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (gcd(nums[i], nums[j]) > 1) {
                    groups.unite(i, j);
                }
            }
        }

        for (int i = 1; i < nums.size(); i++) {
            if (!groups.same(0, i)) {
                return false;
            }
        }
        return true;
    }
};


void test(vector<int>&& nums) {
    cout << Solution().canTraverseAllPairs(nums) << endl;
}

int main()
{
    test({ 1,1 });
    test({2,3,6,});
    test({3,9,5});
    test({4,3,12,8,});
}