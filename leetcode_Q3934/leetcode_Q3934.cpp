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
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include <bitset>
#include <optional>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

namespace problem1 {

class Solution {
public:
    template <typename T = long long>
    static T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
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

    static vector<long long> init_powers(int N, long long b, long long modulo) {
        vector<long long> powers(N + 1);
        powers[0] = 1;
        for (int i = 0; i < N; i++) {
            powers[i + 1] = (powers[i] * b) % modulo;
        }
        return powers;
    }

    static vector<long long> rolling_hash(const vector<int>& source, long long b, long long modulo) {
        const auto N = size(source);
        vector<long long> hash(N + 1);
        for (int i = 0; i < N; i++) {
            hash[i + 1] = (hash[i] * b + static_cast<long long>(source[i])) % modulo;
        }
        return hash;
    }
    static long long get_hash(const vector<long long>& rolling_hash, const vector<long long>& powers, long long modulo, int l, int r) {
        auto hash_value = rolling_hash[r] - (rolling_hash[l] * powers[r - l] % modulo);
        if (hash_value < 0) { hash_value += modulo; }
        return hash_value;
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        const auto n = size(nums);
        constexpr long long BASE1 = 1007;
        constexpr long long MODULO1 = 1e9 + 7;
        constexpr long long BASE2 = 2009;
        constexpr long long MODULO2 = 1e9 + 9;

        const vector<long long> pows1 = init_powers(n, BASE1, MODULO1);
        const vector<long long> hash1 = rolling_hash(nums, BASE1, MODULO1);
        const vector<long long> pows2 = init_powers(n, BASE2, MODULO2);
        const vector<long long> hash2 = rolling_hash(nums, BASE2, MODULO2);

        auto check = [&](long long len)->bool {
            map<pair<long long, long long>, size_t> hash_col_map;
            for (size_t i = 0; i + len <= n; i++) {
                auto h1 = get_hash(hash1, pows1, MODULO1, i, i + len);
                auto h2 = get_hash(hash2, pows2, MODULO2, i, i + len);
                hash_col_map[{h1, h2}]++;
            }
            return any_of(
                cbegin(hash_col_map),
                cend(hash_col_map),
                [](auto& a) { return a.second == 1; }
            );
            };
        long long ok = static_cast<long long>(n);
        long long ng = 0;
        const auto ans = binary_search_meguru<long long>(ok, ng, check);
        return ans;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().smallestUniqueSubarray(nums) << endl;
}
static void run() {
    test(get_list_int("[3,3,3]"));
    test(get_list_int("[2,1,2,3,3]"));
    test(get_list_int("[1,1,2,2,1]"));
}
}

int main() {
	problem1::run();
	return 0;
}
