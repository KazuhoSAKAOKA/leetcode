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
#include <bitset>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:

    static bool is_black(int x, int y) {
        return (x + y) % 2 == 0;
    }

    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        int x1 = static_cast<int>(coordinate1[0] - 'a');
        int y1 = static_cast<int>(coordinate1[1] - '1');

        int x2 = static_cast<int>(coordinate2[0] - 'a');
        int y2 = static_cast<int>(coordinate2[1] - '1');
        return is_black(x1, y1) == is_black(x2, y2);
    }
};

void test(string&& coordinate1, string&& coordinate2) {
    cout << Solution().checkTwoChessboards(coordinate1, coordinate2) << endl;
}
void run() {
    test("a1", "c3");
    test("a1", "h3");
}
}
namespace problem2 {
class Solution {
public:
    void add_heap(vector<int>& heap, size_t heap_size, int value) {
        heap[heap_size] = value;
        auto current = heap_size;

        for(;;){
            if (current == 0) { break; }
            auto parent = (current - 1) / 2;
            if (heap[parent] < heap[current]) {
                break;
            }
            swap(heap[parent], heap[current]);
            current = parent;
        }
    }

    int get_kth(vector<int>& heap, size_t heap_size, int k) {
        if (heap_size < k) {
            return -1;
        }
        return heap[k - 1];
    }

    vector<int> a(vector<vector<int>>& queries, int k) {
        vector<int> heap(size(queries));
        size_t heap_size = 0;

        vector<int> ans;
        ans.reserve(size(queries));
        for (size_t i = 0; i < size(queries); i++) {
            add_heap(heap, i, abs(queries[i][0]) + abs(queries[i][1]));
            ans.emplace_back(get_kth(heap, i + 1, k));
        }
        return ans;
    }

    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        priority_queue<int, vector<int>, std::less<int>> left;
        int kth_value = -1;
        vector<int> ans;
        ans.reserve(size(queries));
        size_t index = 0;
        for (; index < size(queries);index++) {
            const auto dist = abs(queries[index][0]) + abs(queries[index][1]);
            left.push(dist);
            if (size(left) == k) {
                kth_value = left.top();
                ans.emplace_back(kth_value);
                index++;
                break;
            }
            else {
                ans.emplace_back(-1);
            }
        }

        for (; index < size(queries); index++) {
            const auto dist = abs(queries[index][0]) + abs(queries[index][1]);
            if (kth_value < dist) {
                ans.emplace_back(kth_value);
                continue;
            }
            left.push(dist);
            left.pop();
            kth_value = left.top();
            ans.emplace_back(kth_value);
        }
        return ans;
    }
};
void test(vector<vector<int>>&& queries, int k) {
    const auto ans = Solution().resultsArray(queries, k);
    cout << "[";
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << "]" << endl;;
}
void run() {
    test(get_matrix_int("[[1,2],[3,4],[2,3],[-3,0]]"), 2);
    test(get_matrix_int("[[5,5],[4,4],[3,3]]"), 1);
}
}
namespace problem3 {
class Solution {
public:

    struct memo_key_t {
        size_t index;
        unsigned long long low;
        unsigned long long high;
        bool operator<(const memo_key_t& other) const {
            if (index != other.index) {
                return index < other.index;
            }
            if (low != other.low) {
                return low < other.low;
            }
            return high < other.high;
        }
        bool operator==(const memo_key_t& other) const {
            return index == other.index && low == other.low && high == other.high;
        }

    };

    template<class T>
    static inline size_t combine_hash(const size_t seed, const T& v) {
        return seed ^ (std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
    }

    struct memo_hasher {
        std::size_t operator()(const memo_key_t& key) const {
            std::size_t seed = key.index;
            seed = combine_hash(seed, key.low);
            seed = combine_hash(seed, key.high);
            return seed;
        }
    };

    using memo_t = unordered_map<memo_key_t, int, memo_hasher>;

    static int rec(const vector<vector<int>>& grid, size_t row_index, bitset<64>& selected_values_low, bitset<64>& selected_values_high, memo_t& memo) {
        if (size(grid) == row_index) {
            return 0;
        }

        const auto key = memo_key_t{ row_index, selected_values_low.to_ullong(), selected_values_high.to_ullong() };
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int max_score = rec(grid, row_index + 1, selected_values_low, selected_values_high, memo);
        for (int i = 0; i < size(grid.front()); i++) {
            const int value = grid[row_index][i];
            if (value < 64) {
                if (!selected_values_low[grid[row_index][i]]) {
                    selected_values_low[grid[row_index][i]] = true;
                    max_score = max(max_score, rec(grid, row_index + 1, selected_values_low, selected_values_high, memo) + grid[row_index][i]);
                    selected_values_low[grid[row_index][i]] = false;
                }
            }
            else {
                const auto temp = value - 64;
                if (!selected_values_high[temp]) {
                    selected_values_high[temp] = true;
                    max_score = max(max_score, rec(grid, row_index + 1, selected_values_low, selected_values_high, memo) + grid[row_index][i]);
                    selected_values_high[temp] = false;
                }
            }
        }
        memo[key] = max_score;
        return max_score;
    }

    static int tle(const vector<vector<int>>& grid) {
        bitset<64> selected_values_low;
        bitset<64> selected_values_high;
        memo_t memo;
        return rec(grid, 0, selected_values_low, selected_values_high, memo);
    }

    int maxScore(vector<vector<int>>& grid) {

        vector<unordered_set<int>> value_rows(101);
        for (int i = 0; i < size(grid); i++) {
            const auto& col = grid[i];
            for (auto&& value : col) {
                value_rows[value].insert(i);
            }
        }
        unordered_map<int, int> before;
        before[0] = 0;
        for (int i = 1; i < 101; i++) {
            unordered_map<int, int> current(before);
            for (auto&& [bits, score] : before) {
                for (auto&& row : value_rows[i]) {
                    const auto bit = 1 << row;
                    if ((bits & bit) == 0) {
                        current[bits | bit] = max(current[bits | bit], before[bits] + i);
                    }
                }
            }
            before = current;
        }

        int max_score = 0;
        for (auto&& [_, score] : before) {
            max_score = max(max_score, score);
        }
        return max_score;
    }
};
void test(vector<vector<int>>&& grid) {
    cout << Solution().maxScore(grid) << endl;
}
void run() {
    test(get_matrix_int("[[5,5],[5,5],[11,5]]"));
    test(get_matrix_int("[[1,2,3],[4,3,2],[1,1,1]]"));
    test(get_matrix_int("[[8,7,6],[8,3,2]]"));
}
}
namespace problem4 {
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
class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {

        return nums;
    }
};
void test(vector<int>&& nums, vector<vector<int>>&& queries) {
    const auto ans = Solution().maximumSubarrayXor(nums, queries);
    cout << "[";
    for (auto&& value : ans) {
        cout << value << ",";
    }
    cout << "]" << endl;
}

void run() {
    test(get_list_int("[2,8,4,32,16,1]"), get_matrix_int("[[0,2],[1,4],[0,5]]"));
    test(get_list_int("[0,7,3,2,8,5,1]"), get_matrix_int("[[0,3],[1,5],[2,4],[2,6],[5,6]]"));
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