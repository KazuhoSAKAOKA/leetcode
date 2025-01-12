// leetcode_Q2168.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

constexpr long long MODULO = 1e9 + 7;
constexpr long long B = 1e7 + 7;

class Solution {
public:

    static std::vector<long long> init_powers(int N) {
        std::vector<long long> powers(N + 1);
        powers[0] = 1;
        for (int i = 0; i < N; i++) {
            powers[i + 1] = (powers[i] * B) % MODULO;
        }

        return powers;
    }

    static std::vector<long long> rolling_hash(const std::string& s) {
        const auto N = size(s);
        std::vector<long long> hash(N + 1);
        for (int i = 0; i < N; i++)
        {
            hash[i + 1] = (hash[i] * B + s[i]) % MODULO;
        }
        return hash;
    }

    static long long get_hash(const std::vector<long long>& rolling_hash, const std::vector<long long>& powers, int l, int r) {
        auto hash_value = rolling_hash[r] - (rolling_hash[l] * powers[r - l] % MODULO);
        if (hash_value < 0) { hash_value += MODULO; }
        return hash_value;
    }

    int equalDigitFrequency(string s) {
        const vector<long long> powers = init_powers(size(s));
        const vector<long long> hashes = rolling_hash(s);

        set<long long> exists;

        for (int l = 0; l < size(s); l++) {
            vector<int> freqs(10);
            map<int, int> count_map;
            for (int r = l + 1; r <= size(s); r++) {
                const auto index = s[r - 1] - '0';
                if (freqs[index] != 0) {
                    count_map[freqs[index]]--;
                    if (count_map[freqs[index]] == 0) {
                        count_map.erase(freqs[index]);
                    }
                }
                freqs[index]++;
                count_map[freqs[index]]++;
                if (size(count_map) == 1) {
                    exists.insert(get_hash(hashes, powers, l, r));
                }
            }
        }
        return static_cast<int>(size(exists));
    }
};

void test(string&& s) {
    cout << Solution().equalDigitFrequency(s) << endl;
}

int main()
{
    test("1212");
    test("12321");
    return 0;
}