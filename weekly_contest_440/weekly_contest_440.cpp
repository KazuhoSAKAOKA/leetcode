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
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int count = 0;
        vector<bool> used(size(baskets));
        auto find_basket = [&](int fruit) {
            for (int i = 0; i < size(baskets); i++) {
                if (!used[i] && fruit <= baskets[i]) {
                    return i;
                }
            }
            return -1;
            };

        for (auto&& fruit : fruits) {
            const auto index = find_basket(fruit);
            if (index >= 0) {
                used[index] = true;
            }
            else {
                count++;
            }
        }

        return count;
    }
};
void test(vector<int>&& fruits, vector<int>&& baskets) {
    cout << Solution().numOfUnplacedFruits(fruits, baskets) << endl;
}

static void run() {
    test(get_list_int("[4,2,5]"), get_list_int("[3,5,4]"));
    test(get_list_int("[3,6,1]"), get_list_int("[6,4,7]"));
}
}
namespace problem2 {
class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        const auto n = size(nums1);

        vector<size_t> num1_order_indexes(n);
        vector<size_t> num2_order_indexes(n);
        for (size_t i = 0; i < n; i++) {
            num1_order_indexes[i] = i;
            num2_order_indexes[i] = i;
        }
        sort(begin(num1_order_indexes), end(num1_order_indexes), [&](const auto& a, const auto& b) { return nums1[a] < nums1[b]; });
        priority_queue<int, vector<int>, greater<int>> q;

        vector<long long> ans(n);
        long long before_ans = 0;
        long long current_sum = 0;

        int current_count = 0;
        q.push(nums2[num1_order_indexes[0]]);
        current_count++;
        current_sum += nums2[num1_order_indexes[0]];
        int before_index = num1_order_indexes[0];

        for (size_t index = 1; index < n; index++) {
            const int i = num1_order_indexes[index];
            if (nums1[i] == nums1[before_index]) {
                ans[i] = before_ans;
            }
            else {
                before_ans = current_sum;
                ans[i] = before_ans;
            }
            q.push(nums2[i]);
            current_count++;
            current_sum += nums2[i];
            if (current_count > k) {
                current_count--;
                current_sum -= q.top();
                q.pop();
            }
            before_index = num1_order_indexes[index];
        }
        return ans;
    }
};
void test(vector<int>&& nums1, vector<int>&& nums2, int k) {
    output(Solution().findMaxSum(nums1, nums2, k));
}

static void run() {
    test(get_list_int("[25,15,1,28,3,13,29,26,1,2,28,5,2,14,19,2,4]"), get_list_int("[25,21,3,23,26,6,30,22,27,21,24,27,15,17,15,16,25]"), 9);
    test(get_list_int("[4,2,1,5,3]"), get_list_int("[10,20,30,40,50]"), 2);
    test(get_list_int("[2,2,2,2]"), get_list_int("[3,1,2,3]"), 1);
}
}
namespace problem3 {
class Solution {
public:

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
    struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
        seqment_tree_range_minimum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
        template <typename Container>
        seqment_tree_range_minimum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
    };

    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        constexpr long long INF = std::numeric_limits<long long>::max();
        map<int, set<int>> basket_value_map;
        for (int i = 0; i < size(baskets); i++) {
            basket_value_map[baskets[i]].insert(i);
        }
        map<int, int> basket_value_to_stindex_map;
        int st_index = 0;
        for (auto&& [k, _] : basket_value_map) {
            basket_value_to_stindex_map.insert({ k, st_index });
            st_index++;
        }
        const auto seg_size = size(basket_value_map);
        seqment_tree_range_minimum_query<long long> st(seg_size);
        for (auto&& [k, indexes] : basket_value_map) {
            const auto index = basket_value_to_stindex_map[k];
            st.update(index, *cbegin(basket_value_map[k]));
        }

        int count = 0;
        for (auto&& fruit : fruits) {
            const auto it = basket_value_to_stindex_map.lower_bound(fruit);
            if (it == cend(basket_value_to_stindex_map)) {
                count++;
            }
            else {
                const auto min_index = st.query(it->second, seg_size + 1);
                if (min_index == INF) {
                    count++;
                }
                else {
                    basket_value_map[baskets[min_index]].erase(min_index);
                    const auto used = basket_value_to_stindex_map[baskets[min_index]];
                    if (basket_value_map[baskets[min_index]].empty()) {
                        st.update(used, INF);
                    }
                    else {
                        st.update(used, *cbegin(basket_value_map[baskets[min_index]]));
                    }
                }
            }
        }
        return count;
    }
};
void test(vector<int>&& fruits, vector<int>&& baskets) {
    cout << Solution().numOfUnplacedFruits(fruits, baskets) << endl;
}

static void run() {
    test(get_list_int("[4,2,5]"), get_list_int("[3,5,4]"));
    test(get_list_int("[3,6,1]"), get_list_int("[6,4,7]"));
}
}
namespace problem4 {
class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        const auto m = size(conflictingPairs);

        long long count = 0;
        vector<int> llist(m, 1);

        for (int r = 1; r <= n; r++) {
            for (int i = 0; i < m; i++) {

            }


        }

        return count;
    }
};
void test(int n, vector<vector<int>>&& conflictingPairs) {
    cout << Solution().maxSubarrays(n, conflictingPairs) << endl;
}
static void run() {
    test(4, get_matrix_int("[[2,3],[1,4]]"));
    test(5, get_matrix_int("[[1,2],[2,5],[3,5]]"));
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