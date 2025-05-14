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

    static int invalid(string s, int t) {
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



    int lengthAfterTransformations(string s, int t) {
        vector<long long> counts(26, 0);
        for (auto&& c : s) {
            counts[c - 'a']++;
        }

        for (int i = 0; i < t; i++) {
            long long nexta = counts[25];
            long long nextb = counts[25];
            for (int j = 24; j >= 0; j--) {
                counts[j + 1] = counts[j];
            }
            counts[0] = nexta;
            counts[1] += nextb;
            counts[1] %= MODULO;
        }
        long long ans = 0;
        for (auto&& count : counts) {
            ans += count;
            ans %= MODULO;
        }
        return ans;
    }
};
void test(string&& s, int t) {
    cout << Solution().lengthAfterTransformations(s, t) << endl;
}
void run() {
    //test("z", 26 + 1);

    test("abcyy", 2);
    test("azbk", 2);
    test("jqktcurgdvlibczdsvnsg", 7517);
}
}
namespace problem3 {
 

void run() {
}
}
namespace problem4 {
constexpr long long MODULO = 1e9 + 7;

using MATRIX = vector<vector<long long>>;

MATRIX operator * (const MATRIX& a, const MATRIX& b) {
    const auto n1 = size(a);
    const auto m1 = size(a.front());
    const auto n2 = size(b);
    const auto m2 = size(b.front());
    if (m1 != n2) { throw exception(); }
    MATRIX res(n1, vector<long long>(m2));
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            long long v = 0;
            for (int k = 0; k < m1; k++) {
                v += a[i][k] * b[k][j];
                v %= MODULO;
            }
            res[i][j] = v;
        }
    }
    return res;
}

MATRIX mat_pow(const MATRIX& a, int exp) {
    if (exp == 0) {
        MATRIX unit(size(a), vector<long long>(size(a.front())));
        for (int i = 0; i < size(a); i++) {
            unit[i][i] = 1;
        }
        return unit;
    }
    if (exp % 2 == 1) {
        return mat_pow(a * a, exp / 2) * a;
    }
    return mat_pow(a * a, exp / 2);
}


class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        MATRIX freqs(26, vector<long long>(1));
        for (auto&& c : s) {
            freqs[c - 'a'][0]++;
        }
        MATRIX m(26, vector<long long>(26));
        for (int i = 0; i < 26; i++) {
            for (int j = 1; j <= nums[i]; j++) {
                m[(i + j) % 26][i] += 1;
            }
        }

        const auto mr = mat_pow(m, t);
        const auto mat_res = mr * freqs;


        long long ans = 0;
        for (int i = 0; i < 26; i++) {
            ans += mat_res[i][0];
            ans %= MODULO;
        }
        return ans;
    }
};
static void test(string s, int t, vector<int>&& nums) {
    cout << Solution().lengthAfterTransformations(s, t, nums) << endl;
}
void run() {
    //problem4::MATRIX m1{ {1,2,3},{4,5,6},{7,8,9} };
    //problem4::MATRIX m2{ {1,4},{2,5},{3,6} };
    MATRIX m1{ {0,1,0},{0,0,1},{1,0,0} };

    const auto r = m1 * m1;
    output_matrix<long long>(r);
    const auto r2 = mat_pow(m1, 2);
    output_matrix<long long>(r2);


    test("azbk", 1, get_list_int("[2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]"));
    test("abcyy", 2, get_list_int("[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]"));
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