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
    vector<int> get_digits(int n) {
        if (n == 0) { return { 0 }; }
        vector<int> digits;
        while (n > 0) {
            digits.emplace_back(n % 10);
            n /= 10;
        }
        return digits;
    }
    bool checkDivisibility(int n) {
        const auto digits = get_digits(n);

        return n % (
            accumulate(cbegin(digits), cend(digits), 0, [](int a, int b) { return a + b; }) +
            accumulate(cbegin(digits), cend(digits), 1, [](int a, int b) { return a * b; })) == 0;
    }
};

static void test(int n) {
    cout << Solution().checkDivisibility(n) << endl;
}
static void run() {
    test(99);
    test(23);
}
}
namespace problem2 {

class Solution {
public:

    static int tle(const vector<vector<int>>& points) {
        constexpr long long MODULO = 1e9 + 7;
        map<int, set<long long>> y_axis_map;
        for (auto&& point : points) {
            const auto x = point[0];
            const auto y = point[1];
            y_axis_map[y].insert(x);
        }
        long long max_combs = 2;
        for (auto it1 = begin(y_axis_map); it1 != end(y_axis_map);) {
            if (size(it1->second) < 2) {
                it1 = y_axis_map.erase(it1);
            }
            else {
                max_combs = max(max_combs, static_cast<long long>(size(it1->second)));
                ++it1;
            }
        }
        vector<long long> C(max_combs + 1);
        constexpr long long inv2 = (MODULO + 1) / 2;
        for (int i = 0; i <= max_combs; ++i) {
            C[i] = 1LL * i * (i - 1) % MODULO * inv2 % MODULO;
        }

        long long count = 0;
        for (auto it1 = cbegin(y_axis_map); it1 != cend(y_axis_map); ++it1) {
            const auto& x_set_bottom = it1->second;
            const long long bottom_count = static_cast<long long>(size(x_set_bottom));
            for (auto it2 = next(it1); it2 != cend(y_axis_map); ++it2) {
                const auto& x_set_top = it2->second;
                const long long top_count = static_cast<long long>(size(x_set_top));
                count += C[bottom_count] * C[top_count];
                count %= MODULO;
            }
        }
        return static_cast<int>(count % MODULO);
    }

    int countTrapezoids(vector<vector<int>>& points) {
        constexpr long long MODULO = 1e9 + 7;
        unordered_map<int, long long> y_axis_map;
        long long max_combs = 2;
        for (auto&& point : points) {
            const auto x = point[0];
            const auto y = point[1];
            y_axis_map[y]++;
            max_combs = max(max_combs, y_axis_map[y]);
        }

        vector<long long> C(max_combs + 1);
        constexpr long long inv2 = (MODULO + 1) / 2;
        for (int i = 0; i <= max_combs; ++i) {
            C[i] = 1LL * i * (i - 1) % MODULO * inv2 % MODULO;
        }

        long long total_comb = 0;
        for (auto it1 = begin(y_axis_map); it1 != end(y_axis_map);++it1) {
            if (it1->second >= 2) {
                total_comb += C[it1->second];
                total_comb %= MODULO;
            }
        }
        long long count = 0;
        for (auto it1 = cbegin(y_axis_map); it1 != cend(y_axis_map); ++it1) {
            if (it1->second >= 2) {
                const long long cur_comb = C[it1->second];
                total_comb -= cur_comb;
                if (total_comb <= 0) {
                    total_comb += MODULO;
                }
                count += cur_comb * total_comb;
                count %= MODULO;
            }
        }
        return static_cast<int>(count % MODULO);
    }
};
static void test(vector<vector<int>>&& points) {
    cout << Solution().countTrapezoids(points) << endl;
}
static void run() {
    test(get_matrix_int("[[-73,-72],[-1,-56],[-92,30],[-57,-89],[-19,-89],[-35,30],[64,-72]]"));
    test(get_matrix_int("[[1,0],[2,0],[3,0],[2,2],[3,2]]"));
    test(get_matrix_int("[[0,0],[1,0],[0,1],[2,1]]"));
}
}
namespace problem3 {

class Solution {
public:
    template <typename T>
    static int popcount_kernighan(T x) {
        int count = 0;
        while (x) {
            x &= (x - 1);
            count++;
        }
        return count;
    }

    static int P(long long x, long long n) {
        if (n == 0) {
            return x;
        }
        return popcount_kernighan(P(x, n - 1));
    }

    static int popcount_depth(long long x) {
        long long current = x;
        int count = 0;
        while (current != 1) {
            current = static_cast<long long>(popcount_kernighan(current));
            count++;
        }
        return count;
    }
    static vector<int> naive(vector<long long>& nums, vector<vector<long long>>& queries) {
        vector<int> ans;

        for (auto&& query : queries) {
            if (query[0] == 1) {
                const auto l = query[1];
                const auto r = query[2];
                const auto k = query[3];
                int count = 0;
                for (int i = l; i <= r; i++) {
                    if (popcount_depth(nums[i]) == k) {
                        count++;
                    }
                }
                ans.emplace_back(count);
            }
            else if (query[0] == 2) {
                nums[query[1]] = query[2];
            }
        }
        return ans;
    }


    template<typename T>
    class binary_indexed_tree {
        int n;
        std::vector<T> data;

    public:
        binary_indexed_tree(int size) : n(size), data(size + 1, 0) {}

        // i番目にxを加算（0-indexed）
        void add(int i, T x) {
            ++i; // 1-indexedに変換
            while (i <= n) {
                data[i] += x;
                i += i & -i;
            }
        }

        // [0, i) の累積和（0-indexed）
        T sum(int i) const {
            T res = 0;
            while (i > 0) {
                res += data[i];
                i -= i & -i;
            }
            return res;
        }

        // [l, r) の累積和（0-indexed）
        T sum(int l, int r) const {
            return sum(r) - sum(l);
        }
    };

    using fenwick_tree = binary_indexed_tree<long long>;
    static int popcount_depth(long long x, vector<int>& memo) {
        if (memo[x] >= 0) {
            return memo[x];
        }
        const int v = popcount_depth(static_cast<int>(popcount_kernighan(x)), memo) + 1;
        memo[x] = v;
        return v;
    }

    vector<int> popcountDepth(vector<long long>& nums, vector<vector<long long>>& queries) {
        const auto n = size(nums);
        vector<int> memo(65, -1);
        memo[1] = 0;
        for (long long i = 1; i <= 64; i++) {
            memo[i] = popcount_depth(i, memo);
        }
        vector<fenwick_tree> fenwick_trees(6, fenwick_tree(n));

        auto get_ppcnt = [&](long long v)->int {
            if (v < 64) {
                return memo[v];
            }
            const auto p1 = popcount_kernighan<long long>(v);
            return memo[p1] + 1;
            };

        for (int i = 0; i < n; i++) {
            const auto pd = get_ppcnt(nums[i]);
            if (pd < 6) {
                fenwick_trees[pd].add(i, 1LL);
            }
        }
        vector<int> ans;

        for (auto&& query : queries) {
            if (query[0] == 1) {
                const auto l = query[1];
                const auto r = query[2];
                const auto k = query[3];

                const auto count = fenwick_trees[k].sum(l, r + 1);
                ans.emplace_back(count);
            }
            else if (query[0] == 2) {
                const auto index = query[1];
                const auto val = query[2];
                const auto old_val = nums[index];
                const auto pd_old = get_ppcnt(old_val);
                if (pd_old < 6) {
                    fenwick_trees[pd_old].add(index, -1LL);
                }
                nums[index] = val;
                const auto pd = get_ppcnt(val);
                if (pd < 6) {
                    fenwick_trees[pd].add(index, 1LL);
                }
            }
        }
        return ans;
    }
};
static void test(vector<long long>&& nums, vector<vector<long long>>&& queries) {
    output(Solution().popcountDepth(nums, queries));
}
static void run() {
    test(get_list_ll("[2,4]"), get_matrix_ll("[[1,0,1,1],[2,1,1],[1,0,1,0]]"));
    test(get_list_ll("[3,5,6]"), get_matrix_ll("[[1,0,2,2],[2,1,4],[1,1,2,1],[1,0,1,0]]"));
    test(get_list_ll("[1,2]"), get_matrix_ll("[[1,0,1,1],[2,0,3],[1,0,0,1],[1,0,0,2]]"));
}
}
namespace problem4 {

static void test_out(const string& msg, vector<int>&& vals) {
    cout << msg << ":";
    sort(begin(vals), end(vals));
    for (auto&& val : vals) {
        cout << val << ",";
    }
    cout << endl;
}

using Point = pair<int, int>;
Point vec(const Point& a, const Point& b) {
    return { b.first - a.first, b.second - a.second };
}
double cross(const Point& a, const Point& b, const Point& c) {
    // ベクトル ab × ac の外積
    int x1 = b.first - a.first, y1 = b.second - a.second;
    int x2 = c.first - a.first, y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

bool is_convex_quad(const vector<Point>& p) {
    // 4点が凸な順序で並んでいるか
    double c1 = cross(p[0], p[1], p[2]);
    double c2 = cross(p[1], p[2], p[3]);
    double c3 = cross(p[2], p[3], p[0]);
    double c4 = cross(p[3], p[0], p[1]);

    return (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0) ||
        (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0);
}

double quad_area(const vector<Point>& p) {
    // 四角形の面積（2つの三角形に分割）
    double a1 = abs(cross(p[0], p[1], p[2])) / 2.0;
    double a2 = abs(cross(p[0], p[2], p[3])) / 2.0;
    return a1 + a2;
}
bool is_parallel(const Point& v1, const Point& v2) {
    return v1.first * v2.second == v1.second * v2.first;
}

bool is_trapezoid(const vector<Point>& p) {
    if (!is_convex_quad(p)) return false;
    if (quad_area(p) == 0) return false;


    Point AB = vec(p[0], p[1]);
    Point CD = vec(p[2], p[3]);
    Point BC = vec(p[1], p[2]);
    Point DA = vec(p[3], p[0]);

    return is_parallel(AB, CD) || is_parallel(BC, DA);
}

bool is_parallelogram(const vector<Point>& p) {
    if (!is_convex_quad(p)) return false;
    if (quad_area(p) == 0) return false;
    Point AB = vec(p[0], p[1]);
    Point CD = vec(p[2], p[3]);
    Point BC = vec(p[1], p[2]);
    Point DA = vec(p[3], p[0]);

    return is_parallel(AB, CD) && is_parallel(BC, DA);
}

bool check_trapezoid(const Point& A, const Point& B, const Point& C, const Point& D) {
    vector<Point> pts = { A, B, C, D };
    do {
        if (is_trapezoid(pts)) return true;
    } while (next_permutation(pts.begin(), pts.end()));
    return false;
}

bool check_parallelogram(const Point& A, const Point& B, const Point& C, const Point& D) {
    vector<Point> pts = { A, B, C, D };
    do {
        if (is_parallelogram(pts)) return true;
    } while (next_permutation(pts.begin(), pts.end()));
    return false;
}
namespace ref {
    using POINT = pair<int, int>;
    using SLOPE = pair<int, int>;
    struct SLOPE_POINT {
        SLOPE slope;
        POINT p;
    };
    constexpr SLOPE INF = { INT_MAX,INT_MAX };
    static bool operator < (const SLOPE_POINT& a, const SLOPE_POINT& b) {
        if (a.slope == INF) {
            return a.p.first < b.p.first;
        }
        if (a.slope.first == 0) {
            return a.p.second < b.p.second;
        }
        return (a.p.second - b.p.second) * a.slope.second < (a.p.first - b.p.first) * a.slope.first;
    }

    class Solution {
    public:
        template <typename T>
        static
            T gcd(const T& a, const T& b) {
            if (b == 0) { return a; }
            return gcd(b, a % b);
        }

        int countTrapezoids(vector<vector<int>>& points) {
            constexpr SLOPE INF = { INT_MAX,INT_MAX };
            auto get_slope = [&](const vector<int>& p1, const vector<int>& p2)->SLOPE {
                if (p1[0] == p2[0]) {
                    return INF;
                }
                int numerator;
                int denominator;
                if (p1[0] < p2[0]) {
                    numerator = p2[1] - p1[1];
                    denominator = p2[0] - p1[0];
                }
                else {
                    numerator = p1[1] - p2[1];
                    denominator = p1[0] - p2[0];
                }
                const auto d = gcd(numerator, denominator);
                return SLOPE{ numerator / d, denominator / d };
                };


            map<SLOPE, map<SLOPE_POINT, vector<pair<int, int>>>> slope_map;
            const auto n = size(points);
            long long max_combs = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    const SLOPE s = get_slope(points[i], points[j]);
                    auto it = slope_map.find(s);
                    SLOPE_POINT sp{ s, POINT{points[i][0],points[i][1]} };
                    if (it == cend(slope_map)) {
                        slope_map.insert({ s, {{sp, {make_pair(i,j)}}} });
                    }
                    else {
                        it->second[sp].emplace_back(make_pair(i, j));
                    }
                }
            }
            long long total_trapezoids = 0;
            long long parallelograms = 0;

            long long total = 0;
            for (auto&& [s, inner_map] : slope_map) {
                if (size(inner_map) > 1) {
                    for (auto it1 = cbegin(inner_map); it1 != cend(inner_map); ++it1) {
                        for (auto it2 = next(it1); it2 != cend(inner_map); ++it2) {
                            for (auto&& indexes1 : it1->second) {
                                const auto& [ind1a, ind1b] = indexes1;
                                for (auto&& indexes2 : it2->second) {
                                    const auto& [ind2a, ind2b] = indexes2;
                                    const auto s1A = get_slope(points[ind1a], points[ind2a]);
                                    const auto s2A = get_slope(points[ind1b], points[ind2b]);
                                    const auto s1B = get_slope(points[ind1a], points[ind2b]);
                                    const auto s2B = get_slope(points[ind1b], points[ind2a]);
                                    if (s1A == s2A || s1B == s2B) {
                                        total += 1;
                                        parallelograms++;
                                        //cout << "平行四辺形:" << points[ind1a][0] << "," << points[ind1a][1] << "," << points[ind2a][0] << "," << points[ind2a][1] << "," <<
                                        //    points[ind1b][0] << "," << points[ind1b][1] << "," << points[ind2b][0] << "," << points[ind2b][1] << endl;
                                        //cout << "平行四辺形:" << ind1a << "," << ind1b << "," << ind2a << "," << ind2b << endl;
                                        test_out("平行四辺形", { ind1a ,ind1b ,ind2a ,ind2b , });
                                    }
                                    else {
                                        total += 2;
                                        //cout << "台形:(" << points[ind1a][0] << "," << points[ind1a][1] << "),(" << points[ind2a][0] << "," << points[ind2a][1] << "),(" <<
                                        //    points[ind1b][0] << "," << points[ind1b][1] << "),(" << points[ind2b][0] << "," << points[ind2b][1] << ")" << endl;
                                        //cout << "台形:" << ind1a << "," << ind1b << "," << ind2a << "," << ind2b << endl;
                                        test_out("台形", { ind1a ,ind1b ,ind2a ,ind2b , });
                                        total_trapezoids++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            cout << "台形" << total_trapezoids << ":" << "平行四辺形" << parallelograms << endl;
            return static_cast<int>(total / 2);
        }

        static int naive() {

            //auto conv = [](const vector<int>& a)->Point {return { a[0],a[1] };};
            //int dc = 0;
            //int pc = 0;
            //for (int i = 0; i < n; i++) {
            //    const auto A = conv(points[i]);
            //    for (int j = i + 1; j < n; j++) {
            //        const auto B = conv(points[j]);
            //        for (int k = j + 1; k < n; k++) {
            //            const auto C = conv(points[k]);
            //            for (int l = k + 1; l < n; l++) {
            //                const auto D = conv(points[l]);
            //                if (check_trapezoid(A, B, C, D)) {
            //                    //cout << "台形です:" << i << "," << j << "," << k << "," << l << endl;
            //                    test_out("台形", { i ,j ,k,l, });
            //                    dc++;
            //                }
            //                if (check_parallelogram(A, B, C, D)) {
            //                    //cout << "平行四辺形です:" << i << "," << j << "," << k << "," << l << endl;
            //                    test_out("平行四辺形", { i ,j ,k,l, });
            //                    pc++;
            //                }
            //            }
            //        }
            //    }
            //}

            return 0;
        }
    };
}




struct fraction {
    long long numerator;
    long long denominator;
    fraction() : numerator(0), denominator(1) {}
    fraction(long long n, long long d = 1LL) : numerator(n), denominator(d) {
        if (d == 0) { throw exception(); }
        simplification();
    }
    fraction& simplification() {
        const auto gcdv = gcd(numerator, denominator);
        if (gcdv != 1) {
            numerator /= gcdv;
            denominator /= gcdv;
        }
        return *this;
    }
};
static bool operator==(const fraction& a, const fraction& b) {
    return a.numerator == b.numerator && a.denominator == b.denominator;
}
static bool operator == (const fraction& a, const long long& b) {
    if (a.denominator != 1) { return false; }
    return a.numerator == b;
}
static bool operator == (long long& b, const fraction& a) {
    if (a.denominator != 1) { return false; }
    return a.numerator == b;
}
static bool operator < (const fraction& a, const fraction& b) {
    if (a.denominator == b.denominator) {
        return a.numerator < b.numerator;
    }
    else {
        const auto lcmv = lcm(a.denominator, b.denominator);
        return a.numerator * (lcmv / a.denominator) < b.numerator * (lcmv / b.denominator);
    }
}

static fraction operator + (const fraction& a, const fraction& b) {
    if (a.denominator == b.denominator) {
        fraction s(a.numerator + b.numerator, a.denominator);
        s.simplification();
        return s;
    }
    else {
        const auto lcmv = lcm(a.denominator, b.denominator);
        fraction s(a.numerator * (lcmv / a.denominator) + b.numerator * (lcmv / b.denominator), lcmv);
        s.simplification();
        return s;
    }
}
static fraction operator - (const fraction& a, const fraction& b) {
    if (a.denominator == b.denominator) {
        fraction s(a.numerator - b.numerator, a.denominator);
        s.simplification();
        return s;
    }
    else {
        const auto lcmv = lcm(a.denominator, b.denominator);
        fraction s(a.numerator * (lcmv / a.denominator) - b.numerator * (lcmv / b.denominator), lcmv);
        s.simplification();
        return s;
    }
}
static fraction operator * (const fraction& a, const fraction& b) {
    if (a.numerator == 0 || b.numerator == 0) {
        return fraction(0);
    }
    fraction m(a.numerator * b.numerator, a.denominator * b.denominator);
    m.simplification();
    return m;
}
static optional<fraction> operator / (const fraction& a, const fraction& b) {
    if (b.numerator == 0) {
        return nullopt;
    }
    fraction d(a.numerator * b.denominator, a.denominator * b.numerator);
    d.simplification();
    return d;
}

class Solution {
public:
    template <typename T>
    static
        T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }

    int countTrapezoids(vector<vector<int>>& points) {
        const fraction INF = { INT_MAX,1 };
        auto get_slope = [&](const vector<int>& p1, const vector<int>& p2)->fraction {
            if (p1[0] == p2[0]) {
                return INF;
            }
            int numerator;
            int denominator;
            if (p1[0] < p2[0]) {
                numerator = p2[1] - p1[1];
                denominator = p2[0] - p1[0];
            }
            else {
                numerator = p1[1] - p2[1];
                denominator = p1[0] - p2[0];
            }
            const auto d = gcd(abs(numerator), denominator);
            return fraction{ numerator / d, denominator / d };
            };

        auto get_intercept = [&](const fraction& slope, const vector<int>& p)->fraction {
            if (slope == INF) {
                return p[0];
            }
            if (slope.numerator == 0) {
                return p[1];
            }
            return fraction{ p[1] } - fraction{ p[0] } * slope;
            };

        map<fraction, map<fraction, long long>> slope_map;
        map<pair<int, int>, map<fraction, long long>> midpoint_map;

        const auto n = size(points);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                const auto slope = get_slope(points[i], points[j]);
                auto it = slope_map.find(slope);
                const auto intercept = get_intercept(slope, points[i]);
                if (it == cend(slope_map)) {
                    slope_map.insert({ slope, {{intercept, 1LL}} });
                }
                else {
                    auto it2 = it->second.find(intercept);
                    if (it2 == cend(it->second)) {
                        it->second.insert({ intercept, 1LL });
                    }
                    else {
                        it2->second++;
                    }
                }
                const auto midpoint2 = make_pair(points[i][0] + points[j][0], points[i][1] + points[j][1]);
                auto it3 = midpoint_map.find(midpoint2);
                if (it3 == cend(midpoint_map)) {
                    midpoint_map.insert({ midpoint2 , {{slope, 1LL}} });
                }
                else {
                    auto it4 = it3->second.find(slope);
                    if (it4 == cend(it3->second)) {
                        it3->second.insert({ slope, 1LL });
                    }
                    else {
                        it4->second++;
                    }
                }
            }
        }

        long long total_trapezoids = 0;
        for (auto&& [s, inner_map] :  slope_map) {
            if (size(inner_map) > 1) {
                long long cur_total = 0;
                for (auto it1 = cbegin(inner_map); it1 != cend(inner_map); ++it1) {
                    cur_total += it1->second;
                }
                for (auto it1 = cbegin(inner_map); it1 != cend(inner_map); ++it1) {
                    cur_total -= it1->second;
                    total_trapezoids += it1->second * cur_total;
                }
            }
        }
        long long parallelograms = 0;
        for (const auto& [_, inner_map] : midpoint_map) {
            if (size(inner_map) > 1) {
                long long cur_total = 0;
                for (auto it1 = cbegin(inner_map); it1 != cend(inner_map); ++it1) {
                    cur_total += it1->second;
                }
                for (auto it1 = cbegin(inner_map); it1 != cend(inner_map); ++it1) {
                    cur_total -= it1->second;
                    parallelograms += it1->second * cur_total;
                }
            }
        }

        return static_cast<int>(total_trapezoids - parallelograms);
    }
};
static void test(vector<vector<int>>&& points) {
    cout << Solution().countTrapezoids(points) << endl;
    //cout << ref::Solution().countTrapezoids(points) << endl;
}
static void run() {
    test(get_matrix_int("[[-36,-31],[-87,70],[-62,-38],[-99,63],[66,87],[-78,-63],[52,17],[72,-8],[-72,-63],[-5,80],[-47,70],[70,38],[79,70],[-70,45],[52,63],[-48,85],[92,-63],[52,-63]]"));

    //test(get_matrix_int("[[83,-25],[74,11],[-65,-25],[33,-25],[17,-25],[1,30],[-84,-25],[1,-25],[1,-92],[-87,13]]"));
    //test(get_matrix_int("[[0,0],[2,0],[3,1],[-1,1]]"));
    //test(get_matrix_int("[[0,0],[1,0],[0,1],[2,1]]"));
    //test(get_matrix_int("[[-57,-76],[-64,-76],[-64,-82],[-71,-82]]"));
    //test(get_matrix_int("[[-57,-76],[-94,-82],[-78,-18],[-64,-36],[-71,-82],[-47,-69],[-64,-82],[-64,-76]]"));
    //test(get_matrix_int("[[71,-89],[-75,-89],[-9,11],[-24,-89],[-51,-89],[-77,-89],[42,11]]"));
    //test(get_matrix_int("[[-3,2],[3,0],[2,3],[3,2],[2,-3]]"));
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