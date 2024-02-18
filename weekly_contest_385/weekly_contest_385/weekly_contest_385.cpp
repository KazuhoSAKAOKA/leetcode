// weekly_contest_385.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>


using namespace std;


namespace problem1 {
class Solution {
public:

    static bool isPrefixAndSuffix(const string& str1, const string& str2) {
        if (str2.size() < str1.size()) {
            return false;
        }
        if (str1 != str2.substr(0, str1.size())) {
            return false;
        }
        if (str1 != str2.substr(str2.size() -  str1.size(), str1.size())) {
            return false;
        }
        return true;
    }

    int countPrefixSuffixPairs(vector<string>& words) {
        int count = 0;
        for (int i = 0; i < words.size() - 1; i++) {
            for (int j = i + 1; j < words.size(); j++) {
                if (isPrefixAndSuffix(words[i], words[j])) {
                    count++;
                }
            }
        }
        return count;
    }
};

void test(vector<string>&& words) {
    cout << Solution().countPrefixSuffixPairs(words) << endl;
}
void run() {
    test({ "a","aba","ababa","aa" });
    test({ "pa","papa","ma","mama" });
    test({ "abab","ab" });
}

}


namespace problem2 {
class Solution {
public:

    int longestCommonPrefix_str(const string& value1, const string& value2) {
        const int len = min(value1.size(), value2.size());
        for (int i = 0; i < len; i++) {
            if (value1[i] != value2[i]) {
                return i;
            }
        }
        return len;
    }

    int longestCommonPrefix(int value1, int value2) {
        const auto p1 = static_cast<int>(log10(value1));
        const auto p2 = static_cast<int>(log10(value2));
        if (p1 != p2) {
            if (p1 < p2) {
                value2 = value2 / pow(10, p2 - p1);
            }
            else {
                value1 = value1 / pow(10, p1 - p2);
            }
        }

        while (value1 != value2) {
            value1 /= 10;
            value2 /= 10;
        }
        if (value1 == 0) { return 0; }
        const auto len = static_cast<int>(to_string(value1).size());
        return len;
    }

    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        set<int> sets1(cbegin(arr1), cend(arr1));
        set<int> sets2(cbegin(arr2), cend(arr2));
        int max_value = 0;
        vector<int> s_arr1(cbegin(sets1), cend(sets1));
        vector<int> s_arr2(cbegin(sets2), cend(sets2));

        sort(begin(s_arr1), end(s_arr1), [](const auto& a, const auto& b) { return a > b; });
        sort(begin(s_arr2), end(s_arr2), [](const auto& a, const auto& b) { return a > b; });

        for (auto&& value1 : s_arr1){
            for (auto&& value2 : s_arr2) {
                const auto v1 = to_string(value1);
                const auto v2 = to_string(value2);
                if (v1.size() < max_value || v2.size() < max_value) {
                    break;
                }
                max_value = max(max_value, longestCommonPrefix_str(v1, v2));
            }
        }
        return max_value;
    }
};

void test(vector<int>&& arr1, vector<int>&& arr2) {
    cout << Solution().longestCommonPrefix(arr1, arr2) << endl;
}
void run() {

    test(
        { 3099,593,3949,1570,1150,4348,1172,2788,1068,4416,1236,945,2704,4602,2172,3932,3382,3663,3540,3524,877,1850,3815,3730,2364,4472,3537,4563,956,1324,4322,3647,2421,4683,1098,4663,2842,925,800,2748,1765,2312,2724,3834,4561,513,4327,849,3383,3365 },
        { 1447, 4908, 3018, 40, 4051, 4574, 2361, 2063, 2163, 3345, 2830, 4123, 3718, 2302, 2370, 1593, 3399, 2682, 1360, 2916, 2645, 839, 4511, 124, 1230, 3517, 132, 95, 2015, 4732, 2682, 1929, 502, 3298, 2720, 897, 2637, 2752, 2364, 31, 2653, 1760, 180, 1436, 912, 1592, 3791, 2071, 3345, 2258 }
    );


    test(
        { 657,1916,3207,555,701,657,1312,3209,2601,1319,4988,4131,4072,2084,576,581,2955,2539,4809,2579,1761,3231,1400,4359,60,1058,2801,1126,2660,154,515,3321,1040,397,2427,4127,4725,804,707,1960,3956,2583,4333,4796,3286,2772,4126,2470,1683,2991 },
        { 1724, 1423, 3422, 210, 484, 491, 796, 246, 3577, 38, 4639, 3456, 2857, 299, 1486, 4928, 3738, 1285, 3849, 4837, 2278, 754, 2272, 1359, 2821, 3027, 89, 1164, 2859, 449, 3436, 125, 688, 2707, 4401, 2511, 1636, 4214, 4209, 3431, 850, 4044, 4571, 1454, 3188, 1432, 4150, 2105, 4196, 821 }

    );


    test({1, 10, 100}, {1000});
    test({ 1, 2, 3 }, { 4, 4, 4 });



    vector<int> a1(5000, 100000000);
    vector<int> a2(5000, 100000000);
    //test(move(a1), move(a2));
}

}



namespace problem3 {

class Solution {
public:

    static bool is_prime(int value){
        const auto v = static_cast<int>(sqrt(value));
        for (int i = 2; i <= v; i++) {
            if (value % i == 0) { return false; }
        }
        return true;
    }

    static void try_add(const string& current, map<int, int>& ans_map, map<int, bool>& primes) {
        if (current.size() < 2) { return; }
        const int value = std::atoi(current.c_str());
        const auto it = primes.find(value);
        if (it != cend(primes)) {
            if (it->second) {
                ans_map[value]++;
            }
        }
        else {
            if (is_prime(value)) {
                ans_map[value]++;
                primes[value] = true;
            }
            else {
                primes[value] = false;
            }
        }
    }

    void get_values(vector<vector<int>>& mat, int i, int j, int idir, int jdir, string& current, map<int, int>& ans_map, map<int, bool>& primes) {
        if (i < 0 || j < 0 || mat.size() <= i || mat[0].size() <= j) {
            return;
        }
        current += static_cast<char>('0' + mat[i][j]);
        try_add(current, ans_map, primes);
        get_values(mat, i + idir, j + jdir, idir, jdir, current, ans_map, primes);
    }

    void get_all(vector<vector<int>>& mat, int i, int j, map<int, int>& ans_map, map<int, bool>& primes) {
        const vector<pair<int, int>> dirs
        {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            //{0, 0},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1},
        };

        for (auto&[idir, jdir] : dirs) {
            string temp;
            get_values(mat, i, j, idir, jdir, temp, ans_map, primes);
        }
    }

    int mostFrequentPrime(vector<vector<int>>& mat) {
        map<int, int> ans_map;
        map<int, bool> primes;
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                get_all(mat, i, j, ans_map, primes);
            }
        }
        int max_key = -1;
        int max_size = 0;
        for (auto&& [k, v] : ans_map) {
            if (max_size < v) {
                max_size = v;
                max_key = k;
            }
            else if(max_size == v && max_key < k){
                max_key = k;
            }
        }
        return max_key;
    }
};

void test(vector<vector<int>>&& mat) {
    cout << Solution().mostFrequentPrime(mat) << endl;
}

void run() {
    test({ {1,1},{9,9},{1,1} });
    test({ {7} });
    test({ {9,7,8},{4,6,5},{2,8,6} });
}

}

int main()
{
    //problem1::run();
    problem2::run();
    //problem3::run();

}