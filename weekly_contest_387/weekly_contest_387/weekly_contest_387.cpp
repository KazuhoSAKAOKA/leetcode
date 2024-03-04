// weekly_contest_387.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;


namespace problem1 {

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> ans;
        if (nums.size() < 2) { return ans; }
        vector<int> arr1;
        vector<int> arr2;
        arr1.emplace_back(nums[0]);
        arr2.emplace_back(nums[1]);

        for (int i = 2; i < nums.size(); i++) {
            if (arr1.back() > arr2.back()) {
                arr1.emplace_back(nums[i]);
            }
            else {
                arr2.emplace_back(nums[i]);
            }
        }

        ans.reserve(nums.size());
        copy(cbegin(arr1), cend(arr1), back_inserter(ans));
        copy(cbegin(arr2), cend(arr2), back_inserter(ans));

        return ans;
    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().resultArray(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

void run() {
    test({2,1,3});
    test({ 5,4,3,8 });
}

}



namespace problem2 {

class Solution {
public:

    int countSubmatrices(vector<vector<int>>& grid, int k) {
        vector<vector<int>> sums(grid.size() + 1, vector<int>(grid.front().size() + 1, 0));

        for (auto i = 0; i < grid.size(); i++) {
            for (auto j = 0; j < grid.front().size(); j++) {
                sums[i + 1][j + 1] = sums[i + 1][j] + grid[i][j];
            }
        }
        for (auto i = 0; i < grid.size(); i++) {
            for (auto j = 0; j < grid.front().size(); j++) {
                sums[i + 1][j + 1] += sums[i][j + 1];
            }
        }

        int count = 0;
        for (auto i = 0; i < grid.size(); i++) {
            for (auto j = 0; j < grid.front().size(); j++) {
                const auto value = sums[i + 1][j + 1];
                if (value <= k) {
                    count++;
                }
            }
        }

        return count;

    }
};

void test(vector<vector<int>>&& grid, int k) {
    cout << Solution().countSubmatrices(grid, k) << endl;
}

void run() {
    test({ {7,6,3 },{6,6,1} }, 18);
    test({ {7,2,9},{1,5,0},{2,6,6} }, 20);
}
}



namespace problem3 {

class Solution {
public:

    static bool is_Y(size_t n, size_t x, size_t y)
    {
        if (x == y && x == n / 2) {
            return true;
        }
        if (y < n / 2) {
            return x == y || (n - x - 1) == y;
        }
        else {
            return x == n / 2;
        }
    }

    static int sum1(const vector<int>& values, int ignore) {
        int s = 0;
        for (int i = 0; i < values.size(); i++) {
            if (i != ignore) {
                s += values[i];
            }
        }
        return s;
    }


    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        const size_t n = grid.size();

        vector<int> using_y(3, 0);
        vector<int> not_using_y(3, 0);
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                if (is_Y(n, j, i)) {
                    using_y[grid[i][j]]++;
                }
                else {
                    not_using_y[grid[i][j]]++;
                }
            }
        }

        int min_value = INT_MAX;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) { continue; }
                const auto y_change_count = sum1(using_y, i);
                const auto not_y_change_count = sum1(not_using_y, j);
                min_value = min(min_value, y_change_count + not_y_change_count);
            }
        }
        return min_value;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().minimumOperationsToWriteY(grid) << endl;
}

void run() {
    test({ {1,2,2},{1,1,0},{0,1,0} });
    test({ {0,1,0,1,0},{2,1,0,1,2},{2,2,2,0,1},{2,2,2,2,2},{2,1,2,2,2} });
}
}


namespace problem4 {

class Solution {
public:

    static int get_greater_count(const vector<int>& arr, int val, const map<int, int>& counts_map, const set<int>& values) {
        auto it_begin = upper_bound(cbegin(values), cend(values), val);
        int count = 0;
        for (auto it = it_begin; it != cend(values); ++it) {
            if (val < *it) {
                count += counts_map.at(*it);
            }
        }
        return count;
    }

    struct binary_indexed_tree {
        const int _n;
        vector<int> _values;

        binary_indexed_tree(int n):_n(n + 1), _values(n + 1, 0){
        }

        void add(int index, int v) {
            for (int i = index + 1; i < _n; i += (i & -i)) {
                _values[i] += v;
            }
        }

        int sum(int index) {
            int total = 0;
            for (int i = index + 1; i > 0; i -= (i & -i)) {
                total += _values[i];
            }
            return total;
        }

        int sum(int l, int r) {
            return sum(r) - sum(l);
        }
    };


    vector<int> resultArray(vector<int>& nums) {
        vector<int> ans;
        ans.reserve(nums.size());
        if (nums.size() < 2) { return ans; }
        set<int> exists(cbegin(nums), cend(nums));
        map<int, int> value_to_index_map;
        int index = 0;
        for (auto&& value : exists) {
            value_to_index_map[value] = index;
            index++;
        }
        binary_indexed_tree a1tree(nums.size());
        binary_indexed_tree a2tree(nums.size());
        vector<int> arr2;
        ans.emplace_back(nums[0]);
        a1tree.add(value_to_index_map[nums[0]], 1);
        arr2.emplace_back(nums[1]);
        a2tree.add(value_to_index_map[nums[1]], 1);

        for (int i = 2; i < nums.size(); i++) {
            const int index = value_to_index_map[nums[i]];
            const auto v1 = ans.size() - a1tree.sum(index);
            const auto v2 = arr2.size() - a2tree.sum(index);
            bool addtoa1;

            if (v1 > v2) {
                addtoa1 = true;
            }
            else if (v1 < v2){
                addtoa1 = false;
            }
            else {
                if (ans.size() <= arr2.size()) {
                    addtoa1 = true;
                }
                else {
                    addtoa1 = false;
                }
            }
            if (addtoa1) {
                ans.emplace_back(nums[i]);
                a1tree.add(value_to_index_map[nums[i]], 1);
            }
            else {
                arr2.emplace_back(nums[i]);
                a2tree.add(value_to_index_map[nums[i]], 1);
            }

        }

        copy(cbegin(arr2), cend(arr2), back_inserter(ans));

        return ans;

    }
};

void test(vector<int>&& nums) {
    const auto ans = Solution().resultArray(nums);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}

void run() {
    test({ 64,459,340,990 });
    test({ 2,1,3,3 });
    test({ 5,14,3,1,2 });
    test({ 3,3,3,3 });
}

}




int main()
{
//    problem1::run();
//    problem2::run();
//    problem3::run();
    problem4::run();
}