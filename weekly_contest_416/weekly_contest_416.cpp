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
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        unordered_set<string> banned_set(cbegin(bannedWords), cend(bannedWords));

        bool exist_once = false;
        for (auto&& word : message) {
            auto it = banned_set.find(word);
            if (it != cend(banned_set)) {
                if (exist_once) {
                    return true;
                }
                exist_once = true;
            }
        }

        return false;
    }
};
void test(vector<string>&& message, vector<string>&& bannedWords) {
    cout << Solution().reportSpam(message, bannedWords) << endl;
}

void run() {
    test(get_list_str(R"([["l","i","l","i","l"]])"), get_list_str(R"(["d","a","i","v","a"])"));
    test(get_list_str(R"(["hello","world","leetcode"])"), get_list_str(R"(["world","hello"])"));
    test(get_list_str(R"(["hello","programming","fun"])"), get_list_str(R"(["world","programming","leetcode"])"));
}
}
namespace problem2 {
class Solution {
public:
    static long long binary_search(long long ok, long long ng, std::function<bool(long long)> check) {
        while (abs(ng - ok) > 1) {
            const auto mid = (ok + ng) / 2;
            if (check(mid)) {
                ok = mid;
            }
            else {
                ng = mid;
            }
        }
        return ok;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long ng = 0;
        long long ok = ULONG_LONG_MAX / 2;
        auto check = [&](long long t)->bool {
            long long total = 0;
            for (auto&& worker_time : workerTimes) {
                long long ng1 = 1000000;
                long long ok1 = 0;
                const auto value = binary_search(ok1, ng1, [&](long long n) {
                    return static_cast<long long>(worker_time) * n * (n + 1) / 2 <= t;
                    });
                total += value;
                if (mountainHeight <= total) {
                    return true;
                }
            }
            return false;
            };

        const auto ans = binary_search(ok, ng, check);
        return ans;

    }
};
void test(int mountainHeight, vector<int>&& workerTimes) {
    cout << Solution().minNumberOfSeconds(mountainHeight, workerTimes) << endl;
}
void run() {
    test(100000, get_list_int("[1]"));

    test(4, get_list_int("[2,1,1]"));
    test(10, get_list_int("[3,2,2,4]"));
    test(5, get_list_int("[1]"));
}
}
namespace problem3 {
class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        unordered_map<char, size_t> target_map;
        for (auto&& c : word2) {
            target_map[c]++;
        }
        unordered_map<char, size_t> current_map;
        long long count = 0;
        size_t l = 0;

        auto check = [&]() {
            for (auto&& [c, t] : target_map) {
                if (current_map[c] < t) {
                    return false;
                }
            }
            return true;
            };

        for (size_t r = 0; r < size(word1); r++)
        {
            current_map[r]++;
            if (check()) {
                count += r - l + 1;
            }
        }
        return count;
    }
};
void test(string&& word1, string&& word2) {
    cout << Solution().validSubstringCount(word1, word2) << endl;
}
void run() {
    test("bcca", "abc");
    test("abcabc", "abc");
    test("abcabc", "aaabc");
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
    //problem3::run();
    problem4::run();
    return 0;
}