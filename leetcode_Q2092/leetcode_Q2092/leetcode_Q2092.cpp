// leetcode_Q2092.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;
class Solution {
public:


    static vector<int> tle(int n, vector<vector<int>>& meetings, int firstPerson) {
        using PERSON = int;
        using TIME = int;

        unordered_map<PERSON, vector<pair<TIME, PERSON>>> graph;
        for (auto&& meeting : meetings) {
            graph[meeting[0]].emplace_back(make_pair(meeting[2], meeting[1]));
            graph[meeting[1]].emplace_back(make_pair(meeting[2], meeting[0]));
        }
        vector<int> earliest(n, INT_MAX);
        earliest[0] = 0;
        earliest[firstPerson] = 0;

        queue<pair<TIME, PERSON>> tpqueue;
        tpqueue.emplace(make_pair(0, 0));
        tpqueue.emplace(make_pair(0, firstPerson));

        while (!tpqueue.empty()) {
            auto [time, person] = tpqueue.front();
            tpqueue.pop();
            for (auto&& [t, next] : graph[person]) {
                if (t >= time && earliest[next] > t) {
                    earliest[next] = t;
                    tpqueue.push(make_pair(t, next));
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (earliest[i] < INT_MAX) {
                ans.emplace_back(i);
            }
        }

        return ans;
    }


    struct union_find {
        vector<int> _parent;
        vector<int> _size;

        union_find(int n) : _parent(n, 0), _size(n, 1) {
            for (int i = 0; i < n; i++) {
                _parent[i] = i;
            }
        }
        bool is_root(int x) {
            return _parent[x] == x;
        }
        int root(int x) {
            if (_parent[x] == x) { return x; }
            _parent[x] = root(_parent[x]);
            return _parent[x];
        }

        void unite(int x, int y) {
            int rootx = root(x);
            int rooty = root(y);
            if (rootx == rooty) { return; }
            if (_size[rootx] < _size[rooty]) {
                _parent[rootx] = rooty;
                _size[rooty] += _size[rootx];
            }
            else {
                _parent[rooty] = rootx;
                _size[rootx] += _size[rooty];
            }
        }

        bool same(int x, int y) {
            return root(x) == root(y);
        }

        void reset(int x) {
            _parent[x] = x;
            _size[x] = 1;
        }
    };


    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        using PERSON = int;
        using TIME = int;

        unordered_map<TIME, vector<pair<PERSON, PERSON>>> time_map;
        for (auto&& meeting : meetings) {
            const PERSON x = meeting[0];
            const PERSON y = meeting[1];
            const TIME time = meeting[2];
            time_map[time].emplace_back(make_pair(x, y));
        }
        union_find uf(n);
        uf.unite(0, firstPerson);

        for (auto&& [_, edges] : time_map) {
            unordered_set<PERSON> appends;
            for (auto&& edge : edges) {
                appends.insert(edge.first);
                appends.insert(edge.second);
                uf.unite(edge.first, edge.second);
            }
            const auto knowns = uf.root(0);
            for (auto&& v : appends) {
                if (uf.root(v) != knowns) {
                    uf.reset(v);
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (uf.same(0, i)) {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};

void test(int n, vector<vector<int>>&& meetings, int firstPerson) {
    const auto ans = Solution().findAllPeople(n, meetings, firstPerson);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

int main()
{
    test(6, { {1, 2, 5},{2, 3, 8},{1, 5, 10} }, 1);
    test(4, { {3,1,3},{1,2,2},{0,3,3} }, 3);
    test(5, { {3,4,2},{1,2,1},{2,3,1} }, 1);
}