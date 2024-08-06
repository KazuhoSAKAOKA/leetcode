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
class neighborSum {
private:
    const vector<vector<int>> grid_;
    unordered_map<int, pair<int, int>> reverse_map_;
public:
    neighborSum(vector<vector<int>>& grid):grid_(grid){
        for (int i = 0; i < size(grid); i++) {
            for (int j = 0; j < size(grid.front()); j++) {
                reverse_map_[grid[i][j]] = { i,j };
            }
        }
    }

    bool in_range(int y, int x) const {
        if (y < 0 || size(grid_) <= y || x < 0 || size(grid_.front()) <= x) {
            return false;
        }
        return true;
    }

    int get_value(int y, int x) const {
        if (in_range(y, x)) {
            return 0;
        }
        return grid_[y][x];
    }

    int adjacentSum(int value) {
        const auto& [y, x] = reverse_map_[value];
        int sum = 0;
        sum += get_value(y - 1, x);
        sum += get_value(y + 1, x);
        sum += get_value(y, x - 1);
        sum += get_value(y, x + 1);
        return sum;
    }

    int diagonalSum(int value) {
        const auto& [y, x] = reverse_map_[value];
        int sum = 0;
        sum += get_value(y - 1, x - 1);
        sum += get_value(y - 1, x + 1);
        sum += get_value(y + 1, x - 1);
        sum += get_value(y + 1, x + 1);
        return sum;
    }
};

void test(vector<string>&& grid, vector<vector<int>>&& values) {

}

void run() {
    test(get_list_str(R"(["neighborSum", "adjacentSum", "adjacentSum", "diagonalSum", "diagonalSum"])"), get_matrix_int(""));
    test(get_list_str(R"(["neighborSum", "adjacentSum", "diagonalSum"])"), get_matrix_int(""));

}
}
namespace problem2 {
class Solution {
public:

    static int djikstra(const vector<vector<int>>& graph, int s, int e) {
        std::vector<int> costs(graph.size(), std::numeric_limits<int>::max());
        struct point {
            int cost;
            int pos;
            bool operator > (const point& other) const {
                return cost > other.cost;
            }
        };
        std::priority_queue<point, vector<point>, greater<point>> p_queue;
        p_queue.push(point{ 0, s });
        costs[s] = 0;
        while (!p_queue.empty()) {
            const auto [current_cost, current] = p_queue.top();
            p_queue.pop();
            if (costs[current] < current_cost) { continue; }
            for (auto&& to : graph[current]) {
                if (costs[to] > 1 + current_cost) {
                    costs[to] = 1 + current_cost;
                    p_queue.push(point{ costs[to] , to });
                }
            }
        }
        return costs[e];
    }


    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> graph(n);
        for (int i = 0; i < n - 1; i++) {
            graph[i].push_back(i + 1);
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for (auto&& query : queries) {
            graph[query[0]].push_back(query[1]);
            ans.push_back(djikstra(graph, 0, n - 1));
        }
        return ans;
    }
};
void test(int n, vector<vector<int>>&& queries) {
    const auto ans = Solution().shortestDistanceAfterQueries(n, queries);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test(14, get_matrix_int("[[0,6],[4,12]]"));
    test(5, get_matrix_int("[[2,4],[0,2],[0,4]]"));
    test(4, get_matrix_int("[[0,3],[0,2]]"));
}
}
namespace problem3 {
class Solution {
public:

    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        set<int> nodes;
        for (int i = 0; i < n; i++) {
            nodes.insert(i);
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for (auto&& query : queries) {
            auto it_begin = nodes.upper_bound(query[0]);
            auto it_end = nodes.lower_bound(query[1]);
            nodes.erase(it_begin, it_end);
            ans.push_back(size(nodes) - 1);
        }
        return ans;
    }
};
void test(int n, vector<vector<int>>&& queries) {
    const auto ans = Solution().shortestDistanceAfterQueries(n, queries);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test(14, get_matrix_int("[[0,6],[4,12]]"));
    test(5, get_matrix_int("[[2,4],[0,2],[0,4]]"));
    test(4, get_matrix_int("[[0,3],[0,2]]"));
}

}
namespace problem4 {
class Solution {
public:

    template <typename T>
    struct segment_tree {
        T inf_;
        std::vector<std::vector<T>> data_;
        using QUERY = std::function<T(const T&, const T&)>;
        QUERY query_;

        segment_tree(size_t n, QUERY query, T inf) :query_(query), inf_(inf) {
            allocate_buffer(n);
        }
        template<typename Container>
        segment_tree(Container& source, QUERY query, T inf) : query_(query), inf_(inf) {
            const size_t n = source.size();
            allocate_buffer(n);
            build(cbegin(source), cend(source));
        }

        void allocate_buffer(size_t n) {
            size_t count = 1;
            for (;;) {
                data_.emplace_back(std::vector<T>(count, inf_));
                if (n <= count) {
                    break;
                }
                count *= 2;
            }
        }

        template<typename IT>
        void build(IT begin, IT end) {
            size_t index = 0;
            for (auto it = begin; it != end; ++it) {
                data_[data_.size() - 1][index++] = *it;
            }
            for (size_t depth_index = data_.size() - 1; depth_index > 0; depth_index--) {
                const auto& source = data_[depth_index];
                auto& destination = data_[depth_index - 1];
                for (size_t i = 0; i < destination.size(); i++) {
                    destination[i] = query_(source[i * 2], source[i * 2 + 1]);
                }
            }
        }

        void update(size_t index, T value) {
            data_[data_.size() - 1][index] += value;
            for (size_t depth_index = data_.size() - 1; depth_index > 0; --depth_index) {
                index /= 2;
                data_[depth_index - 1][index] = query_(data_[depth_index][index * 2], data_[depth_index][index * 2 + 1]);
            }
        }

        T query(size_t a, size_t b) {
            return query(a, b, 0, 0, 0, data_.back().size());
        }

        T query(size_t a, size_t b, size_t depth_index, size_t index, size_t l, size_t r) {
            if (r <= a || b <= l) {
                return inf_;
            }
            if (a <= l && r <= b) {
                return data_[depth_index][index];
            }
            const auto left = query(a, b, depth_index + 1, index * 2, l, (l + r) / 2);
            const auto right = query(a, b, depth_index + 1, index * 2 + 1, (l + r) / 2, r);
            return query_(left, right);
        }


    };

    using segment_tree_int = segment_tree<int>;
    static int sum(const int& a, const int b) { return a + b; }
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        const auto n = size(colors);

        segment_tree_int seg_tree_count(size(colors), sum, 0);
        segment_tree_int seg_tree_sum(size(colors), sum, 0);
        map<int, int> group_map;
        int streak = 1;
        int before = colors[0];
        int begin = 0;
        for (int i = 1; i < n; i++) {
            if (before == colors[i]) {
                if (streak > 1) {
                    seg_tree_count.update(streak, 1);
                    seg_tree_sum.update(streak, streak);

                    group_map[begin] = streak;
                }
                streak = 1;
                begin = i;
            }
            else {
                streak++;
            }
            before = colors[i];
        }
        if (streak > 1) {
            seg_tree_count.update(streak, 1);
            seg_tree_sum.update(streak, streak);
            group_map[begin] = streak;
        }
        
        vector<int> ans;

        for (auto&& query : queries) {
            if (query[0] == 1) {
                const auto len = query[1];
                if (len == 1) {
                    ans.push_back(static_cast<int>(n));
                }
                else {
                    const auto sum_count = seg_tree_count.query(len, n);
                    const auto sum_sum = seg_tree_sum.query(len, n);
                    auto current = sum_sum - (len - 1) * sum_count;
                    if (colors[0] != colors[n - 1]) {
                        int streak = 1;
                        const int base = n - len + 1;
                        int before = colors[base];
                        for (int i = 1; i < len; i++) {
                            int index = (base + i) % n;
                            if (before == colors[index]) {
                                break;
                            }
                            streak++;
                            if (streak >= len) {
                                current++;
                            }
                        }
                    }
                    ans.push_back(static_cast<int>(current));
                }
            }
            else {
                const auto index = query[1];
                const auto value = query[2];
                if (colors[index] == value) { continue; }
                colors[index] = value;
                const auto upper_it = group_map.upper_bound(index);
                if (upper_it == cend(group_map)) {

                }

            }
        }


        return ans;
    }
};

void test(vector<int>&& colors, vector<vector<int>>&& queries) {
    const auto ans = Solution().numberOfAlternatingGroups(colors, queries);
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << endl;
}
void run() {
    test(get_list_int("[0,0,1,1,0,0,0,1,0,0,1,0,0,0,1,0,1,1,1,0,1,0,0,0]"), get_matrix_int("[[1,2]]"));


    test(get_list_int("[0,0,0,1]"), get_matrix_int("[[2,1,1],[1,3],[2,1,1],[2,0,1]]"));
    test(get_list_int("[0,1,1,0,1]"), get_matrix_int("[[2,1,0],[1,4]]"));
    test(get_list_int("[0,0,1,0,1,1]"), get_matrix_int("[[1,3],[2,3,0],[1,5]]"));
}
}

int main()
{
	//problem1::run();
	//problem2::run();
	//problem3::run();
	problem4::run();
	return 0;
}