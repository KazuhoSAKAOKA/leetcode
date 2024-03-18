// weekly_contest_389.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <numeric>
#include <string>
#include <cmath>

using namespace std;

namespace problem1 {

class Solution {
public:
    bool isSubstringPresent(string s) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(s.size() + 1, 0));

        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < s.size(); j++) {
                const int rev = static_cast<int>(s.size()) - 1 - j;
                if (s[i] == s[rev]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                    if (dp[i + 1][j + 1] >= 2) {
                        return true;
                    }
                }
                else {
                    dp[i + 1][j + 1] = 0;
                }
            }
        }
        return false;
    }
};


void test(string&& s) {
    cout << Solution().isSubstringPresent(s) << endl;
}

void run() {
    test("leetcode");
    test("abcba");
    test("abcd");
}

}


namespace problem2 {

class Solution {
public:
    static long long counting(int n, unordered_map<long long, long long> memo) {
        if (n == 1) {
            return 0;
        }
        const auto it = memo.find(n);
        if (it != cend(memo)) {
            return it->second;
        }
        const auto v = (n - 1) + counting(n - 1, memo);
        memo[n] = v;
        return v;
    }

    long long countSubstrings(string s, char c) {
        long long c_count = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == c) {
                c_count++;
            }
        }
        if (c_count == 0) {
            return 0;
        }
        unordered_map<long long, long long> memo;
        return c_count + counting(c_count, memo);
    }
};
void test(string&& s, char c) {
    cout << Solution().countSubstrings(s, c) << endl;
}

void run() {
    test("abada", 'z');
    test("abcdx", 'a');
    test("abada", 'a');
    test("zzz", 'z');
    test("abcdefga", 'a');
}

}


namespace problem3 {

class Solution {
public:

    static bool check_k_sp(const unordered_map<char, int>& freq_map, int k, char& max_char, char& min_char) {
        if (freq_map.empty()) { return true; }
        int freq_max = 0;
        int freq_min = INT_MAX;
        for (auto&& [k, v] : freq_map) {
            if (v == 0) { continue; }
            if (freq_max < v) {
                freq_max = v;
                max_char = k;
            }
            if (freq_min > v) {
                freq_min = v;
                min_char = k;
            }
        }
        if (freq_min == INT_MAX) { return true; }
        return freq_max - freq_min <= k;
    }

    static int rec(unordered_map<char, int>& freq_map, int k) {
        if (freq_map.empty()) {
            return 0;
        }
        char max_char(0);
        char min_char(0);

        if (check_k_sp(freq_map, k, max_char, min_char)) {
            return 0;
        }

        freq_map[max_char]--;
        const auto v1 = 1 + rec(freq_map, k);
        freq_map[max_char]++;
        const auto m = freq_map[min_char];
        freq_map[min_char] = 0;
        const auto v2 = m + rec(freq_map, k);
        freq_map[min_char] = m;
        return min(v1, v2);
    }

    int minimumDeletions(string word, int k) {
        unordered_map<char, int> freq;
        for (int i = 0; i < word.size(); i++) {
            freq[word[i]]++;
        }

        int min_count = INT_MAX;

        for (auto&& [key, v] : freq) {

            // keyが１文字も取り除かずに残る文字だと仮定して、何文字取り除くかを調べる
            int current_operations = 0;
            for (auto&& [key2, v2] : freq) {
                if (key == key2) { continue; }

                if (v <= v2) {
                    // vより大きい場合は差がkを超える分だけ取り除く
                    current_operations += max(0, v2 - v - k);
                }
                else {
                    // vより小さい場合はすべて取り除く
                    current_operations += v2;
                }
            }
            min_count = min(min_count, current_operations);
        }

        return min_count;
    }
};
void test(string&& word, int k) {
    cout << Solution().minimumDeletions(word, k) << endl;
}

void run() {
    test("ip", 2);

    test("ykekkdhehmhhympxhgjyjsmmkxerplpeegaqwqmswpmkldlllrywjqyeqlmwyphgprsdorlllpmmwdwxsxgkwaogxgglokjykrqyhaasjjxalxwdkjexdqksayxqplwmmleevdkdqdvgelmdhkqgryrqawxeammjhpwqgvdhygyvyqahvkjrrjvgpgqxyywwdvpgelvsprqodrvewqyajwjsrmqgqmardoqjmpymmvxxqoqvhywderllksxapamejdslhwpohmeryemphplqlkddyhqgpqykdhrehxwsjvaqymykjodvodjgqahrejxlykmmaxywdgaoqvgegdggykqjwyagdohjwpdypdwlrjksqkjwrkekvxjllwkgxxmhrwmxswmyrmwldqosavkpksjxwjlldhyhhrrlrwarqkyogamxmpqyhsldhajagslmeehakrxjxpjjmjpydgkehesoygvosrhvyhrqmdhlomgmrqjrmxyvmapmspmdygkhsprqsaxsvsrkovdjprjjyworgqoakrwarjsryydpmvhvyalawsmlsdgolsxgaqhryemvkpkhqvvagmxoapmsmwkrakldlhyojqhjjghjxgksroqpoxqsorrelhqeseegpqpewxydvkvaoaldmsdpmvogaykhpxkjkwmslqjsdqowkqawxadevkswdhywrxkpvqxmgeolayqojqqwxoomyasjrqrjmoearskssppmxpgwrmsjlsrjyqrjkgwjwglxogmkqjpjkwyaqxymelsyxypqxrjvpmssoakksemjhvaxm", 2);
    test("aabcaba", 0);
    test("dabdcbdcdcd", 2);
    test("aaabaaa", 2);


}

}


int main()
{
//    problem1::run();
//    problem2::run();
    problem3::run();
}

