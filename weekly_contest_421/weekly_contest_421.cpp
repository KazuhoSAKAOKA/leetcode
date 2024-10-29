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

template <typename T>
T gcd(const T& a, const T& b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

template <typename T>
T lcm(const T& a, const T& b) {
    return a / gcd(a, b) * b;
}

long long gcd(const vector<long long>& vec) {
    long long l = vec[0];
    for (int i = 0; i < vec.size() - 1; i++) {
        l = gcd(l, vec[i + 1]);
    }
    return l;
}

long long lcm(const vector<long long>& vec) {
    long long l = vec[0];
    for (int i = 0; i < vec.size() - 1; i++) {
        l = lcm(l, vec[i + 1]);
    }
    return l;
}

namespace problem1 {
class Solution {
public:
    long long maxScore(vector<int>& nums) {
        vector<long long> nums_ll;
        nums_ll.reserve(size(nums));
        transform(cbegin(nums), cend(nums), back_inserter(nums_ll), [](const auto& a) { return static_cast<long long>(a); });
        long long cur_max;
        {
            const long long g = gcd(nums_ll);
            const long long l = lcm(nums_ll);
            cur_max = g * l;
        }

        if (size(nums) > 1) {
            for (size_t i = 0; i < size(nums_ll); i++) {
                vector<long long> nums_ll2(nums_ll);
                nums_ll2.erase(next(begin(nums_ll2),i));
                const long long g = gcd(nums_ll2);
                const long long l = lcm(nums_ll2);
                const auto v = g * l;
                cur_max = max(cur_max, v);
            }
        }
        return cur_max;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().maxScore(nums) << endl;
}
void run() {
    test(get_list_int("[2,4,8,16]"));
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[3]"));
}
}
namespace problem2 {
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:

    static void naived0(const string& a, int t) {
        string temp(a);
        for (int i = 0; i < t; i++) {
            string work;
            for (auto&& c : temp) {
                if (c == 'z') {
                    work += "ab";
                }

                else {
                    work += c + 1;
                }
            }
            swap(temp, work);
            cout << temp << endl;
        }
    }


    static long long rec_calc(int remain_count, char c, map<int, long long>& memo) {
        const auto l = 'z' - c;
        if (remain_count <= l) {
            return 1;
        }
        const auto remain = remain_count - l;
        const auto dived = (remain / 26) + 1;
        const auto it = memo.find(dived);
        if (it != cend(memo)) {
            return it->second;
        }

        if (c == 'z') {
            if (remain_count == 0) {
                return 1;
            }
            long long v1 = rec_calc(remain_count - 1, 'a', memo);
            long long v2 = rec_calc(remain_count - 1, 'b', memo);
            const auto r = (v1 + v2) % MODULO;
            memo[dived] = r;
            return r;
        }
        else{
            const auto r = rec_calc(remain_count - l, 'z', memo);
            return r;
        }
    }

    int lengthAfterTransformations(string s, int t) {
        vector<long long> counts(26, 1);
        map<int, long long> memo;
        auto v = rec_calc(t, 'z', memo);
        for (int i = 0; i < 26; i++) {
            counts[i] = rec_calc(t, static_cast<char>('a' + i), memo);
        }
        long long ans = 0;
        for (auto&& c : s) {
            long long v = counts[c - 'a'];
            ans += v;
            ans %= MODULO;
        }
        naived0(s, t);
        return ans;
    }
};
void test(string&& s, int t) {
    cout << Solution().lengthAfterTransformations(s, t) << endl;
}
void run() {
    test("z", 26 + 1);

    //test("jqktcurgdvlibczdsvnsg", 7517);
    //test("abcyy", 2);
    //test("azbk", 2);
}
}
namespace problem3 {
 

void run() {
}
}
namespace problem4 {

void run() {
}
}

int main()
{
    //problem1::run();
    problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}