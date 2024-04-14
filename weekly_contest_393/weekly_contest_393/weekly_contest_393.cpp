// weekly_contest_393.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

namespace problem1 {

class Solution {
public:
    string findLatestTime(string s) {
        string ans;
        ans.reserve(s.size());
        
        if (s[0] == '?') {
            if (s[1] == '1' || s[1] == '0' || s[1] == '?') {
                ans.push_back('1');
            }
            else {
                ans.push_back('0');
            }
        }
        else {
            ans.push_back(s[0]);
        }

        if (s[1] == '?') {
            if (ans[0] == '1') {
                ans.push_back('1');
            }
            else {
                ans.push_back('9');
            }
        }
        else {
            ans.push_back(s[1]);
        }

        ans.push_back(':');

        if (s[3] == '?') {
            ans.push_back('5');
        }
        else {
            ans.push_back(s[3]);
        }

        if (s[4] == '?') {
            ans.push_back('9');
        }
        else {
            ans.push_back(s[4]);
        }

        return ans;
    }
};
void test(string&& s) {
    cout << Solution().findLatestTime(s) << endl;
}

void run() {
    test("??:??");
    test("1?:?4");
    test("0?:5?");
}
}

namespace problem2 {

class Solution {
public:

    static set<int> get_primes(int max_val) {
        vector<bool> values(max_val + 1, false);

        const auto v = static_cast<int>(sqrt(max_val));
        values[0] = true;
        values[1] = true;
        for (int i = 2; i <= v; i++) {
            if (values[i]) { continue; }
            for (int j = i * 2; j <= max_val; j += i) {
                values[j] = true;
            }
        }

        set<int> primes;

        for (int i = 2; i <= max_val; i++) {
            if (!values[i]) {
                primes.insert(i);
            }
        }
        return primes;
    }


    int maximumPrimeDifference(vector<int>& nums) {
        const auto max_value = *max_element(cbegin(nums), cend(nums));
        const auto primes = get_primes(max_value);

        int min_index = nums.size() - 1;
        int max_index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (primes.find(nums[i]) != cend(primes)) {
                min_index = min(min_index, i);
                max_index = max(max_index, i);
            }
        }
        return max_index - min_index;
    }
};
void test(vector<int>&& nums) {
    cout << Solution().maximumPrimeDifference(nums) << endl;
}

void run() {
    test({ 7, });
    test({ 4,2,9,5,3, });
    test({ 4,8,2,8, });
    test({ 1,7 });
}
}

namespace problem3 {

class Solution {
public:

    static long long gcd(long long a, long long b) {
        if (b == 0) {
            return a;
        }
        else {
            return gcd(b, a % b);
        }
    }
    static long long lcm(long long a, long long b) {
        long long d = gcd(a, b);
        return a / d * b;
    }

    static long long counting_tle(const vector<int>& coins, long long value) {
        int total = 0;
        for (long long i = 1; i <= value; i++) {
            if (any_of(cbegin(coins), cend(coins), [i](const auto& a) { return i % a == 0; })) {
                cout << i << ",";
                total++;
            }
        }
        cout << endl;
        return total;
    }

    static long long counting(const vector<int>& coins, long long value) {
        long long total = 0;
        for (int i = 1; i < (1 << coins.size()); i++) {
            int b = 1;
            bool odd = false;
            for (int j = 0; j < coins.size(); j++) {
                if ((i & (1 << j)) != 0) {
                    b = lcm(b, coins[j]);
                    odd = !odd;
                }
            }

            if (odd) {
                total += value / b;
            }
            else {
                total -= value / b;
            }
        }

        return  total;
    }

    static vector<int> get_coprimes(const vector<int>& coins) {
        vector<int> coprimes;

        for (int i = 0; i < coins.size(); i++) {
            const auto v = coins[i];
            if (all_of(cbegin(coins), cend(coins), 
                [v](const auto& a) 
                {
                    if (v == a) { return true; }
                    return v % a != 0;
                }))
            {
                coprimes.emplace_back(coins[i]);
            }
        }
        return coprimes;
    }


    long long findKthSmallest(vector<int>& coins, int k) {
        const auto picoins = get_coprimes(coins);
        long long l = 0;
        long long r = LLONG_MAX;
        
        while (r - l >= 1) {
            const auto v = l + (r - l) / 2;
            const auto count = counting(picoins, v);

            if (k <= count) {
                r = v;
            }
            else {
                l = v + 1;
            }
        }
        return l;
    }
};
void test(vector<int>&& coins, int k) {
    cout << Solution().findKthSmallest(coins, k) << endl;
}

void run() {
    test({ 3,6,9,}, 3);

    test({ 6, 8, 10, }, 20);

    test({ 20,6,15,16,22, }, 25727);

    test({ 5,2, }, 7);
    test({ 6,1,2,4 }, 4);
}
}

int main()
{
//	problem1::run();
//  problem2::run();
    problem3::run();
}