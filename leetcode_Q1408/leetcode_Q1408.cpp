// leetcode_Q1408.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;


class Solution {
public:
    static vector<long long> init_powers(int N, long long b, long long modulo) {
        vector<long long> powers(N + 1);
        powers[0] = 1;
        for (int i = 0; i < N; i++) {
            powers[i + 1] = (powers[i] * b) % modulo;
        }

        return powers;
    }

    static vector<long long> rolling_hash(const string& s, long long b, long long modulo) {
        const auto N = size(s);
        vector<long long> hash(N + 1);
        for (int i = 0; i < N; i++)
        {
            hash[i + 1] = (hash[i] * b + s[i]) % modulo;
        }
        return hash;
    }

    static long long get_hash(const vector<long long>& rolling_hash, const vector<long long>& powers, long long modulo, int l, int r) {
        auto hash_value = rolling_hash[r] - (rolling_hash[l] * powers[r - l] % modulo);
        if (hash_value < 0) { hash_value += modulo; }
        return hash_value;
    }

    vector<string> stringMatching(vector<string>& words) {
        constexpr long long B = 1e5 + 7;
        constexpr long long MODULO = 1e9 + 7;
        vector<vector<long long>> hashes;
        hashes.reserve(size(words));
        int max_len = 0;

        for (int i = 0; i < size(words); i++) {
            max_len = max(max_len, static_cast<int>(size(words[i])));
            hashes.emplace_back(rolling_hash(words[i], B, MODULO));
        }
        const auto powers = init_powers(max_len, B, MODULO);
        map<long long, set<int>> exist_hash_map;
        for (int i = 0; i < size(words); i++) {
            const auto total_hash_val = get_hash(hashes[i], powers, MODULO, 0, size(words[i]));
            exist_hash_map[total_hash_val].insert(i);
        }

        set<int> exists;
        for (int i = 0; i < size(words); i++) {
            for (int j = 0; j < size(words[i]); j++) {
                for (int k = 1; k <= size(words[i]) - j; k++) {
                    const auto hash_val = get_hash(hashes[i], powers, MODULO, j, j + k);
                    auto it = exist_hash_map.find(hash_val);
                    if (it != cend(exist_hash_map)) {
                        for (auto&& index : it->second) {
                            if (index != i) {
                                exists.insert(index);
                            }
                        }
                    }
                }
            }
        }
        vector<string> ans;
        ans.reserve(size(exists));
        for (auto&& index : exists) {
            ans.emplace_back(words[index]);
        }
        return ans;
    }
};

void test(vector<string>&& words) {
    output(Solution().stringMatching(words));
}

int main()
{
    test(get_list_str(R"(["mass","as","hero","superhero"])"));
    test(get_list_str(R"(["leetcode","et","code"])"));
    test(get_list_str(R"(["blue","green","bu"])"));
    return 0;
}