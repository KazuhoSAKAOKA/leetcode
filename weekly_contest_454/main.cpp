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
#include <cctype>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    string generateTag(string caption) {
        string ans;
        ans.reserve(100);
        ans += "#";
        int index = 0;
        bool lower = true;
        while (index < size(caption) && size(ans) < 100) {
            if (isalpha(caption[index])) {
                if (lower) {
                    ans += tolower(caption[index]);
                }
                else {
                    ans += toupper(caption[index]);
                    lower = true;
                }
            }
            else {
                if (size(ans) != 1) {
                    lower = false;
                }
            }
            index++;
        }
        return ans;
    }
};

void test(string&& caption) {
    cout << Solution().generateTag(caption) << endl;
}
static void run() {
    test("Leetcode daily streak achieved");
    test("can I Go There");
    test("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
}
}
namespace problem2 {
class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        constexpr size_t MODULO = 1e9 + 7;
        const auto n = size(nums);
        unordered_map<int, size_t> right_freq_map;
        for (auto&& num : nums) {
            right_freq_map[num]++;
        }
        unordered_map<int, size_t> left_freq_map;
        size_t count = 0;
        left_freq_map[nums[0]]++;
        right_freq_map[nums[0]]--;
        for (int j = 1; j < n; j++) {
            right_freq_map[nums[j]]--;
            const long long left_count = left_freq_map[nums[j] * 2];
            const long long right_count = right_freq_map[nums[j] * 2];
            count += (left_count * right_count) % MODULO;
            count %= MODULO;
            left_freq_map[nums[j]]++;
        }
        return count;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().specialTriplets(nums) << endl;
}

static void run() {
    test(get_list_int("[6,3,6]"));
    test(get_list_int("[0,1,0,0]"));
    test(get_list_int("[8,4,2,8,4]"));
}
}
namespace problem3 {

class Solution {
public:
    static long long naive(vector<int>& nums, int m) {
        long long max_value = LLONG_MIN;
        for (int i = 0; i < size(nums); i++) {
            for (int j = i + m - 1; j < size(nums); j++) {
                max_value = max(max_value, static_cast<long long>(nums[i]) * static_cast<long long>(nums[j]));
            }
        }
        return max_value;
    }

    template <typename T, typename Q>
    struct segment_tree {
        T inf_;
        std::vector<std::vector<T>> data_;
        Q query_;

        segment_tree(size_t n, Q query, T inf) :query_(query), inf_(inf) {
            allocate_buffer(n);
        }
        template<typename Container>
        segment_tree(Container& source, Q query, T inf) : query_(query), inf_(inf) {
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
            data_[data_.size() - 1][index] = value;
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

    template <typename T = long long>
    struct seqment_tree_range_maximum_query : public segment_tree<T, std::function<T(T, T)>> {
        seqment_tree_range_maximum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
        template <typename Container>
        seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
    };
    template <typename T = long long>
    struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
        seqment_tree_range_minimum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
        template <typename Container>
        seqment_tree_range_minimum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
    };



    long long maximumProduct(vector<int>& nums, int m) {
        const auto n = size(nums);
        seqment_tree_range_maximum_query<long long> seg_max(nums);
        seqment_tree_range_minimum_query<long long> seg_min(nums);

        long long max_value = LLONG_MIN;

        for (int i = 0; i < n - m + 1; i++) {
            const long long cur = nums[i];
            if (cur == 0) {
                max_value = max(max_value, 0LL);
            }
            else if (cur < 0) {
                const long long range_min = seg_min.query(i + m - 1, n);
                max_value = max(max_value, range_min * cur);
            }
            else {
                const long long range_max = seg_max.query(i + m - 1, n);
                max_value = max(max_value, range_max * cur);
            }
        }

        return max_value;
    }
};
void test(vector<int>&& nums, int m) {
    cout << Solution().maximumProduct(nums, m) << endl;
}
static void run() {
    test(get_list_int("[-1,-9,2,3,-2,-3,1]"), 1);
    test(get_list_int("[1,3,-5,5,6,-4]"), 3);
    test(get_list_int("[2,-1,2,-6,5,2,-5,7]"), 2);
}
}
namespace problem4 {
class Solution {
public:
    struct edge_t {
        long long weight;
        int to;
    };
    using GRAPH = vector<vector<edge_t>>;

    template<typename T>
    static vector<T> djikstra(const std::vector<std::vector<edge_t>>& graph, size_t s, size_t e) {
        std::vector<T> costs(graph.size(), std::numeric_limits<T>::max());
        struct point {
            T cost;
            size_t pos;
            bool operator > (const point& other) const {
                return cost > other.cost;
            }
        };
        std::priority_queue<point, std::vector<point>, std::greater<point>> p_queue;
        p_queue.push(point{ 0, s });
        costs[s] = 0;
        while (!p_queue.empty()) {
            const auto [current_cost, current] = p_queue.top();
            p_queue.pop();
            if (costs[current] < current_cost) { continue; }
            for (auto&& [cost, to] : graph[current]) {
                if (costs[to] > cost + current_cost) {
                    costs[to] = cost + current_cost;
                    p_queue.push(point{ costs[to] , to });
                }
            }
        }
        return costs;
    }

    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        GRAPH graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge_t{ edge[2], edge[1]  });
            graph[edge[1]].emplace_back(edge_t{ edge[2], edge[0] });
        }

        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            const auto u = query.front();
            const auto v = query.back();
            if (u == v) {
                ans.emplace_back(u);
                continue;
            }
            const auto costs = djikstra<long long>(graph, u, v);
            const auto total = costs[v];
            long long current_cost = total;
            int current = v;
            while (current_cost * 2 > total) {
                for (auto&& edge : graph[current]) {
                    if (costs[edge.to] + edge.weight == current_cost) {
                        current = edge.to;
                        current_cost = costs[edge.to];
                    }
                }
            }

        }
        return ans;
    }


    /*

    static optional<vector<pair<long long, int>>> dfs(const GRAPH& graph, int current, int target, vector<bool>& visited, vector<pair<long long, int>>& route, long long cost) {
        if (target == current) {
            return route;
        }
        for (auto&& next : graph[current]) {
            if (!visited[next.to]) {
                visited[next.to] = true;
                route.emplace_back(make_pair(cost + next.weight, next.to));
                const auto r = dfs(graph, next.to, target, visited, route, cost + next.weight);
                if (r.has_value()) {
                    return r;
                }
                route.pop_back();
                visited[next.to] = false;
            }
        }
        return nullopt;
    }
    template <typename T = long long>
    T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        GRAPH graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge_t{ edge[1], edge[2] });
            graph[edge[1]].emplace_back(edge_t{ edge[0], edge[2] });
        }

        vector<int> ans;
        ans.reserve(size(queries));
        for (auto&& query : queries) {
            const auto u = query.front();
            const auto v = query.back();
            if (u == v) {
                ans.emplace_back(u);
                continue;
            }
            vector<bool> visited(n);
            vector<pair<long long, int>> route;
            visited[u] = true;
            route.emplace_back(make_pair(0, u));
            const auto result = dfs(graph, u, v, visited, route, 0);
            const auto& res_route = result.value();
            const auto total_cost = res_route.back().first;
            const auto nodex_idx = binary_search_meguru<int>(size(res_route), 0, [&](int idx)->bool {
                return total_cost <= res_route[idx].first * 2;
                });

            ans.emplace_back(res_route[nodex_idx].second);
        }
        return ans;
    }

    */
};
void test(int n, vector<vector<int>>&& edges, vector<vector<int>>&& queries) {
    output(Solution().findMedian(n, edges, queries));
}
static void run() {
    test(2, get_matrix_int("[[0,1,2]]"), get_matrix_int("[[1,1]]"));
    test(2, get_matrix_int("[[0,1,7]]"), get_matrix_int("[[1,0],[0,1]]"));
    test(3, get_matrix_int("[[0,1,2],[2,0,4]]"), get_matrix_int("[[0,1],[2,0],[1,2]]"));
    test(5, get_matrix_int("[[0,1,2],[0,2,5],[1,3,1],[2,4,3]]"), get_matrix_int("[[3,4],[1,2]]"));
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