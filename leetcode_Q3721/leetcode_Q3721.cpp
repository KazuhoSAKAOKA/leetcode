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
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

template<typename T, typename Q>
class segment_tree {
    size_t n;
    vector<T> data;
    Q query;
public:
    segment_tree(size_t n, const T& identity, Q query)
		: n(n), data(2 * n, identity), query(query) {
	}
    void update(size_t index, const T& value) {
        index += n;
        data[index] = value;
        while (index > 1) {
            index /= 2;
            data[index] = query(data[2 * index], data[2 * index + 1]);
        }
    }
    T range_query(size_t left, size_t right) {
        T res_left = data[0];  // identity element
        T res_right = data[0]; // identity element
        left += n;
        right += n;
        while (left < right) {
            if (left & 1) {
                res_left = query(res_left, data[left]);
                left++;
            }
            if (right & 1) {
                right--;
                res_right = query(data[right], res_right);
            }
            left /= 2;
            right /= 2;
        }
        return query(res_left, res_right);
	}
};


template<typename T, typename Q>
class lazy_segment_tree {
    size_t n;
    vector<T> data;
    vector<T> lazy;
    Q query;

public:
	lazy_segment_tree(size_t n, const T& identity, Q query) :n(n), data(2 * n, identity), lazy(2 * n, identity), query(query) {
    }
    void apply(size_t index, const T& value) {
        data[index] = query(data[index], value);
        if (index < n) {
            lazy[index] = query(lazy[index], value);
        }
    }
    void push(size_t index) {
        apply(2 * index, lazy[index]);
        apply(2 * index + 1, lazy[index]);
        lazy[index] = T(); // reset to identity
    }
    void update(size_t left, size_t right, const T& value) {
        left += n;
        right += n;
        size_t l0 = left, r0 = right;
        while (left < right) {
            if (left & 1) {
                apply(left, value);
                left++;
            }
            if (right & 1) {
                right--;
                apply(right, value);
            }
            left /= 2;
            right /= 2;
        }
    }
    T range_query(size_t left, size_t right) {
        left += n;
        right += n;
        for (size_t i = __builtin_clz(n); i > 0; --i) {
            if (((left >> i) << i) != left) push(left >> i);
            if (((right >> i) << i) != right) push((right - 1) >> i);
        }
        T res_left = data[0];  // identity element
        T res_right = data[0]; // identity element
        while (left < right) {
            if (left & 1) {
                res_left = query(res_left, data[left]);
                left++;
            }
            if (right & 1) {
                right--;
                res_right = query(data[right], res_right);
            }
            left /= 2;
            right /= 2;
        }
        return query(res_left, res_right);
	}

};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().longestBalanced(nums) << endl;
}

int main()
{
    test(get_list_int("[2,5,4,3]"));
    test(get_list_int("[3,2,2,5,4]"));
    test(get_list_int("[1,2,3,2]"));
    return 0;
}