#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
using namespace std;


vector<long long> factorial_memo;
class Solution {
public:
    static unsigned long long factorial(int n) {
        return factorial_memo[n];
    }

    static long long get_patterns(int n, const vector<int>& digits) {
        map<int, int> freqs;
        for (auto&& digit : digits) {
            freqs[digit]++;
        }

        long long d = 1LL;

        for (auto&& [_,cnt] : freqs) {
            d *= factorial(cnt);
        }
        auto it = freqs.find(0);
        const auto b = (it == cend(freqs) ? factorial(n) : factorial(n - 1) * (n - it->second)) / d;
        return b;
    }


    static bool check_divi_len_palindrome_rec(int k, const vector<int>& side_digits,int center_candidate, int len, int index, vector<int>& cur_vec, map<int,int>& used) {
        if (index == len / 2) {
            vector<int> comp(len);
            for (int i = 0; i < len / 2; i++) {
                comp[i] = cur_vec[i];
                comp[len - 1 - i] = cur_vec[i];
            }
            if (len % 2 == 1) {
                comp[len / 2] = center_candidate;
            }
            long long cur_val = 0;
            for (int d : comp) { cur_val = cur_val * 10 + d; }
            return cur_val % k == 0;
        }

        for (int i = 0; i < size(side_digits); i++) {
            if (index == 0 && side_digits[i] == 0) { continue; }
            if (used[side_digits[i]] > 0) {
                used[side_digits[i]]--;
                cur_vec.emplace_back(side_digits[i]);
                if (check_divi_len_palindrome_rec(k, side_digits, center_candidate, len, index + 1, cur_vec, used)) {
                    return true;
                }
                cur_vec.pop_back();
                used[side_digits[i]]++;
            }
        }
        return false;
    }

    static bool check_divi_len_palindrome(int k, const vector<int>& digits) {
        map<int, int> freqs;
        for (auto&& digit : digits) {
            freqs[digit]++;
        }
        int center_candidate = -1;
        vector<int> dupdigits;
        for (auto&& [d, c] : freqs) {
            if (c > 1) {
                for (int i = 0; i < c / 2; i++) {
                    dupdigits.emplace_back(d);
                }
            }
            if (c % 2 == 1) {
                center_candidate = d;
            }
        }
        for (auto&& [d,c] : freqs) {
            c /= 2;
        }
        vector<int> cur_vec;
        return check_divi_len_palindrome_rec(k, dupdigits, center_candidate, size(digits), 0, cur_vec, freqs);
    }




    static bool check_divi_2(const vector<int>& digits) {
        int count = 0;
        for (auto&& digit : digits) {
            if (digit != 0 && digit % 2 == 0) { count++; }
        }
        return count >= 2;
    }
    static bool check_divi_3(const vector<int>& digits) {
        return accumulate(cbegin(digits), cend(digits), 0, [](int a, int b) { return a + b; }) % 3 == 0;
    }
    static bool check_divi_4(const vector<int>& digits) {
        return check_divi_len_palindrome(4, digits);
    }
    static bool check_divi_5(const vector<int>& digits) {
        int count = 0;
        for (auto&& digit : digits) {
            if (digit == 5) { count++; }
        }
        return count >= 2;
    }
    static bool check_divi_6(const vector<int>& digits) {
        return check_divi_len_palindrome(6, digits);
    }
    static bool check_divi_7(const vector<int>& digits) {
        return check_divi_len_palindrome(7, digits);
    }
    static bool check_divi_8(const vector<int>& digits) {
        return check_divi_len_palindrome(8, digits);
    }
    static bool check_divi_9(const vector<int>& digits) {
        return accumulate(cbegin(digits), cend(digits), 0, [](int a, int b) { return a + b; }) % 9 == 0;
    }

    static bool check_divi_k(int k, const vector<int>& digits) {
        switch (k) {
        case 1:
            return true;
        case 2:
            return check_divi_2(digits);
        case 3:
            return check_divi_3(digits);
        case 4:
            return check_divi_4(digits);
        case 5:
            return check_divi_5(digits);
        case 6:
            return check_divi_6(digits);
        case 7:
            return check_divi_7(digits);
        case 8:
            return check_divi_8(digits);
        case 9:
            return check_divi_9(digits);
        }
        //assert
        return false;
    }

    static long long patterns(int n, int k, const vector<int>& cur_digits) {
        if (check_divi_k(k, cur_digits)) {
            //for (auto&& d : cur_digits) { cout << d << ","; }
            const auto v = get_patterns(n, cur_digits);
            //cout << ":patterns:" << v << endl;

            //string s;
            //for (auto&& d : cur_digits) { s += static_cast<char>(d) + '0'; }
            //sort(s.begin(), s.end());
            //my_test_dict.insert({ s,v });
            return v;
        }
        return 0LL;
    }
    static long long rec(int n, int k, vector<int>& cur_digits, int digit, bool remain_odd) {
        if (digit == 10) {
            if (size(cur_digits) == n) {
                return patterns(n, k, cur_digits);
            }
            return 0LL;
        }
        long long total = rec(n, k, cur_digits, digit + 1, remain_odd);
        const auto remain = digit == 0 ? n - size(cur_digits) - 2 : n - size(cur_digits);
        for (int i = 1; i <= remain; i++) {
            if (i % 2 == 0) {
                for (auto j = 0; j < i; j++) { cur_digits.emplace_back(digit); }
                total += rec(n, k, cur_digits, digit + 1, remain_odd);
                for (auto j = 0; j < i; j++) { cur_digits.pop_back(); }
            }
            else {
                if (remain_odd) {
                    for (auto j = 0; j < i; j++) { cur_digits.emplace_back(digit); }
                    total += rec(n, k, cur_digits, digit + 1, false);
                    for (auto j = 0; j < i; j++) { cur_digits.pop_back(); }
                }
            }
        }
        return total;
    }

    long long countGoodIntegers(int n, int k) {
        if (n == 1) { return 9 / k; }

        factorial_memo.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            factorial_memo[i] = factorial_memo[i - 1] * i;
        }
        vector<int> digits;
        return rec(n, k, digits, 0, n % 2 != 0);
    }
};


void test(int n, int k) {
    cout << Solution().countGoodIntegers(n, k) << endl;
}

int main() {
    //test(3, 6);

    //test(3, 5);
    //test(1, 4);
    test(5, 6);

    //test1(5, 6);
    return 0;
}
/*

long long test1(int n, int k) {
    unordered_set<string> dict;
    int base = pow(10, (n - 1) / 2);
    int skip = n & 1;
for (int i = base; i < base * 10; i++) {
    string s = to_string(i);
    s += string(s.rbegin() + skip, s.rend());
    long long palindromicInteger = stoll(s);
    if (palindromicInteger % k == 0) {
        sort(s.begin(), s.end());
        dict.emplace(s);
    }
}


vector<long long> factorial(n + 1, 1);
long long ans = 0;
for (int i = 1; i <= n; i++) {
    factorial[i] = factorial[i - 1] * i;
}
for (const string& s : dict) {
    vector<int> cnt(10);
    for (char c : s) {
        cnt[c - '0']++;
    }
    long long tot = (n - cnt[0]) * factorial[n - 1];
    for (int x : cnt) {
        tot /= factorial[x];
    }

    const auto it = my_test_dict.find(s);
    if (it == cend(my_test_dict)) {
        cout << "empty :" << s << endl;
    }
    else {
        if (it->second != tot) {
            cout << "invald " << s << ":" << tot << "!=" << it->second << endl;
        }
    }


    ans += tot;
}

return ans;
}*/