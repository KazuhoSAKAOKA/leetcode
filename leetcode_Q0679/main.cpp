#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
template <typename T>
static T gcd(const T& a, const T& b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

template <typename T>
static T lcm(const T& a, const T& b) {
    return a / gcd(a, b) * b;
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
static bool operator == (const fraction& a, const long long& b) {
    if (a.denominator != 1) { return false; }
    return a.numerator == b;
}
static bool operator == (long long& b, const fraction& a) {
    if (a.denominator != 1) { return false; }
    return a.numerator == b;
}

class Solution {
public:

    static vector<fraction> gets(const fraction& a, const fraction& b) {
        vector<fraction> l;
        l.emplace_back(a + b);
        l.emplace_back(a - b);
        l.emplace_back(a * b);
        const auto v = a / b;
        if (v.has_value()) {
            l.emplace_back(v.value());
        }
        return l;
    }

    static bool exist24(const fraction& a, const fraction& b) {
        const auto vals = gets(a, b);
        return any_of(cbegin(vals), cend(vals), [](const auto& v) { return v == 24LL; });
    }

    static bool check(const vector<int>& cards) {
        const fraction a(cards[0]);
        const fraction b(cards[1]);
        const fraction c(cards[2]);
        const fraction d(cards[3]);
        const auto ab = gets(a, b);
        const auto bc = gets(b, c);
        const auto cd = gets(c, d);
        for (auto&& abv : ab) {
            for (auto&& cdv : cd) {
                if (exist24(abv, cdv)) {
                    return true;
                }
            }
            const auto abc = gets(abv, c);
            for (auto&& abcv : abc) {
                if (exist24(abcv, d)) {
                    return true;
                }
            }
        }

        for (auto&& bcv : bc) {
            const auto abc = gets(a, bcv);
            for (auto&& abcv : abc) {
                if (exist24(abcv, d)) {
                    return true;
                }
            }

            const auto bcd = gets(bcv, d);
            for (auto&& bcdv : bcd) {
                if (exist24(a, bcdv)) {
                    return true;
                }
            }
        }
        for (auto&& cdv : cd) {
            const auto bcd = gets(b, cdv);
            for (auto&& bcdv : bcd) {
                if (exist24(a, bcdv)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool judgePoint24(vector<int>& cards) {
        sort(begin(cards), end(cards));
        do {
            if (check(cards)) {
                return true;
            }
        } while (next_permutation(begin(cards), end(cards)));

        return false;
    }
};
static void test(vector<int>&& cards) {
    cout << Solution().judgePoint24(cards) << endl;
}

int main() {
    test(get_list_int("[6,1,3,4]"));
    test(get_list_int("[1,3,4,6]"));
    test(get_list_int("[4,1,8,7]"));
    test(get_list_int("[1,2,1,2]"));
    return 0;
}