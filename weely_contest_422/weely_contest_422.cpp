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
    bool isBalanced(string num) {
        int evens = 0;
        int odds = 0;
        for (int i = 0; i < size(num); i++) {
            if ((i % 2) == 0) {
                evens += static_cast<int>(num[i] - '0');
            }
            else {
                odds += static_cast<int>(num[i] - '0');
            }
        }
        return evens == odds;
    }
};

static void test(string&& num) {
    cout << Solution().isBalanced(num) << endl;
}

static void run() {
    test("1234");
    test("24123");
}
}
namespace problem2 {
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        const size_t H = size(moveTime);
        const size_t W = size(moveTime.front());
        struct state {
            int y;
            int x;
            int time;
        };
        const vector<pair<int, int>> dirs{ {1,0},{0,1},{-1,0},{0,-1} };
        auto get_time = [&](const state& a)-> int {
            return max(a.time, moveTime[a.y][a.x]);
            };

        auto compare = [&](const state& a, const state& b) ->bool {
            return get_time(a) > get_time(b);
            };
        priority_queue<state, vector<state>, decltype(compare)> q(compare);

        q.push(state{ 0, 0, 0});
        vector<vector<bool>> visited(size(moveTime), vector<bool>(size(moveTime.front())));
        visited[0][0] = true;
        while (!q.empty()) {
            const auto [y, x, time] = q.top();
            if (y == H - 1 && x == W - 1) {
                return time;
            }
            q.pop();
            for (auto&& [dy, dx] : dirs) {
                const auto cy = y + dy;
                const auto cx = x + dx;

                if (0 <= cy && cy < H && 0 <= cx && cx < W) {
                    if (!visited[cy][cx]) {
                        visited[cy][cx] = true;
                        q.push(state{ cy, cx, max(time, moveTime[cy][cx]) + 1});
                    }
                }
            }

        }

        throw exception();
    }
};
static void test(vector<vector<int>>&& moveTime) {
    cout << Solution().minTimeToReach(moveTime) << endl;
}
static void run() {
    test(get_matrix_int("[[56,93],[3,38]]"));
    test(get_matrix_int("[[17,56],[97,80]]"));
    test(get_matrix_int("[[0,4],[4,4]]"));
    test(get_matrix_int("[[0,0,0],[0,0,0]]"));
    test(get_matrix_int("[[0,1],[1,2]]"));
}
}
namespace problem3 {

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        const size_t H = size(moveTime);
        const size_t W = size(moveTime.front());
        struct state {
            int y;
            int x;
            int time;
            int step;
        };
        const vector<pair<int, int>> dirs{ {1,0},{0,1},{-1,0},{0,-1} };
        auto get_time = [&](const state& a)-> int {
            return max(a.time, moveTime[a.y][a.x]);
            };

        auto compare = [&](const state& a, const state& b) ->bool {
            const auto a1 = get_time(a);
            const auto b1 = get_time(b);
            if (a1 != b1) { return a1 > b1; }
            return a.step % 2 < b.step % 2;
            };
        priority_queue<state, vector<state>, decltype(compare)> q(compare);

        q.push(state{ 0, 0, 0, 0, });
        vector<vector<int>> visited(H, vector<int>(W, INT_MAX));
        visited[0][0] = 0;
        while (!q.empty()) {
            const auto [y, x, time, step] = q.top();
            if (y == H - 1 && x == W - 1) {
                return time;
            }
            q.pop();
            const auto cur_sec = step % 2 == 0 ? 1 : 2;
            for (auto&& [dy, dx] : dirs) {
                const auto cy = y + dy;
                const auto cx = x + dx;
                if (0 <= cy && cy < H && 0 <= cx && cx < W) {
                    const auto next_time = max(time, moveTime[cy][cx]) + cur_sec;
                    if (next_time < visited[cy][cx]) {
                        visited[cy][cx] = next_time;
                        q.push(state{ cy, cx, next_time, step + 1 });
                    }
                }
            }
        }
        throw exception();
    }
};
static void test(vector<vector<int>>&& moveTime) {
    cout << Solution().minTimeToReach(moveTime) << endl;
}
static void run() {
    test(get_matrix_int("[[0,4],[4,4]]"));
    test(get_matrix_int("[[0,0,0,0],[0,0,0,0]]"));
    test(get_matrix_int("[[0,1],[1,2]]"));
    test(get_matrix_int("[[0,0,0],[0,0,0]]"));
    test(get_matrix_int("[[56,93],[3,38]]"));
    test(get_matrix_int("[[17,56],[97,80]]"));
}
}
namespace problem4 {
constexpr long long MODULO = 1e9 + 1;
class Solution {
public:
    static bool check(const string& num) {
        int evens = 0;
        int odds = 0;
        for (int i = 0; i < size(num); i++) {
            if (i % 2 == 0) {
                evens += static_cast<int>(num[i] - '0');
            }
            else {
                odds += static_cast<int>(num[i] - '0');
            }
        }
        return evens == odds;
    }

    static int naive(string& num) {
        unordered_set<string> distincts;
        sort(begin(num), end(num));
        long long count = 0;
        do {
            if (distincts.count(num) == 0) {
                if (check(num)) {
                    count++;
                    count %= MODULO;
                }
                distincts.insert(num);
            }
        } while (next_permutation(begin(num), end(num)));
        return count;
    }

    static long long factorial(int n) {
        long long result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    static long long counting(const vector<char>& list) {
        int n = size(list);
        map<int, int> frequency;
        for (int c : list) {
            frequency[c]++;
        }

        long long denominator = 1;
        for (const auto& [key, freq] : frequency) {
            denominator *= factorial(freq);
        }
        return factorial(n) / denominator;
    }


    static int rec_enum(const string& num, int index, vector<char>& even_group, vector<char>& odd_group, int even_sum, int odd_sum) {
        if (size(num) == index) {
            if (size(num) % 2 == 0) {
                if (size(even_group) == size(odd_group) && even_sum == odd_sum) {
                    auto temp = counting(even_group) * counting(odd_group);
                    temp %= MODULO;
                    return temp;
                }
            }
            else {
                if (size(even_group) == size(odd_group) + 1 && even_sum == odd_sum) {
                    auto temp = counting(even_group) * counting(odd_group);
                    temp %= MODULO;
                    return temp;
                }
            }
            return 0;
        }
        const auto even_limit = size(num) % 2 == 0 ? (size(num) / 2) : (size(num) / 2 + 1);
        const auto odd_limit = size(num) / 2;

        long long count = 0;
        if (size(even_group) < even_limit) {
            even_group.emplace_back(num[index]);
            count = rec_enum(num, index + 1, even_group, odd_group, even_sum + static_cast<int>(num[index] - '0'), odd_sum);
            even_group.pop_back();
        }

        if (size(odd_group) < odd_limit) {
            odd_group.emplace_back(num[index]);
            count += rec_enum(num, index + 1, even_group, odd_group, even_sum, odd_sum + static_cast<int>(num[index] - '0'));
            count %= MODULO;
            odd_group.pop_back();
        }
        return count;
    }


    int countBalancedPermutations(string num) {
        sort(begin(num), end(num));
        vector<char> work1, work2;
        vector<pair<vector<char>, vector<char>>> enums;
        
        return rec_enum(num, 0, work1, work2, 0, 0); 0;
    }
};
static void test(string&& num) {
    cout << Solution().countBalancedPermutations(num) << endl;
}
static void run() {
    test("123");
    test("112");
    test("1234");
    test("12345");
    test("7449833178");
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