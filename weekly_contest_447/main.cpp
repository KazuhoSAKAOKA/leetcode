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
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
    class Solution {
    public:
        int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
            
            vector<set<int>> xlist(n + 1);
            vector<set<int>> ylist(n + 1);
            for (auto&& building : buildings) {
                const auto x = building.front();
                const auto y = building.back();
                xlist[x].insert(y);
                ylist[y].insert(x);
            }
            int count = 0;

            for (auto&& building : buildings) {
                const auto x = building.front();
                const auto y = building.back();
                const auto xit = xlist[x].find(y);
                const auto yit = ylist[y].find(x);
                if (xit != cbegin(xlist[x]) && next(xit) != cend(xlist[x]) && yit != cbegin(ylist[y]) && next(yit) != cend(ylist[y])) {
                    count++;
                }
            }
            return count;
        }
    }; 
    void test(int n, vector<vector<int>>&& buildings) {
        cout << Solution().countCoveredBuildings(n, buildings) << endl;
    }

static void run() {
    test(3, get_matrix_int("[[1,2],[2,2],[3,2],[2,1],[2,3]]"));
    test(3, get_matrix_int("[[1,1],[1,2],[2,1],[2,2]]"));
    test(5, get_matrix_int("[[1,3],[3,2],[3,3],[3,5],[5,3]]"));
}
}
namespace problem2 {
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
    static vector<bool> tle(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        union_find uf(n);
        for (int i = 0; i < n; i++) {
            int j = i + 1;
            while (j < n && abs(nums[j] - nums[i]) <= maxDiff) {
                uf.unite(i, j);
                j++;
            }
        }
        vector<bool> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            ans.emplace_back(uf.same(query.front(), query.back()));
        }
        return ans;
    }


    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        set<int> walls;
        for (int i = 0; i < n - 1; i++) {
            if (nums[i + 1] - nums[i] > maxDiff) {
                walls.insert(i);
            }
        }

        vector<bool> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            const int low = min(query.front(), query.back());
            const int high = max(query.front(), query.back());
            const auto lowit = walls.lower_bound(low);
            const auto highit = walls.lower_bound(high);
            ans.emplace_back(lowit == highit);
        }
        return ans;
    }
};
void test(int n, vector<int>&& nums, int maxDiff, vector<vector<int>>&& queries) {
    output(Solution().pathExistenceQueries(n, nums, maxDiff, queries));
}

static void run() {
    test(2, get_list_int("[1,3]"), 1, get_matrix_int("[[0,0],[0,1]]"));
    test(4, get_list_int("[2,5,6,8]"), 2, get_matrix_int("[[0,1],[0,2],[1,3],[2,3]]"));
}
}
namespace problem3 {
class Solution {
public:

    static vector<int> convert_digits(const vector<int>& nums) {
        vector<int> digits;
        for (auto&& num : nums) {
            int cur = num;
            if (cur == 0) {
                digits.emplace_back(0);
            }
            else {
                vector<int> temp;
                while (cur > 0) {
                    temp.emplace_back(cur % 10);
                    cur /= 10;
                }
                digits.insert(end(digits), crbegin(temp), crend(temp));
            }
        }
        return digits;
    }

    static bool divisible(const vector<int>& nums, int k) {
        const auto digits = convert_digits(nums);
        int cur = 0;
        for (auto&& digit : digits) {
            cur = cur * 10 + digit;
            cur %= k;
        }
        return cur == 0;
    }

    static vector<int> tle(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));

        do {
            if (divisible(nums, k)) {
                return nums;
            }
        } while (next_permutation(begin(nums), end(nums)));

        return vector<int>{};
    }

    static int get_columns(int num) {
        if (num == 0) { return 1; }
        int count = 0;
        int cur(num);
        while (cur > 0) {
            cur /= 10;
            count++;
        }
        return count;
    }

    static int pow10(int e) {
        if (e == 1) {
            return 10;
        }
        else if (e == 2) {
            return 100;
        }
        else if (e == 3) {
            return 1000;
        }
        else if (e == 4) {
            return 10000;
        }
        else if (e == 5) {
            return 100000;
        }
        throw exception();
    }

    static bool divisible2(const vector<int>& nums, int k) {
        int cur = 0;
        for (auto&& num : nums) {
            const auto cols = get_columns(num);
            cur = cur * pow10(cols) + num;
            cur %= k;
        }
        return cur == 0;
    }
    static vector<int> tle2(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        do {
            if (divisible2(nums, k)) {
                return nums;
            }
        } while (next_permutation(begin(nums), end(nums)));

        return vector<int>{};
    }
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        const auto n = size(nums);
        const auto bitmask_max = (1 >> n);
        vector<vector<int>> dp(bitmask_max, vector<int>(k, -1));

    }
}; 

void test(vector<int>&& nums, int k) {
    output(Solution().concatenatedDivisibility(nums, k));
}

static void run() {
    test(get_list_int("[3,12,45]"), 5);
    test(get_list_int("[10,5]"), 10);
    test(get_list_int("[1,2,3]"), 5);
}
}
namespace problem4 {
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> indexes(n);
        for (int i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](int a, int b) { return nums[a] < nums[b]; });
        set<int> walls;
        for (int i = 0; i < n - 1; i++) {
            if (nums[indexes[i + 1]] - nums[indexes[i]] > maxDiff) {
                walls.insert(i);
            }
        }

        throw exception();
    }
};
void test(int n, vector<int>&& nums, int maxDiff, vector<vector<int>>&& queries) {

}
static void run() {
    test(5, get_list_int("[1,8,3,4,2]"), 3, get_matrix_int("[[0,3],[2,4]]"));
    test(5, get_list_int("[5,3,1,9,10]"), 2, get_matrix_int("[[0,1],[0,2],[2,3],[4,3]]"));
    test(3, get_list_int("[3,6,1]"), 1, get_matrix_int("[[0,0],[0,1],[1,2]]"));
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}